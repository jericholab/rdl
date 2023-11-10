
//-------------------------------------------------------------------
// FONCTION: pHFunc
// PURPOSE: Communicate with the pH meter and provide pH values
// INPUT: none
// OUTPUT: none

void pHFunc(){

//      delay(10);                     //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      int sensorValue;               //variable declaration
//      for (int i= 1; i<5; i++){
//        sensorValue = analogRead(PH_PIN);   // multiple readings are required to let the PMU/ADC adapt to the new voltage reference
//      }

      digitalWrite(enable_V_MUX, LOW);                          // toggle pin to LOW value in order turn on the V_MUX
      delay(100);                                    //delay is recommended by Arduino Reference doc to allow ADC to adjust its tension.
      setMultiplexer(5);                             // select the multiplexer channel                   
      delay(100);
      Serial.print("*");
      spacing2("*",12); 
      float voltage = voltFunc();  // read the voltage while assuming a 5000mV voltage reference
      Serial.print(voltage);  //////temporary test  
      spacing(voltage,12);     
      Serial.print(ph.readPH(voltage,25)); // temporary test  

      //spacing(phValue,12); 
      //voltage = analogRead(PH_PIN)/1024.0*5000;  // read the voltage while assuming a 5000mV voltage reference
      //float phValue = ph.readPH(voltage,25);  // temporary commented //convert voltage to pH with temperature compensation disabled (fixed value of 25C)
      //float voltage = voltFunc();
      //float voltage = voltFunc();
      //float voltage = voltFunc();
      //float voltage = voltFunc();
        
        
    //ph.calibration(voltage,temperature);           // calibration process by Serail CMD   ////////// TEMPORARILY COMMENTED UNTIL I READ ABOUT IT.

    ////////////////////
    // I don't know what is SERAIL CMD. I don't know why calibration is done at every call. I don't know why calibration is done after the measurement
    // 
    /////////////////////
}
