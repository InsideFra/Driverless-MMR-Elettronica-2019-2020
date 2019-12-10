<html>
<body>
Driverless-MMR-Elettronica

<p>Da decidere</p>
<ul>
  <li>Microcontrollore per applicazioni autonome :
    <ul>
      <li><a href="https://www.microchip.com/wwwproducts/en/PIC32MZ1024ECH064"> 32 Bit, Microchip</a> NOARM, CAN BUS Disponibile</li>
      <li><a href="https://www.microchip.com/wwwproducts/en/PIC18F26K83"> 8 Bit, Microchip</a> NOARM, CAN BUS Disponibile, 28 pin, molto semplice</li>
      <li><a href="https://www.microchip.com/wwwproducts/en/PIC18F26K83"> 8 Bit, Microchip (ATMEGA)</a> NOARM, CAN BUS Non disponibile, molto semplice ma con più funzionalità (<i>aka "Sensor Node Applications"</i>)</li>
    </ul>
  </li>
</ul>

<p>Gli Attutatori da realizzare sono 4:</p>
  <b>Freno</b> :
    <ul>
	<li>
    Bisogna sviluppare un sistema "Brake by Wire", concesso dal regolamento <b>solo durante la guida Driverless</b> (T6.1.4), quindi
    complementare ai due sistemi idraulici già presenti sulla combustion (T6.1.2)
    <p>Possibile soluzione: Dietro al giunto, che collega la leva del freno alla pompa del freno, potrebbe essere inserito un attuatore lineare non collegato
    alla leva del freno. In questo modo, in caso di guida manuale, la leva del freno continuerà a funzionare anche senza il funzionamento dell'attuatore
    In caso di guida autonoma, il movimento dell'attuatore muoverà la leva del freno, creando pressione
    Per sicurezza, sono necessari due attuatori, con fili di controllo separati
    </p>
	</li>
	</ul>
    <p>Necessario:</p>
    <ul>
      <li>- Dal disegno sul cad, la leva del freno agisce su due pompe che creano pressione sui due sistemi idraulici.</li>
      <li>- Due Motori Elettrici che producano pressione nel circuito idraulico dei freni (Due attuatori lineari sembrano già essere stati scelti, con relativo disegno CAD)</li>
      <li>- Sensore velocità (istantaneo E non) su ogni singola ruota, collegato al MCU (1)
      </li>
      <li>- Due Accelerometri posti sulla stessa linea su parti opposte dell'auto (2) <br><i> NB Almeno uno sembra già essere presente, verificare </i></li>
      <li>- Giroscopio (5) - <i>NB Sembra già essere presente, verificare</i></li>
      <li>- Sensore pressione idraulica su entrambi i circuiti (3)
      <br><i>NB Il GPS non appare come un sistema indispensabile, in quanto è consentito nella sua forma base, imprecisa, GPS
      e in forma DGPS, più precisa, ma senza la sicurezza di poterlo utilizzare, dunque è preferibile non utilizzarlo.
      </i></li><li>- Microcontrollore che gestisca i due motori collegato al CAN BUS e i dati provenienti da (1, 2, 3, 5) </p>
      </li>
      </ul>
    Elenco sensori :
    <ul>
        <li> Accelerometro :
          <ul>
            <li> ... </li>
          </ul>
        </li>
        <li> Giroscopio :
          <ul>
            <li> ... </li>
          </ul>
        </li>
        <li> Sensore pressione :
          <ul>
            <li> ... </li>
          </ul>
        </li>
        <li> Attuatore Lineare :
          <ul>
            <li> ... </li>
          </ul>
        </li>
    </ul>
<b>Acceleratore : </b>
  -Necessario: 
  <ul>
    <li>- Dalla visione del CAD, l'acceleratore sembra già essere elettronico </li>
    <li>- Microcontrollore dedicato collegato al CAN BUS, dovrà:
      <ul>
		<li>- Interfacciarsi con la centralina Magneti Marelli, in modo da simulare la pressione del pedale (0% - 100%)</li>
		<li>- Leggere i dati provenienti dall'acceleratore</ul>
	  </ul>
	</li>
  </ul>
<b>Sterzo : </b>
  Steering systems using cables or belts for actuation are prohibited.
  [DV ONLY] This does not apply for autonomous steering actuators.
  (T2.6.2) The steering wheel must directly mechanically actuate the front wheels
  Necessario: 
  <ul>
    <li>- Motore Elettrico ( Stepper Motor ? ) con controllo coppia angolare </li>
    <li>- MCU collegato al CAN BUS con controllo del motore dello sterzo </li>
  </ul>
<b> Frizione + Cambio Marcia : </b>
</body>
</html>
