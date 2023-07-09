#!/usr/bin/env python

from __future__ import print_function

import rospy
import threading
from geometry_msgs.msg import Twist

from std_msgs.msg import Float32 

class ArduinoController:

    def __init__(self, rate):

        rospy.init_node('arduino_controller')

        rospy.Subscriber("cmd_vel", Twist, self.set_objective_controller_command)
        rospy.Subscriber("motors/cut_power", Float32, self.cut_power)
        
        self.rate = rospy.Rate(rate)
        self.to_cut_power = False

        self.right_feedback = rospy.Publisher("/drivebase_speeds/right", Float32, queue_size=10)
        self.left_feedback = rospy.Publisher("/drivebase_speeds/left", Float32, queue_size=10)

        # Check this
        self.pubArduino = rospy.Publisher('control_hydra', Twist, queue_size=10)

        # For specific motors
        self.front_left = rospy.Publisher('/motor_driver_1/Command', Command, queue_size=10)
        self.back_right = rospy.Publisher('/motor_driver_2/Command', Command, queue_size=10)
        self.back_left = rospy.Publisher('/motor_driver_3/Command', Command, queue_size=10)
        self.front_right = rospy.Publisher('/motor_driver_0/Command', Command, queue_size=10)

        self.obj_fl = 0
        self.obj_br = 0
        self.obj_bl = 0
        self.obj_fr = 0

        #rospy.Subscriber("/motor_driver_2/feedback", Feedback, self.update_br_feedback)
        rospy.Subscriber("/motor_driver_1/feedback", Feedback, self.update_fl_feedback)
        rospy.Subscriber("/motor_driver_0/feedback", Feedback, self.update_fr_feedback)
        #rospy.Subscriber("/motor_driver_3/feedback", Feedback, self.update_bl_feedback)

        self.lxAddly = 0.4
        self.scale = 30 / 3.1415926 / 0.076
        #self.scale = 1000 / 3.1459256 / 0.076

        while not rospy.is_shutdown():
            #self.publish_controller_command() #old command
            self.set_objective_controller_command() # new command
            #self.pubArduino.publish() # new command without encapsulation
            self.rate.sleep()

    def update_fr_feedback(self, msg):
        self.right_feedback.publish((msg.motor_rpm_feedback / (60.0 * 20.0)) * (3.14 * 0.15 * 2.45))

    def update_fl_feedback(self, msg):
        self.left_feedback.publish((msg.motor_rpm_feedback / (60.0 * 20.0)) * (3.14 * 0.15 * 2.45))

    def cut_power(self, msg):
        self.to_cut_power = True

    # def set_objective_controller_command(self, msg):

    #     self.to_cut_power = False
    #     spd = msg.linear.x
    #     steering = msg.angular.z

    #     # .4953 is wheelbase width and 0.15 is wheel diameter
    #     r_rad = (spd + steering * (0.4953/2) * 3.14) / (0.15/2)
    #     l_rad = (spd - steering * (0.4953/2) * 3.14) / (0.15/2)

    #     max_rps = (3000 / 60)

    #     r_percentage = r_rad / max_rps
    #     l_percentage = l_rad / max_rps

    #     r_speed = r_percentage * 1000
    #     l_speed = l_percentage * 1000

    #     self.obj_fl = l_speed
    #     self.obj_fr = r_speed

    # NEW NEW NEW publishes Twist message to Arduino
    def set_objective_controller_command(self, msg):
        self.pubArduino.publish(msg)

    def update_br_command(self, msg):
        #print(msg.header.stamp.secs, self.start_time.secs, msg.header.stamp.nsecs,  msg.header.stamp.nsecs // 10 ** 8)
        ind = (msg.header.stamp.secs - self.start_time.secs) * 10 + (msg.header.stamp.nsecs // 10 ** 8)
        self.data.add('back_right_command', msg.motor_command * self.command_ratio, ind)

    def update_fl_command(self, msg):
        ind = (msg.header.stamp.secs - self.start_time.secs) * 10 + (msg.header.stamp.nsecs // 10 ** 8)
        self.data.add('front_left_command', msg.motor_command * self.command_ratio, ind)

    def update_fr_command(self, msg):
            
        ind = (msg.header.stamp.secs - self.start_time.secs) * 10 + (msg.header.stamp.nsecs // 10 ** 8)
        self.data.add('front_right_command', msg.motor_command * self.command_ratio, ind)

    def update_bl_command(self, msg):

        ind = (msg.header.stamp.secs- self.start_time.secs) * 10 + (msg.header.stamp.nsecs // 10 ** 8)
        self.data.add('back_left_command', msg.motor_command * self.command_ratio, ind)

def main():

    controller = ArduinoController(30)

if __name__ == '__main__':
    main()

    
