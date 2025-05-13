#include <Wire.h>
#include <MPU6050.h>
#include <engineLibrary.h>

//engine  controller pins
#define RPWM_PIN 5
#define LPWM_PIN 6


MPU6050 mpu; //variables for gyro


int values[2];
int pitch;
int roll;
int pitchG;
int rollG;
String incomingString;

void setup() {

  initializeEngine(RPWM_PIN, LPWM_PIN);

  //initialize serial connection for gyro
  Serial.begin(9600);
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  testEngine();
}

void loop() {

  readGyro();
  readSerial();
  

  

  delay(10); // war mal 100
}


void readGyro(){
  Vector normAccel = mpu.readNormalizeAccel();
  pitchG = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  rollG = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
}
int splitString(String input, char delimiter, int output[], int maxParts) {
  int count = 0;
  int startIndex = 0;
  int delimIndex = input.indexOf(delimiter);
  

  while (delimIndex >= 0 && count < maxParts - 1) {


    
    output[count++] = input.substring(startIndex).toInt();
    startIndex = delimIndex + 1;
    delimIndex = input.indexOf(delimiter, startIndex);
  }

  // Add the last part
  output[count++] = input.substring(startIndex).toInt();
  return count;
}
void readSerial(){
  if (Serial.available() > 0) {

        incomingString = Serial.readStringUntil("\n");
        
        int count = splitString(incomingString, ';', values, 2);
        for (int i = 0; i < count; i++){
          Serial.println(values[i]);
        }
        pitch = values[0];
        roll = values[1];
  }
}

void testEngine(){
  rotate('r', 100);
  delay(5000);
  rotate('l', 100);
  delay(2500);
  rotate('l', 255);
  delay(2500);
  stop();
}
