// This include is necessary since we are not using a .ino extension
#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include "MeEncoderNew.h"
#include "ros.h"
#include "std_msgs/String.h"
// #include "std_msgs/Uint8.h"
#include "geometry_msgs/Twist.h"

#define ROS_MESSAGE_PUBLISHER "RACR_motors"

#define CE_PIN 7
#define CSN_PIN 8
#define DEBUG_ON 1

// unit is meter
#define WHEEL_RADIUS 0.076
#define WHEEL_SEPARATION_WIDTH 0.2
#define WHEEL_SEPARATION_LENGTH 0.2

// NOTE: LL = LongLong type
const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
uint16_t joystick[4];

MeEncoderNew motor1(0x09, SLOT1); //  motor1 at slot1
MeEncoderNew motor2(0x09, SLOT2); //  motor2 at slot2
MeEncoderNew motor3(0x0a, SLOT1); //  motor3 at slot1
MeEncoderNew motor4(0x0a, SLOT2); //  motor4 at slot2

ros::NodeHandle nh;

void moveTwist(geometry_msgs::Vector3 linear, geometry_msgs::Vector3 angular)
{
  float lx = linear.x;
  float ly = linear.y;
  float az = angular.z;
  float motor1Speed = (1 / WHEEL_RADIUS) * (lx + ly + (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH) * az);
  float motor2Speed = (1 / WHEEL_RADIUS) * (lx - ly - (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH) * az);
  float motor3Speed = (1 / WHEEL_RADIUS) * (lx + ly - (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH) * az);
  float motor4Speed = (1 / WHEEL_RADIUS) * (lx - ly + (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH) * az);
  motor1.runSpeed(motor1Speed);
  motor2.runSpeed(-motor2Speed);
  motor3.runSpeed(-motor3Speed);
  motor4.runSpeed(motor4Speed);
  float motor1SpeedGet = motor1.getCurrentSpeed();
  float motor2SpeedGet = motor2.getCurrentSpeed();
  float motor3SpeedGet = motor3.getCurrentSpeed();
  float motor4SpeedGet = motor4.getCurrentSpeed();
#if DEBUG_ON
  Serial.println(lx);
  Serial.println(ly);
  Serial.println(az);
  Serial.println(motor1Speed);
  Serial.println(-motor2Speed);
  Serial.println(-motor3Speed);
  Serial.println(motor4Speed);
  Serial.println(motor1SpeedGet);
  Serial.println(motor2SpeedGet);
  Serial.println(motor3SpeedGet);
  Serial.println(motor4SpeedGet);
#endif
}

void messageCb(const geometry_msgs::Twist &control_msg)
{
  moveTwist(control_msg.linear, control_msg.angular);
}

std_msgs::String str_msg;

// ros::Publisher chatter("chatter", &str_msg);
ros::Subscriber<geometry_msgs::Twist> sub(ROS_MESSAGE_PUBLISHER, &messageCb);

char hello[13] = "hello world!";

void setup()
{
  Serial.begin(9600);

  motor1.begin();
  motor2.begin();
  motor3.begin();
  motor4.begin();

  nh.initNode();
  // nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{
  // str_msg.data = hello;
  // chatter.publish( &str_msg );
  nh.spinOnce();
  delay(50);
}
