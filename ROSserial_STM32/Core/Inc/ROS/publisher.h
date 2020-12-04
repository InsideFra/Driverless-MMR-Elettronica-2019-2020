/*
 * publisher.h
 *
 *  Created on: 4 dic 2020
 *      Author: franc
 */

#ifndef INC_ROS_PUBLISHER_H_
#define INC_ROS_PUBLISHER_H_

#include "TopicInfo.h"
#include "node_handle.h"

namespace ros {
	/* Generic Publisher */
	class Publisher
	{
	public:
	  Publisher( const char * topic_name, Msg * msg, int endpoint=ID_PUBLISHER) :
		topic_(topic_name),
		has_flash_topic_( false ),
		msg_(msg),
		endpoint_(endpoint)
	  {};

	  int publish( const Msg * msg ) { return nh_->publish(id_, msg); };
	  int getEndpointType(){ return endpoint_; }

	  const char * topic_;
	  bool has_flash_topic_;
	  Msg *msg_;
	  // id_ and no_ are set by NodeHandle when we advertise
	  int id_;
	  NodeHandleBase_* nh_;

	private:
	  int endpoint_;
	};
}


#endif /* INC_ROS_PUBLISHER_H_ */
