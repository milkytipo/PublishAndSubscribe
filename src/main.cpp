#include <ros/ros.h>
#include <serial/serial.h> 
#include <std_msgs/String.h>
#include <std_msgs/Empty.h> 
#include <nmea_msgs/Gpgga.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>
#include <string>
#include <sstream>
#include <Eigen/Core>
#include <Eigen/Geometry>
using namespace std;

#define PI 3.141592653589793


class PublishAndSubscribe
{

private:
	ros::NodeHandle nh; 
	ros::Subscriber sub_n;
	ros::Publisher pub_n;

public:
	PublishAndSubscribe()
	{
		pub_n = nh.advertise<sensor_msgs::Imu>("/imu",1);
		sub_n = nh.subscribe("/kitti/oxts/imu",1,&PublishAndSubscribe::Imucallback,this);
	}

	void Imucallback(const sensor_msgs::Imu& msg)
	{
		sensor_msgs::Imu output_msg;
		// output_msg.header.seq = count;
		output_msg.header.stamp = ros::Time::now();
		output_msg.header.frame_id = "imu";
		output_msg.orientation.x = msg.orientation.x;
		output_msg.orientation.y = msg.orientation.y;
		output_msg.orientation.z = msg.orientation.z;
		output_msg.orientation.w = msg.orientation.w;
		output_msg.orientation_covariance = msg.orientation_covariance;
		output_msg.angular_velocity.x = msg.angular_velocity.x;
		output_msg.angular_velocity.y = msg.angular_velocity.y;
		output_msg.angular_velocity.z = msg.angular_velocity.z;
		output_msg.angular_velocity_covariance = msg.angular_velocity_covariance;
		output_msg.linear_acceleration.x = msg.linear_acceleration.x;
		output_msg.linear_acceleration.y = msg.linear_acceleration.y;
		output_msg.linear_acceleration.z = msg.linear_acceleration.z;
		output_msg.linear_acceleration_covariance = msg.linear_acceleration_covariance;
		pub_n.publish(output_msg);
	}

};

int main(int argc,char **argv)
{
	ros::init(argc,argv,"subscribe and publish");
	PublishAndSubscribe SAPObject;

	ros::spin();

	return 0;
}