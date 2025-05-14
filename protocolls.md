## Protocolls
### Serial connection Arduino - PC
The data contains the pitch and yaw and is being sent in one line
Pitch and yaw are both represented by an integer and seperated by a ";" (semicolon)
The line containing the data is structured as follows
pitch;roll

### Engine Library
void initializeEngine(int RPWM_PIN_new, int LPWM_PIN_new)
void stop()
void rotate(char direction, int value)
- if direction is character 'r' the engine turns right, if direction is anything else, than the motor turns left
