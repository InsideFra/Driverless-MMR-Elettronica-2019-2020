/*
 * time.h
 *
 *  Created on: 4 dic 2020
 *      Author: franc
 */

#ifndef INC_ROS_STD_MSGS_TIME_H_
#define INC_ROS_STD_MSGS_TIME_H_

#include "../msg.h"
#include "../Time.h"

namespace std_msgs { // same as original
	class Time : public ros::Msg
	{
		public:
		typedef ros::Time _data_type;
		_data_type data;

		Time(): data() {}
		virtual int serialize(unsigned char *outbuffer) const
		{
			int offset = 0;
			*(outbuffer + offset + 0) = (this->data.sec >> (8 * 0)) & 0xFF;
			*(outbuffer + offset + 1) = (this->data.sec >> (8 * 1)) & 0xFF;
			*(outbuffer + offset + 2) = (this->data.sec >> (8 * 2)) & 0xFF;
			*(outbuffer + offset + 3) = (this->data.sec >> (8 * 3)) & 0xFF;
			offset += sizeof(this->data.sec);
			*(outbuffer + offset + 0) = (this->data.nsec >> (8 * 0)) & 0xFF;
			*(outbuffer + offset + 1) = (this->data.nsec >> (8 * 1)) & 0xFF;
			*(outbuffer + offset + 2) = (this->data.nsec >> (8 * 2)) & 0xFF;
			*(outbuffer + offset + 3) = (this->data.nsec >> (8 * 3)) & 0xFF;
			offset += sizeof(this->data.nsec);
			return offset;
			return 0;
		}

		virtual int deserialize(unsigned char *inbuffer)
		{
			int offset = 0;
			this->data.sec =  ((uint32_t) (*(inbuffer + offset)));
			this->data.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
			this->data.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
			this->data.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
			offset += sizeof(this->data.sec);
			this->data.nsec =  ((uint32_t) (*(inbuffer + offset)));
			this->data.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
			this->data.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
			this->data.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
			offset += sizeof(this->data.nsec);
			return offset;
			return 0;
		}
		const char * getType(){ /*return PSTR( "std_msgs/Time" );*/return 0; };
		const char * getMD5(){ /*return PSTR( "cd7166c74c552c311fbcc2fe5a7bc289" );*/return 0; }; // TODO: getType, getMD5

	};
}
#endif /* INC_ROS_STD_MSGS_TIME_H_ */
