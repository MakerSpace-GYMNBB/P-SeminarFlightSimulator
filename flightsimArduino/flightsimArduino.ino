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
  //readSerial();
  //convertPitch(pitch);
  //setEngineRoll(convertRoll(roll));
  

  

  delay(10); // war mal 100
}

int convertPitch(int pitchN){
  if(pitchN > 30){
    return 30;
  }
  else if(pitchN < -30){
    return -30;
  }
  else{
    return pitchN;
  }
}

int convertRoll(int rollN){
  if(rollN > 30){
    return 30;
  }
  else if(rollN < -30){
    return -30;
  }
  else{
    return rollN;
  }
}

void readGyro(){
  Vector normAccel = mpu.readNormalizeAccel();
  pitchG = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  rollG = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  //Serial.println(pitchG);
  //Serial.println(rollG);
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

void setEngineRoll(int roll){
  if(abs(roll - rollG) > 2){ // 2 degree tolerance
    if(roll - rollG > 0){
        rotate('r', 100);
    }
    else{
        rotate('l', 100);
    }
  }
  else{
    stop();
  }

}

/*void setEnginePitch(int pitch){
  if(abs(pitch - pitchG) > 2){ // 2 degree tolerance
    if(pitch - pitchG > 0){
        rotate('r', 100);
    }
    else{
        rotate('l', 100);
    }
  }
  else{
    stop();
  }

}*/

void testEngine(){
  rotate('r', 100);
  delay(5000);
  rotate('l', 100);
  delay(2500);
  rotate('l', 255);
  delay(2500);
  stop();
}
