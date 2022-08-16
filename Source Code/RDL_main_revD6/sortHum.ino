//-------------------------------------------------------------------
// FONCTION NAME: illuminance
// PURPOSE: Sort the humidities by analyzing the 'humidities' vector and creating couples (dry & wet). arrayH vector in the format ("db1,wb1,db2,wb2,db3,wb3,db4,wb4")
// INPUT: none
// OUTPUT: nnone

int sortHum(){
    
    for (int i=0; i<sizeof(humidities); i++){      
      if (humidities[i]=='A'){
        sortedHum[0]= i;
      }
      if (humidities[i]=='B'){
        sortedHum[2]= i;
      }
      if (humidities[i]=='C'){
        sortedHum[4]= i;
      }
      if (humidities[i]=='D'){
        sortedHum[6]= i;
      }
      if (humidities[i]=='1'){
        sortedHum[1]= i;
      }
      if (humidities[i]=='2'){
        sortedHum[3]= i;
      }
      if (humidities[i]=='3'){
        sortedHum[5]= i;
      }
      if (humidities[i]=='4'){
        sortedHum[7]= i;
      }
    }
}

//-------------------------------------------------------------------
