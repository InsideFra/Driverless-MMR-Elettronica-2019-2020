/*
 * subscribers.h
 *
 *  Created on: 4 dic 2020
 *      Author: franc
 */

#ifndef INC_ROS_SUBSCRIBER_H_
#define INC_ROS_SUBSCRIBER_H_

#include "TopicInfo.h"

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
#endif /* INC_ROS_SUBSCRIBER_H_ */
