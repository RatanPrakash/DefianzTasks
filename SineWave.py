#! /usr/bin/env python3
import math
import numpy as np
import rospy
from ackermann_msgs.msg import AckermannDriveStamped

##some required constants
oneDegtoRad = math.pi/180
max_angle = 30.0
vel = 0


if __name__ == "__main__":
    rospy.init_node("SinWave Mode", anonymous= False)

    # target_angle = 0.0      ##maybe not required here
    # curr_angle = 0.0

    msg = AckermannDriveStamped()
    for i in range(0,361):
        Angle = math.sin(i * oneDegtoRad); ## using Sine func by converting angles to radian
        argAngle = np.interp(Angle * 10, [-10, 10], [-max_angle, max_angle]);    ## mapping extreme values of sin function to -45/+45 
        # target_angle = argAngle - curr_angle
        pub = rospy.Publisher('/robot_control/command',AckermannDriveStamped , queue_size = 1)
        
        msg.header.stamp = rospy.Time.now()
        msg.header.frame_id = '/SinWaveAngles'
        msg.drive.steering_angle = argAngle
        msg.drive.speed = vel  #m/s
        pub.publish(msg)
        # curr_angle = argAngle    ##don't think its required here

        ## publisher to publish steering and velocity commands to /robot_control/command (topic which is subscribed by robot_controls node to drive the car)

    # ts.registerCallback(callback)
        rospy.spin()


