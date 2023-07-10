#!/usr/bin/env python

import rospy
from diagnostic_msgs.msg import DiagnosticArray
import os

# Directory to store the collected information
COLLECTED_INFO_DIRECTORY = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'diagnostics')

def diagnostics_callback(msg):
    # Create a unique filename based on the current timestamp
    filename = os.path.join(COLLECTED_INFO_DIRECTORY, 'diagnostics_'+str(rospy.Time.now())+'.txt')

    # Write the received diagnostics information to the file
    with open(filename, 'w') as file:
        file.write(str(msg))

    print("details saved")

def subscribe_to_diagnostics_topic():
    rospy.init_node('diagnostics_subscriber', anonymous=True)
    rospy.Subscriber('/diagnostics', DiagnosticArray, diagnostics_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        if not os.path.exists(COLLECTED_INFO_DIRECTORY):
            os.makedirs(COLLECTED_INFO_DIRECTORY)
        subscribe_to_diagnostics_topic()
    except rospy.ROSInterruptException:
        pass

