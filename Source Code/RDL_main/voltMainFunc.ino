//-------------------------------------------------------------------
// FONCTION: voltMainFunc
// PURPOSE: Operate the 3 MUX to enable reading channels associated with analog sensors
// INPUT: none
// OUTPUT: none

int voltMainFunc(){

      digitalWrite(10, LOW);                          // toggle pin to LOW value in order turn on the A_MUX  (D10)
      Serial.print("*");
      spacing2("*",12);  
      for (int i=0; i< (8); i++) {   
        setMultiplexer(i);                            // select the multiplexer channel                   
        int channel = i+1;                            //channel being measured
        arrayV[i] = voltFunc();                        // storing voltages to array  
        delay(50);
      }
      digitalWrite(10, HIGH);                          // toggle pin to LOW value in order turn on the A_MUX  (D10)
        //int channel = i+1;                            //channel being measured

        //struct STRUCT1 valeurs = voltFunc();          //call function and store results in a structure
        //struct STRUCT1 valeurs = thermistor(arrayA[i], arrayB[i], arrayC[i],channel);   //call 'thermistor' function and store results in a structure
        //arrayV[i] = valeurs.t;                        // storing temperature to array
        //arrayR[i] = valeurs.o;                        // storing resistances (ohm) to array       
      //}   

    
    //digitalWrite(10, HIGH);                            // toggle pin to HIGH value in order turn off MUX while not used (avoid self-heating effect, MUX consumption)
    
//    for (int i=0; i< (numberC); i++) {               // print all probes temperature with a loop
//      Serial.print(arrayV[i],2);                     // print value from array with 2 decimals  
//      spacing(arrayV[i], 12);
//    }
        
}
  
      
