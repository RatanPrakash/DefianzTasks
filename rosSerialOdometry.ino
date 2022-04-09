#include <ros.h>
// #include <std_msgs/Float32.h>
#include <nav_msgs/Odometry.h>
// #include <tf/transform_broadcaster.h>         //Optional

ros::NodeHandle n;
nav_msgs::Odometry odom;
// ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);

ros::Publisher odometry("/wheelOdometry", &odom);


// tf::TransformBroadcaster odom_broadcaster;     //Optional

double x = 0.0;
double y = 0.0;
double th = 0.0;

double vx = 0.0;
double vy = 0.0;
double vth = 0.0;

ros::Time current_time;

float count = 0;
int stTime = 0;
int time;
float rpm = 0.0;               // RPM
float linSpeed = 0.0;          // SPEED OF CAR
float distance = 0.0;          // LINEAR DISTANCE TRAVELLED
const int nOfslits = 40;       // no. of slits in one full rotation
const float cirOfWheel = 0.65; // some random value as CIRCUMFERENCE OF WHEEL in meters

void revolutions()
{
  count++;
}

void setup()
{
  // put your setup code here, to run once:
  n.initNode();
  // pinMode(13, OUTPUT);
  Serial.begin(9600);
  // pinMode(7, INPUT);
  attachInterrupt(0, revolutions, RISING);
  n.advertise(odometry);
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(1000);
  detachInterrupt(0);

  time = millis() - stTime;
  stTime = millis();
  float tempCount = count / nOfslits;     // convert the no of slits covered to revolutions
  rpm = ((tempCount * 1000 / time) * 60); // RPM OF WHEEL
  distance = count * cirOfWheel / 40;     // Distance travelled by the wheel
  count = 0;
  linSpeed = (rpm * cirOfWheel) / 60; // Linear Speed of the car in motion

  x = distance;
  vx = linSpeed;

  // //since all odometry is 6DOF we'll need a quaternion created from yaw
  // geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

  // //first, we'll publish the transform over tf
  // geometry_msgs::TransformStamped odom_trans;
  // odom_trans.header.stamp = current_time;
  // odom_trans.header.frame_id = "odom";
  // odom_trans.child_frame_id = "base_link";

  // odom_trans.transform.translation.x = x;
  // odom_trans.transform.translation.y = y;
  // odom_trans.transform.translation.z = 0.0;
  // // odom_trans.transform.rotation = odom_quat;

  // //send the transform
  // odom_broadcaster.sendTransform(odom_trans);          //OPTIONAL

  // next, we'll publish the odometry message over ROS
//   nav_msgs::Odometry odom;
  odom.header.stamp = current_time;
  odom.header.frame_id = "odom";

  // set the position
  odom.pose.pose.position.x = x;
  odom.pose.pose.position.y = y;
  odom.pose.pose.position.z = 0.0;
  // odom.pose.pose.orientation = odom_quat;

  // set the velocity
  odom.child_frame_id = "base_link";
  odom.twist.twist.linear.x = vx;
  odom.twist.twist.linear.y = vy;
  odom.twist.twist.angular.z = vth;

  // publish the message
  odometry.publish(&odom);
}
