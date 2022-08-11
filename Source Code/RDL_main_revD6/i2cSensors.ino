//-------------------------------------------------------------------
// FONCTION: i2cSensors
// INPUT: none
// OUTPUT: none

int i2cSensors(){

//AM2301b digital humidity and temperature sensor

    sensors_event_t humidity, temp;                              //define two events (objects)
      
if(AHT_present == 1){
    aht.getEvent(&humidity, &temp);                              //populate temp and humidity objects with fresh data
    Serial.print(temp.temperature);                              //print the temperature
    spacing(temp.temperature,12); 
    Serial.print(humidity.relative_humidity);                    //print the relative humidity
    spacing(humidity.relative_humidity,12);
}

else{
    Serial.print("0.00");                              //print the temperature
    spacing2("0.00",12); 
    Serial.print("0.00");                               //print the relative humidity
    spacing2("0.00",12);
}
  }
