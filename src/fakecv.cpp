#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char *argv[]){
	ros::init(argc,argv,"fakeCV");
	ros::NodeHandle n;

	ros::Publisher twist_pub = n.advertise<geometry_msgs::Twist>("cv_result",100);
	ros::Rate loop_rate(5);

	geometry_msgs::Twist msg;
	while(ros::ok()){
		msg.linear.x = 9.8;
		msg.linear.y = 12.4;
		msg.linear.z = 20.0;

		twist_pub.publish(msg);

		ros::spinOnce();

		loop_rate.sleep();
	}

	return 0;
}
