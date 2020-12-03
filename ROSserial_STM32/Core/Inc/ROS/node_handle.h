/*
 * node_handle.h
 *
 *  Created on: Nov 29, 2020
 *      Author: franc
 */

#ifndef _NODE_HANDLE_H_
#define _NODE_HANDLE_H_

#define SYNC_SECONDS        5

#define MODE_FIRST_FF       0
/*
 * The second sync byte is a protocol version. It's value is 0xff for the first
 * version of the rosserial protocol (used up to hydro), 0xfe for the second version
 * (introduced in hydro), 0xfd for the next, and so on. Its purpose is to enable
 * detection of mismatched protocol versions (e.g. hydro rosserial_python with groovy
 * rosserial_arduino. It must be changed in both this file and in
 * rosserial_python/src/rosserial_python/SerialClient.py
 */
#define MODE_PROTOCOL_VER   1
#define PROTOCOL_VER1		0xff // through groovy
#define PROTOCOL_VER2		0xfe // in hydro
#define PROTOCOL_VER 		PROTOCOL_VER2
#define MODE_SIZE_L         2
#define MODE_SIZE_H         3
#define MODE_SIZE_CHECKSUM  4   // checksum for msg size received from size L and H
#define MODE_TOPIC_L        5   // waiting for topic id
#define MODE_TOPIC_H        6
#define MODE_MESSAGE        7
#define MODE_MSG_CHECKSUM   8   // checksum for msg and topic id

#define ID_PUBLISHER 0
#define ID_SUBSCRIBER 1
#define ID_SERVICE_SERVER 2
#define ID_SERVICE_CLIENT 4
#define ID_PARAMETER_REQUEST 6
#define ID_LOG 7
#define ID_TIME 10
#define ID_TX_STOP 11


#define MSG_TIMEOUT 20  //20 milliseconds to recieve all of message data

#include "main.h"
#include "ArduinoHardware.h"
#include "Time.h"
#include "ros.h"

extern uint8_t bufferIndex[MAX_BUFFER_RX_USART];

namespace ros {

	class Msg {
	public:
		virtual int serialize(unsigned char *outbuffer) const = 0;
		virtual int deserialize(unsigned char *data) = 0;
		virtual const char * getType() = 0;
		virtual const char * getMD5() = 0;
	};

}

namespace std_msgs {
	class Time : public ros::Msg
	{
		public:
		typedef struct {
			uint32_t sec;
			uint32_t nsec;
		} data_type_time;
		Time() {
			data_type_time data;

		}
		int serialize(unsigned char *outbuffer) const
		{
//			int offset = 0;
//			*(outbuffer + offset + 0) = (this->data.sec >> (8 * 0)) & 0xFF;
//			*(outbuffer + offset + 1) = (this->data.sec >> (8 * 1)) & 0xFF;
//			*(outbuffer + offset + 2) = (this->data.sec >> (8 * 2)) & 0xFF;
//			*(outbuffer + offset + 3) = (this->data.sec >> (8 * 3)) & 0xFF;
//			offset += sizeof(this->data.sec);
//			*(outbuffer + offset + 0) = (this->data.nsec >> (8 * 0)) & 0xFF;
//			*(outbuffer + offset + 1) = (this->data.nsec >> (8 * 1)) & 0xFF;
//			*(outbuffer + offset + 2) = (this->data.nsec >> (8 * 2)) & 0xFF;
//			*(outbuffer + offset + 3) = (this->data.nsec >> (8 * 3)) & 0xFF;
//			offset += sizeof(this->data.nsec);
//			return offset;
			return 0;
		}

		int deserialize(unsigned char *inbuffer)
		{
//			int offset = 0;
//			this->data.sec =  ((uint32_t) (*(inbuffer + offset)));
//			this->data.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
//			this->data.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
//			this->data.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
//			offset += sizeof(this->data.sec);
//			this->data.nsec =  ((uint32_t) (*(inbuffer + offset)));
//			this->data.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
//			this->data.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
//			this->data.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
//			offset += sizeof(this->data.nsec);
//			return offset;
			return 0;
		}
		protected:
	};
}

namespace ros {
//	void normalizeSecNSec(uint32_t &sec, uint32_t &nsec);
//
//	class Time
//	{
//	public:
//	  uint32_t sec, nsec;
//
//	  Time() : sec(0), nsec(0) {}
//	  Time(uint32_t _sec, uint32_t _nsec) : sec(_sec), nsec(_nsec)
//	  {
//		normalizeSecNSec(sec, nsec);
//	  }
//
//	  double toSec() const { return (double)sec + 1e-9*(double)nsec; };
//	  void fromSec(double t) { sec = (uint32_t) floor(t); nsec = (uint32_t) round((t-sec) * 1e9); };
//
//	  uint32_t toNsec() { return (uint32_t)sec*1000000000ull + (uint32_t)nsec; };
//	  Time& fromNSec(int32_t t);
//
//	  Time& operator +=(const Duration &rhs);
//	  Time& operator -=(const Duration &rhs);
//
//	  static Time now();
//	  static void setNow( Time & new_now);
//	};
}

namespace ros {

	class Subscriber_
	{
	public:
		virtual void callback(unsigned char *data)=0;
		virtual int getEndpointType()=0;

		// id_ is set by NodeHandle when we advertise
		int id_;

		virtual const char * getMsgType()=0;
		virtual const char * getMsgMD5()=0;
		const char * topic_;
		bool has_flash_topic_;
	};
}

namespace ros {
	template<class Hardware,
           int MAX_SUBSCRIBERS=25,
           int MAX_PUBLISHERS=25,
           int INPUT_SIZE=512,
           int OUTPUT_SIZE=512>
	class NodeHandle_
	{
	public:
		/********************************************************************
		       * Time functions
		********************************************************************/

	  void requestSyncTime()
	  {
		std_msgs::Time t;
		publish(ID_TIME, &t);
		rt_time = hardware_.time();
	  }

//	  void syncTime(uint8_t * data)
//	  {
//		std_msgs::Time t;
//		uint32_t offset = hardware_.time() - rt_time;
//
//		t.deserialize(data);
//		t.data.sec += offset/1000;
//		t.data.nsec += (offset%1000)*1000000UL;
//
//		this->setNow(t.data);
//		last_sync_receive_time = hardware_.time();
//	  }
//
//	  Time now()
//	  {
//		uint32_t ms = hardware_.time();
//		Time current_time;
//		current_time.sec = ms/1000 + sec_offset;
//		current_time.nsec = (ms%1000)*1000000UL + nsec_offset;
//		normalizeSecNSec(current_time.sec, current_time.nsec);
//		return current_time;
//	  }
//
//	  void setNow( Time & new_now )
//	  {
//		uint32_t ms = hardware_.time();
//		sec_offset = new_now.sec - ms/1000 - 1;
//		nsec_offset = new_now.nsec - (ms%1000)*1000000UL + 1000000000UL;
//		normalizeSecNSec(sec_offset, nsec_offset);
//	  }

		virtual int publish(int id, Msg *msg)
		{
			if(id >= 100 && !configured_)
				return 0;

			/* serialize message */
			uint16_t l = msg->serialize(message_out+7);

			/* setup the header */
			message_out[0] = 0xff;
			message_out[1] = PROTOCOL_VER;
			message_out[2] = (uint8_t) ((uint16_t)l&255);
			message_out[3] = (uint8_t) ((uint16_t)l>>8);
			message_out[4] = 255 - ((message_out[2] + message_out[3])%256);
			message_out[5] = (uint8_t) ((int16_t)id&255);
			message_out[6] = (uint8_t) ((int16_t)id>>8);

			/* calculate checksum */
			int chk = 0;
			for(int i =5; i<l+7; i++)
			  chk += message_out[i];
			l += 7;
			message_out[l++] = 255 - (chk%256);

			if( l <= OUTPUT_SIZE ){
			  hardware_.write(message_out, l);
			  return l;
			}else{
			  //logerror("Message from device dropped: message larger than buffer."); TODO: logerror
			  return -1;
			}
		}
		void initNode(){
			//hardware_.init();
			mode_ = MODE_FIRST_FF;
			bytes_ = 0;
			index_ = 0;
			topic_ = 0;
		};

		int spinOnce(uint8_t data) {

		/*if ( mode_ != MODE_FIRST_FF){
		  if (c_time > last_msg_timeout_time){
			mode_ = MODE_FIRST_FF;
		  }
		}*/

		if( data < 0 )
			return 0;

		checksum_ += data;
		if( mode_ == MODE_MESSAGE ){        /* message data being recieved */
			message_in[index_++] = data;
			bytes_--;
			if(bytes_ == 0)                  /* is message complete? if so, checksum */
				mode_ = MODE_MSG_CHECKSUM;
		}
		else if( mode_ == MODE_FIRST_FF ){
			if(data == 0xff){
				mode_++;
				//last_msg_timeout_time = c_time + MSG_TIMEOUT;
			}
		}
		else if( mode_ == MODE_PROTOCOL_VER ){
			if(data == PROTOCOL_VER){
				mode_++;
			}
			else {
				mode_ = MODE_FIRST_FF;
				if (configured_ == false) ; // TODO: requestSyncTime
				//requestSyncTime(); 	// send a msg back showing our protocol version
			}
		}
		else if( mode_ == MODE_SIZE_L ){   /* bottom half of message size */
			bytes_ = data;
			index_ = 0;
			mode_++;
			checksum_ = data;               /* first byte for calculating size checksum */
		}
		else if( mode_ == MODE_SIZE_H ){   /* top half of message size */
			bytes_ += data<<8;
			mode_++;
		}
		else if( mode_ == MODE_SIZE_CHECKSUM ){
			if( (checksum_%256) == 255)
				mode_++;
			else
				mode_ = MODE_FIRST_FF;          // Abandon the frame if the msg len is wrong
		}
		else if( mode_ == MODE_TOPIC_L ){  /* bottom half of topic id */
			topic_ = data;
			mode_++;
			checksum_ = data;               /* first byte included in checksum */
		}
		else if( mode_ == MODE_TOPIC_H ){  /* top half of topic id */
			topic_ += data<<8;
			mode_ = MODE_MESSAGE;
			if(bytes_ == 0)
				mode_ = MODE_MSG_CHECKSUM;
		}
		else if( mode_ == MODE_MSG_CHECKSUM ){ /* do checksum */
			mode_ = MODE_FIRST_FF;
			if( (checksum_%256) == 255){
				/*
				 * Se tutto ok ->
				 * TCompleted = 1;
				 * callback
				 */
				if(topic_ == ID_PUBLISHER){
					//requestSyncTime(); TODO: requestSyncTime
					//negotiateTopics(); TODO: negotiateTopics;
					//last_sync_time = c_time;
					//last_sync_receive_time = c_time;
					return -1;
				}
				else if(topic_ == ID_TIME){
					//syncTime(message_in); TODO: syncTime
				}
//				else if (topic_ == TopicInfo::ID_PARAMETER_REQUEST){
//					req_param_resp.deserialize(message_in);
//					param_recieved= true;
//				}
				else if(topic_ == ID_TX_STOP){
					configured_ = false;
				}
				else{
					if(subscribers[topic_-100])
						subscribers[topic_-100]->callback( message_in );
				}
			}
		}

		/* occasionally sync time */
		/*if( configured_ && ((c_time-last_sync_time) > (SYNC_SECONDS*500) )){
		  //requestSyncTime(); TODO: requestSyncTime
		  last_sync_time = c_time;
		}*/

		return 0;
	  }
	protected:
		int mode_;
		int bytes_;
		int topic_;
		int index_;
		int checksum_;

		bool configured_;
		/* used for syncing the time */
		uint32_t last_sync_time;
		uint32_t last_sync_receive_time;
		uint32_t last_msg_timeout_time;

		uint32_t rt_time;

		/* used for computing current time */
		uint32_t sec_offset, nsec_offset;

		uint8_t message_in[INPUT_SIZE];
		uint8_t message_out[OUTPUT_SIZE];

		//Publisher * publishers[MAX_PUBLISHERS];
		Subscriber_ * subscribers[MAX_SUBSCRIBERS];

		Hardware hardware_;
	};
}



#endif /* INC_ROS_NODE_HANDLE_H_ */
