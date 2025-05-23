#include <stdlib.h>
#include <engineLibrary.h>



String incomingString;
int values[2];
int pitch;
int roll;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //initializeEngine(int RPWM_PIN_new, int LPWM_PIN_new);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
        incomingString = Serial.readStringUntil("\n");

        //Serial.print("I get ");
        //Serial.println(incomingString);
        
        int count = splitString(incomingString, ';', values, 2);
        for (int i = 0; i < count; i++){
          Serial.println(values[i]);
        }
        pitch = values[0];
        roll = values[1];

        

  }
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

