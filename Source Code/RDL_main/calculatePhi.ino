//-------------------------------------------------------------------
// FONCTION: calculatePhi
// PURPOSE: calculate water tension based on water content
// INPUT: teta
// OUTPUT: phi
  
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
