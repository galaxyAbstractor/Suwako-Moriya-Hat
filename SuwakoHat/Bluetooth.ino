#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t prevState = ACI_EVT_DISCONNECTED;
unsigned long prevLEDtime = 0L; // For LED timing
char msg[21] = {0}; // BLE 20 char limit + NUL
uint8_t msgLen = 0; 


void Bluetooth() {
  BTLEserial.begin();
}

uint8_t readStr(char dest[], uint8_t maxlen) {
  int c;
  uint8_t len = 0;
  while((c = BTLEserial.read()) >= 0) {
    if(len < maxlen) dest[len++] = c;
  }
  return len;
}

unsigned long bluetoothLoop() {
 
  BTLEserial.pollACI();
  aci_evt_opcode_t state = BTLEserial.getState();
  
  if(state != prevState) {
    prevState = state;
  }
  
  if((state == ACI_EVT_CONNECTED) && BTLEserial.available()) {
    if(BTLEserial.peek() == 'a') { // select both eyes
      char eye[2];
      Serial.println("Eye set!!");
      readStr(eye, sizeof(eye));
      setEyes(eye[1] - '0'); // Took me too long to figure out >.<
    } else if(BTLEserial.peek() == 'b') { // left eye
      char eye[2];
      readStr(eye, sizeof(eye));
      setLeftEyeIndex(eye[1] - '0'); 
    } else if(BTLEserial.peek() == 'c') { // right eye
      char eye[2];
      readStr(eye, sizeof(eye));
      setRightEyeIndex(eye[1] - '0');
    } else if(BTLEserial.peek() == 'd') { // eyeMode
      char eyeMode[2];
      readStr(eyeMode, sizeof(eyeMode));
      
      // 0 static
      // 1 random
      
      Serial.println("Eye mode set!");
      if (eyeMode[1] - '0' == 0) {
        Serial.println("Set to false!");
        setRandomEyes(false);
      } else {
        Serial.println("Set to true!");
        setRandomEyes(true);
      }
    } else { // Not color, must be message string
      msgLen = readStr(msg, sizeof(msg)-1);
      msg[msgLen] = 0;
    }
  }
  
  return millis();
  
}

