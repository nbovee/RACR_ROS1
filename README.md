# Rowan Autonomous Car Research:

Robotic platform for the testing of edge computing in neural networks.

## Installation on Jetson:
### Jetson Setup
1) Install the latest version of Jetpack for the hardware from the Nvidia SDK manager
2) Enable auto-login in Ubuntu settings
3) (potential adjust udev rules?)
4) Install git and docker
5) Clone this repository
6) Build and start the docker container with `./build.sh`

#### Attribution:
The starting point of much of our code was based upon code provided by WSU under the MIT license with delivery of the initial robot. It has since been upgraded and modified to suit our purposes.

<hr>

## Previous Readme, cleanup as needed:

### Common Setup
1) Follow the steps in `79-robot.rules.md` to enable the correct UDEV Rules for both follower and guidance robot
    - This only needs to be done once (reboot both after doing so)
2) Run `source usbsetup.sh` on *both* machines (run this every time on startup or set it as a Cron job)

**SSH Setup:**
It is recommended to not have either the Jetson or Raspberry Pi connected via HDMI while it is moving (for obvious reasons). You can use a separate computer (any OS) or a Linux one with ROS installed (melodic or noetic) to use RVIZ and other utilities. 

1) Get the IP Address of each machine and note it down by running `ifconfig` and checking the `inet` entry under `wlan0`. Ensure that each robot's computer is set to autologin, and you can disconnect and you should not have to connect again.
2) Using the central computer (neither of the robots), edit `/etc/hosts` (or your OS's equivalent) to give a name to each computer (I used `jetson` and `raspberrypi`)
3) Run `ssh [username]@[computer_name]` for each robot in a new terminal window (ex: `ssh nvidia@jetson`)
4) Set the environment variable of `$ROS_IP` on **ALL MACHINES** (including remote computer) to their respective IPs
5) On all machines except the Master/Guidance robot, add the master robot to the list in `/etc/hosts`
6) On all machines except the Master/Guidance robot, set the environment variable of `$ROS_MASTER_URI` to `http://[computer_name]:11311` (ex: `http://jetson:11311`)
    - You should put the commands for steps 4 and 6 in the `.bashrc` or your shell's run configuration file to run every time a shell is opened. 

## Running FollowMe:
1) Complete all installation and common setup steps above.
2) Run `roslaunch robot robot.launch` on the **guidance** robot and `roslaunch follower_robot robot.launch` on the **follower** robort
3) In a separate terminal on the master robot, run `rosrun robot followme.py`
4) Open RVIZ on the remote computer (you can use the config included in `rviz/main.rviz`), specify a Nav goal, and watch the master robot navigate while the follower robot follows it. 


## If not using FollowMe:
These steps are how to run basic demos of the various sensors and motors across the robot. These are outdated if you plan on using FollowMe and the setup described in `79-robot-rules.md`.

### setup for lidar:
```sh
sudo chmod 666 /dev/ttyUSB0
roslaunch rplidar_ros rplidar_s1.launch
```

### setup for motor
```sh
sudo chmod 777 /dev/ttyUSB0
roslaunch chip_bldc_driver example.launch
```

### Demos

#### Realsense Camera Demos:
Start the camera node:
`roslaunch realsense2_camera rs_camera.launch initial_reset:=true enable_gyro:=true enable_accel:=true align_depth:=true filters:=pointcloud`

Object Detection and Distance Estimation
```sh
# start the inferencing node
rosrun ros_deep_learning detectnet /dettnet/image_in:=/camera/color/image_raw
rosrun camera detectdepth.py
```

Heading Tracking with IMU:
`rosrun camera heading.py`

SLAM-type Mapping (doesn't work very well) using heading
```sh
rosrun camera mapper.py
rviz
```

#### RPLidar Demos:
Start with:
```sh
roslaunch rplidar_ros rplidar_s1.launch
```

Single revolution plotted as a map:
`rosrun lidar single_map.py` 

Multi Object Detection:
```sh
rosrun lidar pointcloud.py
rosrun multi_object_tracking_lidar kf_tracker
rviz
```

#### Any of the motor demos:
```sh
rosrun chip_bldc_driver bldc_driver_node
rosrun motor [stepper.py, rpm.py etc.]
```
