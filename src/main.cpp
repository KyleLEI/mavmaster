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

	printf("Callback executed\n");
}
int main(int argc, char* argv[]){
	mavconn::MAVConnInterface::Ptr fcu_link;
	fcu_link=mavconn::MAVConnInterface::open_url("serial:///dev/ttyUSB0",21,78);
	fcu_link->message_received_cb=myCB;
	while(true){
		sleep(0);
	}
}
