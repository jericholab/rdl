#include "rtd_grav.h"
Gravity_RTD RTD = Gravity_RTD(A0);


uint8_t user_bytes_received = 0;
const uint8_t bufferlen = 32;
char user_data[bufferlen];


void parse_cmd(char* string) {
  strupr(string);
  String cmd = String(string);
  if(cmd.startsWith("CAL")){
    int index = cmd.indexOf(',');
    if(index != -1){
      String param = cmd.substring(index+1, cmd.length());
      if(param.equals("CLEAR")){
        RTD.cal_clear();
        Serial.println("CALIBRATION CLEARED");
      }else {
        RTD.cal(param.toFloat());
        Serial.println("RTD CALIBRATED");
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("Use command \"CAL,nnn.n\" to calibrate the circuit to a specific temperature\n\"CAL,CLEAR\" clears the calibration"));
  if(RTD.begin()){
    Serial.println("Loaded EEPROM");
  }
}

void loop() {

  if (Serial.available() > 0) {
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));
  }

  if (user_bytes_received) {
    parse_cmd(user_data);
    user_bytes_received = 0;
    memset(user_data, 0, sizeof(user_data));
  }
  
  Serial.println(RTD.read_RTD_temp_C());
  
  //uncomment for readings in F
  //Serial.println(RTD.read_RTD_temp_F()); 
  delay(500);

}
