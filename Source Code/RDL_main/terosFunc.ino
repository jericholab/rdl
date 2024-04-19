//-------------------------------------------------------------------
// FONCTION: terosFunc
// PURPOSE: Calculates the current value of the TEROS 10 soil humidity sensor, based on manufacturer VWC eq. and van genuchten equation (pressure)
// INPUT: none
// OUTPUT: none


void terosFunc(uint8_t channel){                                  

  digitalWrite(enable_V_MUX, LOW);               // toggle pin to LOW value in order turn on the V_MUX
  setMultiplexer(channel);                       // select the multiplexer channel
  pcf1.digitalWrite(channel, LOW);               // turn LED on by sinking current to ground
  pcf2.digitalWrite(channel, HIGH);              // turn LED on by sinking current to ground
  delay(500);
  
  bool readMode = 1;
  float sensorValue = getVoltFunc(readMode);           // read the voltage while assuming a 5000mV voltage reference
  float voltage1 = sensorValue * 1000;                 // conversion to millivolts to make it usable by the VWC eq.
  Serial.print("*");
  spacing2("*",12);      
  Serial.print(voltage1,2);                            //mVolts
  spacing1(voltage1,12);

  float VWC = 4.824E-10 * pow(voltage1,3) - 2.278E-06*pow(voltage1,2) + 3.898E-03*voltage1 - 2.154;  // Reference: TEROS 10 User Manual, Third-Order equation for mineral soils (does not apply to air or pure water).
  Serial.print(VWC,3);  //mVolts
  spacing1(VWC,11);  // since a bonus decimal is printed, the spacing requirement is reduced by one unit.

  pcf1.digitalWrite(channel, HIGH); //turn LED off by turning off sinking transistor
  pcf2.digitalWrite(channel, LOW);  //turn LED off by turning off sinking transistor

  //WATER TENSION CALCULATION
  
  float teta = VWC;           // Transfer TEROS value to phi
  float phi_result = calculatePhi(teta);  // calculate the water tension (phi) in Pascals.
  Serial.print (phi_result,1);  //mVolts
  spacing1(phi_result,13);
  }

  ///// WATER TENSION FUNCTION TETA (VAN GENUCHTEN EQUATION)

  float calculatePhi(float teta) {
      if (teta <0){
        teta = 0.001;            // Negative and zero values must be avoided
      }
      // Declare the parameters as constants or variables
      const float teta_r = 0.01; //0.131;      // Residual water content  (soil dependent value, dummy value for example)
      const float teta_s = 0.396;      // Saturated water content (soil dependent value, dummy value for example)
      const float alpha = 0.00423;     // Empirical parameter  (soil dependent value, dummy value for example)
      const float n = 2.06;            // Empirical parameter  (soil dependent value, dummy value for example)

      float m = (1 - (1 / n));          //unsure of the reference. there are multiple versions of m for the von gnuchten equation.
      float term1 = pow(teta_s / teta, (1 / m));
      float term2 = pow(term1 - 1, (1 / n));
      float phi = (1/ alpha) * term2; 
      return phi;
}
