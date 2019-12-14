#include <ros.h>
#include <sensor_msgs/LaserScan.h>
#include <Servo.h>

Servo myservo;
ros::NodeHandle node;
sensor_msgs::LaserScan scan;
ros::Publisher range_pub("/ultrascan", &scan);

//define constants
const int trigPin = 2;
const int echoPin = 2;
const int maxD = 200;


// define variables
float duration;
float distance;
float ranges[20];
int count = 0;
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(3);
  node.initNode();
  node.advertise(range_pub);
  Serial.begin(57600);
  scan.header.frame_id = "laser_frame";
  scan.angle_min = 0;
  scan.angle_max = PI;
  scan.angle_increment = PI / 60;
  scan.time_increment = 0.2;
  scan.range_min = 0.0;
  scan.range_max = 200.0;
}

void loop() {
  for (pos = 0; pos <= 180; pos += 3) {
    count += 1;
    myservo.write(pos);
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    scan.ranges[count] = distance;
    Serial.print("newangle = ");
    Serial.println(pos);
    delay(100);
  }
  range_pub.publish(&scan);
  node.spinOnce();

}
