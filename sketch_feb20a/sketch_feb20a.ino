#define NSensori16bit 12
#define NSensori8bit 8

#define GUIMessage_L 8

#include "variant.h"
#include <due_can.h>

typedef struct {
  uint8_t InitialSequence;
  uint8_t typeMessage;
  uint8_t ID;
  uint8_t FirstSeparator;
  uint8_t SecondSeparator;
  uint8_t upperByte;
  uint8_t lowerByte;
  uint8_t TerminatorSequence;
} GUIMessage;

typedef struct {
  uint8_t IDSensore;
  uint8_t Nome[24];
  uint8_t helper;
  uint16_t lastValoreChecked;
} SensList16;

typedef struct {
  uint8_t IDSensore;
  uint8_t Nome[24];
  uint8_t helper;
  uint8_t lastValoreChecked;
} SensList8;

GUIMessage TxB = {0xF0, 0, 0, 250, 249, 0, 0, 255};
uint8_t TxBB[GUIMessage_L];

uint8_t StartAcquisition = 0;
uint8_t StatoVeicolo = 0;

// SERIAL
uint8_t RxBuffer[24] = {0};
uint8_t RxBufferLast[24] = {0};
// END SERIAL

uint32_t timer0 = 0;

void serialize_GUI(GUIMessage a, uint8_t *b);

void error_handle(uint8_t id);

SensList16 SList16[NSensori16bit] = {
  //  ID, NOME,         h, UltimoValore;
    {1,   "Acc X",      0, 0}, // Analogico
    {2,   "Acc Y",      1, 0}, // Analogico
    {3,   "Giroscopio", 0, 0}, // Analogico
    {4,   "APPS1",      0, 0}, // Potenziometro Acceleratore
    {5,   "APPS2",      1, 0}, // Potenziometro Acceleratore Backup
    {6,   "TPS1",       0, 0}, // Potenziometro Apertura Farfalla
    {7,   "TPS2",       1, 0}, // Potenziometro Apertura Farfalla Backup
    {8,   "PosFrizDes", 0, 0}, //
    {9,   "PosFrenoDes",0, 0}, //
    {10,  "RPM",        0, 0}, //
    {11,  "LAMBDA",        0, 0}, //
    {12,  "V Batt12", 0, 0},  // Analogico, V Batteria 12v
};

SensList8 SList8[NSensori8bit] = {
  //  ID, NOME,       h, UltimoValore;
    {22,  "V Batt24", 1, 0},  // Analogico, V Batteria 12v
    {24,  "TOil",     0, 0},  // Sens. Temp. Olio,    Analogico
    {25,  "TEngine",  0, 50}, // Sens. Temp. Acqua,   Analogico
    {26,  "STAir",    0, 0},  // Sens. Temp. Aria Asp, Analogico
    {27,  "SGear",    0, 0},  // Marcia Inserita
    {28,  "POil",     0, 0},  // Sens. Temp. Olio,    Analogico
    {29,  "vVehicle", 0, 0} // Sens. Temp. Olio,    Analogico
};

void setup() {
  Serial.begin(115200);
  // Initialize CAN0 and CAN1, Set the proper baud rates here
  Can0.begin(1000000);
  Can1.begin(1000000);
  
  //By default there are 7 mailboxes for each device that are RX boxes
  //This sets each mailbox to have an open filter that will accept extended
  //or standard frames
  int filter;
  //extended
  for (filter = 0; filter < 3; filter++) {
    Can0.setRXFilter(filter, 0, 0, true);
    Can1.setRXFilter(filter, 0, 0, true);
  }  
  //standard
  for (int filter = 3; filter < 7; filter++) {
    Can0.setRXFilter(filter, 0, 0, false);
    Can1.setRXFilter(filter, 0, 0, false);
  }  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
}

void loop() {

  CAN_FRAME incoming;

  if (Can0.available() > 0) {
    Can0.read(incoming); 
    printFrame(incoming);
  }
  if (Can1.available() > 0) {
    Can1.read(incoming); 
    printFrame(incoming);
  }
  
  if(Serial.available()) {
    uint8_t i = 0;
    while(Serial.available()) {
      if (i >= 24) {
        error_handle(1);
      }
      RxBuffer[i] = Serial.read();
      i++;
      delay(20);
    }
  }
  if(RxBuffer[0] != RxBufferLast[0]) {
    if (!strncmp((char*)RxBuffer, "StartAcquisition", 16)) {
      StartAcquisition = 1;
      TxB.typeMessage = 0x01;
      serialize_GUI(TxB, TxBB);
      Serial.write(TxBB, 8);
    }
    if (!strncmp((char*)RxBuffer, "StopAcquisition", 16)) {
      StartAcquisition = 0;
      TxB.typeMessage = 0x02;
      serialize_GUI(TxB, TxBB);
      Serial.write(TxBB, 8);
    }
    if (!strncmp((char*)RxBuffer, "StartVehicle", 12)) {
      StatoVeicolo = 1;
      TxB.typeMessage = 0x03;
      serialize_GUI(TxB, TxBB);
      Serial.write(TxBB, 8);
    }
    if (!strncmp((char*)RxBuffer, "StopVehicle", 12)) {
      StatoVeicolo = 0;
      TxB.typeMessage = 0x04;
      serialize_GUI(TxB, TxBB);
      Serial.write(TxBB, 8);
    }
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    memset(RxBuffer, 0, sizeof(RxBuffer));
  }
  if (millis() - timer0 >= 500) {
    timer0 = millis();
    if (StartAcquisition) {
      TxB.typeMessage = 0x01;
      serialize_GUI(TxB, TxBB);
      Serial.write(TxBB, 8);
  
      for (uint8_t i = 0; i < NSensori16bit; i++) {
        TxB.typeMessage = 0x00;
        TxB.ID = SList16[i].IDSensore;
        TxB.lowerByte = ((uint16_t)SList16[i].lastValoreChecked >> 0) & 0xFF;  // shift by 0 not needed, of course, just stylistic
        TxB.upperByte = ((uint16_t)SList16[i].lastValoreChecked >> 8) & 0xFF;
        serialize_GUI(TxB, TxBB);
        Serial.write(TxBB, 8);
      }
      for (uint8_t i = 0; i < NSensori8bit; i++) {
        TxB.typeMessage = 0x00;
        TxB.ID = SList8[i].IDSensore;
        TxB.lowerByte = ((uint16_t)SList8[i].lastValoreChecked >> 0) & 0xFF;  // shift by 0 not needed, of course, just stylistic
        TxB.upperByte = ((uint16_t)SList8[i].lastValoreChecked >> 8) & 0xFF;
        serialize_GUI(TxB, TxBB);
        Serial.write(TxBB, 8);
      }
    }
    else if (!StartAcquisition) {
      TxB.typeMessage = 0x02;
      serialize_GUI(TxB, TxBB);
      Serial.write(TxBB, 8);
    }
  }
}

void serialize_GUI(GUIMessage a, uint8_t *b) {
  b[0] = a.InitialSequence;
  b[1] = a.typeMessage;
  b[2] = a.ID;
  b[3] = a.FirstSeparator;
  b[4] = a.SecondSeparator;
  b[5] = a.lowerByte;
  b[6] = a.upperByte;
  b[7] = a.TerminatorSequence;
}

void error_handle(uint8_t id) {
  Serial.println("ERROR CATCHED");
}

void printFrame(CAN_FRAME &frame) {
   /*Serial.print("ID: 0x");
   Serial.print(frame.id, HEX);
   Serial.print(" Len: ");
   Serial.print(frame.length);
   Serial.print(" Data: 0x");
   for (int count = 0; count < frame.length; count++) {
       Serial.print(frame.data.bytes[count], HEX);
       Serial.print(" ");
   }
   Serial.print("\r\n");*/
   if(frame.id == 0x0) { // poil
      SList8[5].lastValoreChecked = (frame.data.byte[0]);
   }
   if(frame.id == 0x1) { // tmot
      SList8[2].lastValoreChecked = (frame.data.bytes[0]-40);
   }
   if(frame.id == 0x2) { // tint
      SList8[3].lastValoreChecked = (frame.data.bytes[0]-40);
   }
   if(frame.id == 0x03) { // toil
      SList8[1].lastValoreChecked = (frame.data.bytes[0]-40);
      //Serial.println(SList8[2].lastValoreChecked, DEC);
      //Serial.println(frame.data.bytes[0], DEC);
   }
   if(frame.id == 0x04) { // nmot
      SList16[9].lastValoreChecked = (frame.data.bytes[1] << 8 | frame.data.bytes[0]);
      //Serial.println(SList8[2].lastValoreChecked, DEC);
      //Serial.println(frame.data.bytes[0], DEC);
   }
   if(frame.id == 0x05) { // ub
      SList16[11].lastValoreChecked = (frame.data.bytes[1] << 8 | frame.data.bytes[0]);
   }
   if(frame.id == 0x06) { // lambda
      SList16[10].lastValoreChecked = (frame.data.bytes[1] << 8 | frame.data.bytes[0]);
   }
}
