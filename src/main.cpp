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
	ros::NodeHandle nh,nh2; 
	ros::Subscriber sub_n;
	ros::Publisher pub_n;
    ros::Subscriber sub_n_gnss;
	ros::Publisher pub_n_gnss;

public:
	PublishAndSubscribe()
	{
		pub_n = nh.advertise<sensor_msgs::Imu>("/imu",1);
		sub_n = nh.subscribe("/kitti/oxts/imu",1,&PublishAndSubscribe::Imucallback,this);
		pub_n_gnss = nh2.advertise<sensor_msgs::NavSatFix>("/gps/fix",1);
		sub_n_gnss = nh2.subscribe("/kitti/oxts/gps/fix",1,&PublishAndSubscribe::GPScallback,this);
	}

	void Imucallback(const sensor_msgs::Imu& msg)
	{
		sensor_msgs::Imu output_msg;
		// output_msg.header.seq = count;
		output_msg.header.stamp = msg.header.stamp;
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

	void GPScallback(const sensor_msgs::NavSatFix& msg2)
	{
		sensor_msgs::NavSatFix msg_navsatfix;
		msg_navsatfix.header.stamp = msg2.header.stamp;
		msg_navsatfix.header.frame_id = msg2.header.frame_id;
		msg_navsatfix.status.status = msg2.status.status;
		msg_navsatfix.status.service = msg2.status.service;
		msg_navsatfix.latitude = msg2.latitude;
		msg_navsatfix.longitude = msg2.longitude;
		msg_navsatfix.altitude = msg2.altitude;
		msg_navsatfix.position_covariance = msg2.position_covariance;
		msg_navsatfix.position_covariance_type = msg2.position_covariance_type;
		pub_n_gnss.publish(msg_navsatfix);
	}

};

int main(int argc,char **argv)
{
	ros::init(argc,argv,"subscribe and publish");
	PublishAndSubscribe SAPObject;

	ros::spin();

	return 0;
}