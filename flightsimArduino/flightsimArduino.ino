#include <Wire.h>
#include <MPU6050.h>
#include <engineLibrary.h>

#define BTN_PIN 7  //engine  controller pins
#define RPWM_PIN 5
#define LPWM_PIN 6

unsigned long T1 = 0, T2 = 0;     //variables for engine
uint8_t TimeInterval = 5; // 5ms
bool Direction = 0;

MPU6050 mpu; //variables for gyro

int winkel = 30;

double pitch;
double roll;
String zwischenspeicher;
char incomingChar;

void setup() {


  initializeEngine(RPWM_PIN, LPWM_PIN);
  rotate('r', 100);
  delay(5000);
  rotate('l', 100);
  delay(2500);
  rotate('l', 255);
  delay(2500);
  stop();
  ;


  //initialize serial connection for gyro
  Serial.begin(115200);
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  //while(Serial.available() = 0)  {}
}

void loop() {

  readGyro();


  if(winkel - pitch > 0){
    //analogWrite(RPWM_PIN, )
  }

  delay(10); // war mal 100
}

/*void readSerial(){
  Serial.print("T");
  while((char)Serial.Read() != '&'){

  }

  zwischenspeicher = "";

  do{
    incomingChar = (char)Serial.read;
    zwischenspeicher = zwischenspeicher + incomingChar;
  }while(incomingChar != '%');

  pitch = zwischenspeicher.toDouble();
  zwischenspeicher = "";

  do{
    incomingChar = (char)Serial.read;
    zwischenspeicher = zwischenspeicher + incomingChar;
  }while(incomingChar != '§');
  
  roll = zwischenspeicher.toDouble();

}*/

void readGyro(){
  Vector normAccel = mpu.readNormalizeAccel();
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  Serial.print(pitch);
  Serial.print(" ");
  Serial.print(roll);
  Serial.println();
}
bool debounce(void){
  static uint16_t btnState = 0;
  btnState = (btnState<<1) | (!digitalRead(BTN_PIN));
  return (btnState == 0xFFF0);
}