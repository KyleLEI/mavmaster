/*
 * main.cpp
 *
 *  Created on: Mar 3, 2018
 *      Author: kyle
 */
#include "mavcomm.h"

int main(int argc, char* argv[]){
	try{
		MAVComm mavcomm(1,1);
	}catch(boost::system::system_error &err){
		printf("Error configuring serial device: %s\n",err.what());
	}

}
