% Steinhart_SinglePoint
% This code works well. It requires the function file called SteinhartFun.m

% To-Do-List

close all; %close all windows
clear all; %erase all variables in memory
clc; %clean command window

% Input data for calibration
T1=0.00; %[C] %Celcius are converted to K in SteinhartFun function
T2=36.14; %[C]
T3=99.88; %[C]
R1=27417; %[ohm]
R2=6702; %[ohm]
R3=975; %[ohm]

% wrapper function allows feeding constants (e.g. T1) to the function SensorFun
wrapperFun = @(T1,T2,T3,R1,R2,R3) @(x) SteinhartFun(x,T1,T2,T3,R1,R2,R3); 

% SteinhartFun is used to create a homogeneous non-linear system (verify)
% fsolve is an Octave native function for solving a system of non-linear equations (verify)
% fsolve (FCN, X0, OPTIONS)
% "TolX" specifies the termination tolerance in the unknown variables, while "TolFun" is a tolerance for equations
% Default tolerance of solver is '1e-7' for both "TolX" and "TolFun"
x0 = [0 0 0]; %initial guess for non-linear solver called fsolve
[x, fval, info] = fsolve( wrapperFun(T1,T2,T3,R1,R2,R3), x0);

%printf("Validation data from Stanford Research System.\r\n")
%printf("T1 5 oC  R1 25000 ohm.\r\n")
%printf("T2 25 oC R2 10000 ohm.\r\n")
%printf("T3 45 oC R3 4000 ohm.\r\n")
%printf("A= 2.108508173 e-3.\r\n")
%printf("B= 0.7979240727 e-4.\r\n")
%printf("C = 6.535076315 e-7.\r\n")
%printf(" \r\n")
printf("Coefficients from Jericho program.\r\n")
printf("A = %10.10e\r\n",x(1))
printf("B = %10.10e\r\n",x(2))
printf("C = %10.10e\r\n",x(3))
printf("\r\n")
fval %FVAL contains the value of the function FCN evaluated at X (i.e. residuals)
info % a number code gives status. '1' means 'converged to specified tolerance'