%% SteinhartFun
%% This function contains the non-linear system made of three Steinhart-Hart equations
%% that will be solved by the non-linear solver called 'fsolve' in Steinhart_SinglePoint.m
  %Steinhart equation : 1/T = A + B*ln(R)+C*(ln(R))^3
  
function y = SteinhartFun (x,T1,T2,T3,R1,R2,R3)
  
  % T1, T2, and T3 represents the 3 calibration point known temperature (e.g. ice bath, room T, boiling bath)
  % R1, R2 and R3 represents the 3 measured resistance of the thermistor at T1, T2 and T3
  
  % Temperatures are received in Celcius and transformed to Kelvin
  T1K=T1+273.15;
  T2K=T2+273.15;
  T3K=T3+273.15;
  
    y = zeros (3, 1);
    y(1) = -1/T1K+x(1)+x(2)*log(R1)+x(3)*(log(R1))^3;
    y(2) = -1/T2K+x(1)+x(2)*log(R2)+x(3)*(log(R2))^3;
    y(3) = -1/T3K+x(1)+x(2)*log(R3)+x(3)*(log(R3))^3;
    
    
endfunction

  %Equations
  %x(1) = coefficient A
  %x(2) = coefficient B
  %x(3) = coefficient C

