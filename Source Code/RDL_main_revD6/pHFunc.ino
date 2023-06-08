
//-------------------------------------------------------------------
// FONCTION: pHFunc
// PURPOSE: Communicate with the pH meter and provide pH values
// INPUT: none
// OUTPUT: none

int pHFunc(){


      analogReference(DEFAULT);      //put the analog reference back to 5V to allow reading 0-5V signals
      delay(10);                     //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      int sensorValue;               //variable declaration
      for (int i= 1; i<5; i++){
        sensorValue = analogRead(PH_PIN);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
      }
      
      //temperature = readTemperature();         // read your temperature sensor to execute temperature compensation
      voltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage while assuming a 5000mV voltage reference
      phValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
      analogReference(EXTERNAL);     //put the analog reference back to 3.3V  
      //Serial.print(voltage,2);  //raw value from ADC based on probe voltage
      Serial.print("*"); 
      spacing2("*",12);   
      Serial.print(phValue,2);  // pH value
      spacing(phValue,11); 
      Serial.print(temperature,1); //temperature 
      spacing(temperature,11); 
        
        
        
    //ph.calibration(voltage,temperature);           // calibration process by Serail CMD   ////////// TEMPORARILY COMMENTED UNTIL I READ ABOUT IT.

    ////////////////////
    // I don't know what is SERAIL CMD. I don't know why calibration is done at every call. I don't know why calibration is done after the measurement
    // 
    /////////////////////
}
