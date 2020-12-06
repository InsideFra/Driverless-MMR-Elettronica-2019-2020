#ifndef _ROS_std_msgs_Float32_h
#define _ROS_std_msgs_Float32_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "../msg.h"

namespace std_msgs
{

  class Float32 : public ros::Msg
  {
    public:
      float V_Ang_RF_AD;
      float V_Ang_RF_AS;
      float V_Ang_RF_PD;
      float V_Ang_RF_PS;

    Float32():
      V_Ang_RF_AD(-1),
	  V_Ang_RF_AS(-1),
	  V_Ang_RF_PD(-1),
	  V_Ang_RF_PS(-1)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;

      union {
        float real;
        uint32_t base;
      } u_data;

      u_data.real = this->V_Ang_RF_AD;
      *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_data.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_data.base >> (8 * 3)) & 0xFF;
      offset += sizeof(float);

      u_data.real = this->V_Ang_RF_AS;
	  *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
	  *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
	  *(outbuffer + offset + 2) = (u_data.base >> (8 * 2)) & 0xFF;
	  *(outbuffer + offset + 3) = (u_data.base >> (8 * 3)) & 0xFF;
	  offset += sizeof(float);

	  u_data.real = this->V_Ang_RF_PD;
	  *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
	  *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
	  *(outbuffer + offset + 2) = (u_data.base >> (8 * 2)) & 0xFF;
	  *(outbuffer + offset + 3) = (u_data.base >> (8 * 3)) & 0xFF;
	  offset += sizeof(float);

	  u_data.real = this->V_Ang_RF_PS;
      *(outbuffer + offset + 0) = (u_data.base >> (8 * 0)) & 0xFF;
	  *(outbuffer + offset + 1) = (u_data.base >> (8 * 1)) & 0xFF;
	  *(outbuffer + offset + 2) = (u_data.base >> (8 * 2)) & 0xFF;
	  *(outbuffer + offset + 3) = (u_data.base >> (8 * 3)) & 0xFF;
	  offset += sizeof(float);


      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;

      union {
        float real;
        uint32_t base;
      } u_data;

      u_data.base = 0;
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->V_Ang_RF_AD = u_data.real;
      offset += sizeof(float);

      u_data.base = 0;
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->V_Ang_RF_AS = u_data.real;
      offset += sizeof(float);

      u_data.base = 0;
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->V_Ang_RF_PS = u_data.real;
      offset += sizeof(float);

      u_data.base = 0;
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_data.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->V_Ang_RF_PD = u_data.real;
      offset += sizeof(float);
     return offset;
    }

    const char * getType(){ /*return PSTR( "std_msgs/Float32" );*/ };
    const char * getMD5(){ /*return PSTR( "73fcbf46b49191e672908e50842a83d4" );*/ }; // TODO: getType and getMD5

  };

}
#endif
