/*
 * LAB Name: Arduino DC Motor Control With BTS7960 Driver
 * Author: Khaled Magdy
 * For More Info Visit: www.DeepBlueMbedded.com
*/
#define BTN_PIN 7
#define RPWM_PIN 5 //turn right pin
#define LPWM_PIN 6 //turn left  pin
 
unsigned long T1 = 0, T2 = 0;
uint8_t TimeInterval = 5; // 5ms
bool Direction = 0;
 
void setup() {
  pinMode(BTN_PIN, INPUT);
  pinMode(RPWM_PIN, OUTPUT);
  pinMode(LPWM_PIN, OUTPUT);
  analogWrite(RPWM_PIN, 0);
  analogWrite(LPWM_PIN, 0);
}
 
void loop() {
  T2 = millis();
  if( (T2-T1) >= TimeInterval) // Every 5ms
  {
    // Read The Direction Control Button State
    if (debounce()) {
      Direction = !Direction; // Toggle Rotation Direction
    }
    // Read The Potentiometer & Control The Motor Speed (PWM) + Direction
    if(Direction)
    {
      analogWrite(RPWM_PIN, (analogRead(A0)>>2));
      analogWrite(LPWM_PIN, 0);
    }
    else
    {
      analogWrite(LPWM_PIN, (analogRead(A0)>>2));
      analogWrite(RPWM_PIN, 0);
    }    
    T1 = millis();
  }
}
 
bool debounce(void)
{
  static uint16_t btnState = 0;
  btnState = (btnState<<1) | (!digitalRead(BTN_PIN));
  return (btnState == 0xFFF0);
}