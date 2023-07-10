#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import os
import shutil

# Directory to store the received images within the container
IMAGE_DIRECTORY = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'Images')

def image_callback(msg):
    try:
        # Convert the ROS image message to OpenCV format
        cv_bridge = CvBridge()
        cv_image = cv_bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')

        # Create a unique filename based on the current timestamp
        filename = os.path.join(IMAGE_DIRECTORY, 'image_'+str(rospy.Time.now())+'.jpg')

        # Save the image to the container directory
        cv2.imwrite(filename, cv_image)

        print("Image saved: {}".format(str(filename)))

    except Exception as e:
        print("Error processing the image: {}".format(str(e)))

def subscribe_to_image_topic():
    rospy.init_node('image_subscriber', anonymous=True)
    rospy.Subscriber('/camera/color/image_raw', Image, image_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        if not os.path.exists(IMAGE_DIRECTORY):
            os.makedirs(IMAGE_DIRECTORY)
        subscribe_to_image_topic()
    except rospy.ROSInterruptException:
        pass


