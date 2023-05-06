/*
Arduino Uno 驱动HC-SR04 超声波测距传感器模块

使用Arduino Uno驱动HC-SR04超声波测距传感器模块
程序运行后，传感器将感应到的距离信息通过Arduino IDE的串口监视器显示。

接线方法:
HC-SR04 引脚 VCC 连接到 Arduino 引脚 +5VDC
HC-SR04 引脚 Trig 连接到  Arduino 引脚 11
HC-SR04 引脚 Echo 连接到  Arduino 引脚 12
HC-SR04 引脚 GND 连接到  Arduino 引脚 GND


This example code is in the public domain.

*/
 
int trigPin = 11;    //Trig
int echoPin = 12;    //Echo
long duration, cm, inches;
int redPin = 8;      //Red LED pin
int greenPin = 9;    //Green LED pin
int bluePin = 10;    //Blue LED pin
 
void setup() {
  //Serial Port begin
  Serial.begin(9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
 
void loop() {
 
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  inches = (duration/2) / 74; 

  if (cm < 10) {
    // Display red when distance is less than 20cm
    analogWrite(redPin, 200);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } else if (cm > 70) {
    // Display green when distance is greater than 50cm
    analogWrite(redPin, 0);
    analogWrite(greenPin, 200);
    analogWrite(bluePin, 0);
  } else {
    // Gradually change color for distances between 20cm and 50cm
    int redValue = map(cm, 10, 70, 200, 0);
    int greenValue = map(cm, 10, 70, 0, 200);
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, 0);
  }
  
  
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  
  
  delay(10);
}