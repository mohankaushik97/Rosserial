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

void setup() {
  myservo.attach(4);
  myservo.write(0);
  node.initNode();
  node.advertise(range_pub);
  Serial.begin(57600);


}

void loop() {
  int count = 0;

  for (int pos = 0; pos <= 180; pos += 9) {
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
    Serial.print("distance = ");
    Serial.print(distance);
    Serial.print("       angle =");
    Serial.println(pos);
    ranges[count++] = distance;
    delay(100);
  }


  /*int pos = 0;    // variable to store the servo position
    int count = 0;
    while (pos <= 180) {
    myservo.write(pos);
    Serial.print("newangle = ");
    Serial.println(pos);
    pos = pos + 9;
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
    //Serial.println(pos);
    ranges[count++] = distance;
    delay(100);
    }
  */
  Serial.print("done");



  scan.header.frame_id = "laser_frame";
  scan.angle_min = 0;
  scan.angle_max = PI;
  scan.angle_increment = PI / 60;
  scan.time_increment = 0.2;
  scan.range_min = 0.0;
  scan.range_max = 200.0;
  scan.ranges = ranges;
  range_pub.publish(&scan);
  for (int i = 0; i <= 20; i++) {
    Serial.print(",");
    Serial.print(scan.ranges[i]);
  }
  node.spinOnce();

}
