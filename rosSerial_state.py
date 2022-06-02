#include <ros.h>
#include <nav_msgs/Odometry.h>


ros::NodeHandle n;
nav_msgs::Odometry odom;

ros::Publisher odometry("/wheelOdometry", &odom);

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
  n.initNode();
  Serial.begin(57600);
  attachInterrupt(digitalPinToInterrupt(2), revolutions, RISING);
  n.advertise(odometry);
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(1000);
  detachInterrupt(digitalPinToInterrupt(2));

  time = millis() - stTime;
  stTime = millis();
  float tempCount = count / nOfslits;     // convert the no of slits covered to revolutions
  rpm = ((tempCount * 1000 / time) * 60); // RPM OF WHEEL
  distance = count * cirOfWheel / 40;     // Distance travelled by the wheel
  count = 0;
  linSpeed = (rpm * cirOfWheel) / 60; // Linear Speed of the car in motion

  x = distance;
  vx = linSpeed;

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

  Serial.print("\n rpm = ");
  Serial.print(rpm);

  // publish the message
  odometry.publish(&odom);
  n.spinOnce();
  delay(50);
  attachInterrupt(digitalPinToInterrupt(2), revolutions, RISING);

}
