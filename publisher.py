#!/usr/bin/env python

import rospy
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue

def publish_diagnostics_data():
    rospy.init_node('diagnostics_publisher', anonymous=True)
    pub = rospy.Publisher('/diagnostics', DiagnosticArray, queue_size=10)
    rate = rospy.Rate(1)  # Publish at 1Hz

    while not rospy.is_shutdown():
        # Create a DiagnosticArray message
        diagnostics = DiagnosticArray()
        diagnostics.header.stamp = rospy.Time.now()

        # Create a DiagnosticStatus message
        status = DiagnosticStatus()
        status.name = "MyComponent"
        status.level = DiagnosticStatus.OK
        status.message = "Everything is operating normally"

        # Add key-value pairs of diagnostic information
        status.values.append(KeyValue("Temperature", "25C"))
        status.values.append(KeyValue("Voltage", "12V"))

        # Add the status to the DiagnosticArray
        diagnostics.status.append(status)

        # Publish the diagnostics message
        pub.publish(diagnostics)
        rate.sleep()

if __name__ == '__main__':
    try:
        publish_diagnostics_data()
    except rospy.ROSInterruptException:
        pass

