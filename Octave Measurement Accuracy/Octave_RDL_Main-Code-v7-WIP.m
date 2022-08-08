% TDL Octave Main Code
% Version 7.0
% Written by Frederic Coulombe.
% Copyright 2022 Jericho Laboratory inc.
% This program is free software: you can redistribute it and/or modify it under 
% the terms of the GNU General Public License as published by the Free Software 
% Foundation, either version 2 of the License, or (at your option) any later version.
% This program is distributed in the hope that it will be useful, but WITHOUT 
% ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
% FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
% You should have received a copy of the GNU General Public License along with 
% this program. If not, see <https://www.gnu.org/licenses/>. 

% This code calculates the performance of the TDL device
% This code will do the following things:
% Part 1- evaluate the resistance range that device can measure (print)
% Part 2- evaluate the resolution as a function of the resistance measured (graph)
% Part 3- evaluate the measurement temperature as a function of resistance (Steinhart-Hart equation) (graph)
% Part 4- evaluate the resistance as a function of temperature (reverse Steinhart-Hart equation) (graph)
% Part 5- evaluate the temperature measurement total uncertainty and its components (graph)
% The uncertainty calculation is based on error propagation.
% Three uncertainties are considered: analog-to-digital converter, series resistor and thermistor
% Reminder: Steinhart equation: 1/T = A + B*ln(R)+C*(ln(R))^3

% TO DO LIST
% terms 3 does not provide same result as annex
% how does the bath temperature uncertainty will affect the end user uncertainty ? the steinhart equation allows us to calculate
% the exact curve that goes through the three calibration point. so at 0C, the uncertainty is the absolute uncertainty of the bath..
% ... plus the uncertainty of the ADC and the uncertainty of the series resistor. %But what is the error in between the points?
% should we assume linear function of the uncertainty ?

close all; %close all windows
clear all; %erase all variables in memory
clc; %clean command window

% - - - - - - - - - - - - - - - - - - - - - - 
% INPUT DATA
%(comes from the results of a calibration test and the design characteristics)

A = 1.1009515911e-03; %Steinhart-Hart coefficient A
B = 2.3870548321e-04; %Steinhart-Hart coefficient B
C = 6.9761855776e-08; %Steinhart-Hart coefficient C
bit=10; %Number of bit for the Arduino's Analog-to-Digital Converter (ADC) (e.g. 10-bit ADC)
bits=2^bit; % Number of values possible with the given ADC
Vcc=3.3; %V %reference voltage of the ADC (external reference)
Rs= 10000; %ohm  %electrical resistance value of series resistance in voltage divider circuit
Rs_uncertainty = 0.001; %fraction
R_uncertainty=0.01; %fraction


% Hence ADC value 0 is associated with 0V and max ADC value (ex: 1023) is associated with Vcc (ex: 3.3V)
% The ADC has a linear relationship with input voltage

% - - - - - - - - - - - - - - - - - - - - - - 

%define the indepedent value vector (ADC)
bit_min=1;  %we are not interested in the firsts bit (0) (zero resistance)
bit_max=(bits-1)-1; %we are not interested in the last bit (infinite resistance)
rangeA=bit_max-bit_min;  
vector_ADC=linspace(bit_min,bit_max,rangeA+1)';  % transform into a column vector

%define the voltage vector
vector_voltage=zeros(rangeA+1,1);
function Result = voltage(ADC,VRef,bits);
  Result = ADC/(bits-1)*VRef;
endfunction
for i=bit_min:bit_max
  vector_voltage(i)=voltage(i,Vcc,bits);
endfor

%define the resistance vector
vector_resistance=zeros(rangeA+1,1);
function Result = resistance(V,Rs,Vcc)
  Result=(Rs*V)/(Vcc-V);
endfunction
for i=bit_min:bit_max
  vector_resistance(i)=resistance(vector_voltage(i),Rs,Vcc);
endfor

%define the temperature vector
vector_temperatureK=zeros(rangeA+1,1);
function Result=temperature(A,B,C,R)
  Result=1/(A + B*log(R)+C*(log(R))^3); %K %Temperature from Steinhart equation
endfunction
for i=bit_min:bit_max
  vector_temperatureK(i)=temperature(A,B,C,vector_resistance(i)); %kelvin
  vector_temperatureC=vector_temperatureK-273.15;
endfor
% - - - - - - - - - - - - - - - - - - - - - - 
% PART 0: Start a results matrix (bit, resistance, voltage, temperature, resolution, etc)

matResults=vector_ADC;   %create matrix A progressivement;
matResults(:,2)=vector_resistance; 
matResults(:,3)=vector_voltage;
matResults(:,4)=vector_temperatureC; 

% - - - - - - - - - - - - - - - - - - - - - - 
%PART 1: Evaluate the resistance range that the device can measure (print)

voltage_min=vector_voltage(1);  
voltage_max=vector_voltage(end);
R_min=vector_resistance(1);
R_max=vector_resistance(end);
T_min=vector_temperatureC(end);
T_max=vector_temperatureC(1);

fprintf('Bit_min = %d \r\n',bit_min)   %formatted output
fprintf('Bit_max = %d \r\n',bit_max)
fprintf('Voltage min = %.3f V\r\n',voltage_min)
fprintf('Voltage max = %.3f V\r\n',voltage_max)
fprintf('Resistance min = %.1f ohm \r\n',R_min)
fprintf('Resistance max = %.0f ohm \r\n',R_max)
fprintf('Temerature min = %.0f C\r\n',T_min)
fprintf('Temperature max = %.0f C\r\n',T_max)
fprintf('\r\n')

% - - - - - - - - - - - - - - - - - - - - - - 
% Part 2a: Evaluate the resistance resolution as a function of the resistance measured (graph)

x1 = vector_resistance(2:end);
x2 = vector_resistance(1:end-1);
res_R = x1-x2;  %resolution vector for resistance

figure(1)
subplot(2,3,1); 
loglog(x1, res_R)  %plot temperature as a function of resistance
grid on;
title('Resistance measurement resolution as a function of resistance')
xlabel('Resistance (Ohm))')
ylabel('Measurement resolution (Ohm))')

% - - - - - - - - - - - - - - - - - - - - - - 
% Part 2b: Evaluate the temperature resolution as a function of the temperature measured (graph)

x3 = vector_temperatureC(2:end);
x4 = vector_temperatureC(1:end-1);
res_T = x4-x3;  %resolution vector for resistance

subplot(2,3,2); 
semilogy(x3, res_T)  %plot temperature as a function of resistance
grid on;
title('Temperature measurement resolution as a function of temperature')
xlabel('Temperature (oC))')
ylabel('Temperature resolution (oC))')
% - - - - - - - - - - - - - - - - - - - - - - 
% Add the resolution vector to the matrix for result
res_T(length(res_T)+1)=0;  %modify res_T to obtain a vector of the right length
matResults(:,5) = res_T;
matResults

% - - - - - - - - - - - - - - - - - - - - - - 
% Part 3: Plot temperature as a function of resistance
subplot(2,3,3); 
semilogx(vector_resistance,vector_temperatureC)  %plot temperature as a function of resistance
title('Steinhart-Hart Equation: Temperature as a function of resistance')
xlabel('Resistance (Ohm))')
ylabel('Temperature (oC))')
grid on;

%define the temperature vector
%vector_T_resolution=zeros(rangeA+1,1);   %since the resolution varies, we take the largest value of the two
%function Result = resolutionT(T1,T2,T3)
vectorA=vector_temperatureC(2:end);
vectorB=vector_temperatureC(1:(end-1));
vector_T_resolution=vectorB-vectorA;



%----------
%OLD PART ---- A LOT OF USEFUL STUFF TO REUSE (TERM1, 2,3,4)


%define the analyzed range
T_min=0;  %C
T_max=100; %C
kk=30; %we want to plot a certain number of points on this curve (T,R) 
T_vectorC=linspace(T_min,T_max,kk); %temperature vector will be reused through the script
M=zeros(kk,5); %create an empty matrix M for storing results

% Steinhart reverse equation (resistance as a function of temperature in Celcius)
function R= Stein_rev(A,B,C,T) 
T=T+273.15;
X=(A-1/T)/C;  
Y=sqrt((B/(3*C))^3+(X^2)/4);
R=exp((Y-(X/2))^(1/3) - (Y+(X/2))^(1/3));
end

%First graph (Reverse steinhart equation)
% en meme temps creer le vecteur de Resistance qui seront utilisées à partir de la palge de température
for i=1:kk
R_test(i)=Stein_rev(A,B,C,T_vectorC(i));
end

%Figure (1): plot results for the reverse steinhart equation as verification
%figure(1)
subplot(2,3,4)
plot(T_vectorC,R_test,'-') %plot result from reverse Steinhart equation
title('Steinhart-Hart reverse equation: Resistance as a function of temperature')
xlabel('Temperature (oC)')
ylabel('Resistance (ohm))')
grid on;

% Main iteration loop for calculating the uncertainty curve
for i=1:kk %
R1=R_test(i);

% TERM 1: Thermistor uncertainty (dT/dR)
delR=10; %ohm %increment dR pour calculer la derive centrale numerique de la fonction dT/dR
R2a=R1-delR; %ohm % Resistance at point 2a (point before R)
T2a=1/(A + B*log(R2a)+C*(log(R2a))^3); %K %Temperature at point 2 from Steinhart equation
R2b=R1+delR; %ohm %Resistance at point 2b (point after R)
T2b=1/(A + B*log(R2b)+C*(log(R2b))^3); %K %Temperature at point 3 from Steinhart equation
dT_dR= (T2b-T2a)/(R2b-R2a); % derivative of steinhart function at a given temperature

% TERM 2: Analog-to-digital converter (ADC) uncertainty (dT/dADC)
V1=R1*Vcc/(R1+Rs); %V  %tension across thermistor at given temperature T1
dR_dV=(Rs*Vcc)/(Vcc-V1)^2; %
dV_dADC=Vcc/(bits-1); % 
dT_dADC = dT_dR*dR_dV*dV_dADC; %

% TERM 3: Series resistance (Rs) uncertainty (dT/dRs)
dV_dRs=-R1*Vcc/(R1+Rs)^2;   % this equation was reverified, redeveloped in 2019. it was okay.
dT_dRs=dT_dR*dR_dV*dV_dRs;  

% OVERALL UNCERTAINTY (Propagation of error by combining terms 1, 2 and 3)
dADC=1; % absolute uncertainty of ADC value (By definition, uncertainty on ADC reading is 1 unit)
dRs=Rs_uncertainty*Rs; %ohm %absolute uncertainty of series resistance, based on manufacturer accuracy in percentage
dR=R_uncertainty*R1; %ohm %absolute uncertainty of thermistor, based on manufacturer accuracy in percentage
dT1=abs(dT_dADC*dADC); %C %uncertainty caused by the ADC
dT2=abs(dT_dRs*dRs); %C %uncertainty caused by the series resistance
dT3=abs(dT_dR*dR); %C %uncertainty caused by the thermistor
dT=sqrt((dT1)^2+(dT2)^2 + (dT3)^2); %C Global uncertainty on temperature measurement
M(i,1)=T_vectorC(i);
M(i,2)=dT1;
M(i,3)=dT2;
M(i,4)=dT3;
M(i,5)=dT;
end

%Printing results
fprintf("        T         dT_ADC       dT_Rs       dT_R       dT \n")
disp(M)

%Figure (5): Plotting uncertainty results

subplot(2,3,5); 
plot(M(:,1),M(:,2),'-')
title('Measurement uncertainty components as a function of temperature')
xlabel('Temperature (oC)')
ylabel('Uncertainty (oC))')
grid on;
hold on;
plot(M(:,1),M(:,3),'-') 
plot(M(:,1),M(:,4),'s')
plot(M(:,1),M(:,5),'-o')
legend show
legend('ADC','Rs','R','Total')


