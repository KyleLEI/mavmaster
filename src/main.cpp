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
//	try{
//		MAVComm mavcomm(1,1);
//	}catch(boost::system::system_error &err){
//		printf("Error configuring serial device: %s\n",err.what());
//	}
	mavconn::MAVConnInterface ser(21,78);
	ser.message_received_cb=myCB;
	while(true){
		sleep(0);
	}
	//ser.ReceivedCb=NULL;
}
