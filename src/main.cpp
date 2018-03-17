/*
 * main.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: kyle
 */
#include "interface.h"
#include <unistd.h>
#include <cstdio>

void myCB(const mavlink_message_t *message, const mavconn::Framing framing){
	static mavlink_heartbeat_t hb;
	static mavlink_attitude_t att;
	switch(message->msgid){
		case MAVLINK_MSG_ID_HEARTBEAT:
			mavlink_msg_heartbeat_decode(message,&hb);
			printf("Decoded Heartbeat: %d,%d,%d,%d\n",hb.type,hb.base_mode,hb.custom_mode,hb.system_status);
			break;
		case MAVLINK_MSG_ID_ATTITUDE:
			mavlink_msg_attitude_decode(message,&att);
			printf("Decoded Attitude: %d, %f, %f, %f",att.time_boot_ms,att.roll,att.pitch,att.yaw);
			break;
		default:
			printf("Unknown message\n");
	}
	printf("TODO: publish to ROS here\n\n");
}

int main(int argc, char* argv[]){
	mavconn::MAVConnInterface::Ptr fcu_link;
	fcu_link=mavconn::MAVConnInterface::open_url("serial:///dev/ttyUSB0",21,78);

//	fcu_link->message_received_cb=[](const mavlink_message_t *message, const mavconn::Framing framing){
//		printf("Callback executed, long live Lambda\n");
//		printf("TODO: publish to ROS here\n\n");
//	};
	fcu_link->message_received_cb=myCB;
	while(true){
		sleep(0);
	}
}
