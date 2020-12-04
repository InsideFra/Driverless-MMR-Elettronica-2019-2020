/*
 * msg.h
 *
 *  Created on: 4 dic 2020
 *      Author: franc
 */

#ifndef INC_ROS_MSG_H_
#define INC_ROS_MSG_H_

namespace ros {
	class Msg {
	public:
		virtual int serialize(unsigned char *outbuffer) const = 0;
		virtual int deserialize(unsigned char *data) = 0;
		virtual const char * getType() = 0;
		virtual const char * getMD5() = 0;


	  // Copy data from variable into a byte array
	  template<typename A, typename V>
	  static void varToArr(A arr, const V var)
	  {
		for(size_t i = 0; i < sizeof(V); i++)
		  arr[i] = (var >> (8 * i));
	  }

	  // Copy data from a byte array into variable
	  template<typename V, typename A>
	  static void arrToVar(V& var, const A arr)
	  {
		var = 0;
		for(size_t i = 0; i < sizeof(V); i++)
		  var |= (arr[i] << (8 * i));
	  }
	};
}
#endif /* INC_ROS_MSG_H_ */
