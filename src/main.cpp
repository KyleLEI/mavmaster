/*
 * main.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: kyle
 */
#include "interface.h"
#include <unistd.h>
#include <cstdio>

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

ros::Publisher att_pub;

void myCB(const mavlink_message_t *message, const mavconn::Framing framing){
	static mavlink_heartbeat_t hb;
	static mavlink_attitude_t att;

	static geometry_msgs::Twist ros_att;
	switch(message->msgid){
		case MAVLINK_MSG_ID_HEARTBEAT:
			mavlink_msg_heartbeat_decode(message,&hb);
			printf("Decoded Heartbeat: %d,%d,%d,%d\n\n",hb.type,hb.base_mode,hb.custom_mode,hb.system_status);
			break;
		case MAVLINK_MSG_ID_ATTITUDE:
			mavlink_msg_attitude_decode(message,&att);
			printf("Decoded Attitude: %d, %f, %f, %f\n\n",att.time_boot_ms,att.roll,att.pitch,att.yaw);
			ros_att.angular.x=att.roll;
			ros_att.angular.y=att.pitch;
			ros_att.angular.z=att.yaw;
			att_pub.publish(ros_att);
			break;
		default:
			printf("Unknown message\n\n");
	}
}

int main(int argc, char* argv[]){

	ros::init(argc,argv,"mavmaster");
	ros::NodeHandle n;
	
	att_pub = n.advertise<geometry_msgs::Twist>("Attitude",50);

	mavconn::MAVConnInterface::Ptr fcu_link;
	fcu_link=mavconn::MAVConnInterface::open_url("serial:///dev/ttyUSB0",21,78);

//	fcu_link->message_received_cb=[](const mavlink_message_t *message, const mavconn::Framing framing){
//		printf("Callback executed, long live Lambda\n");
//	};
	fcu_link->message_received_cb=myCB;
    ros::spin();
}
