#ifndef CURRENT_COEFFICIENTS_H
#define CURRENT_COEFFICIENTS_H

float current_offset[8] = {2.4874, 2.5000, 0, 0, 0, 0, 0, 0};   //// TAMURA current sensor output value when null current for channels 1-8
uint8_t current_T_channel[8] = {1, 1, 0, 0, 0, 0, 0, 0};        //// Temperature channel associated with the current sensor temperature compensation probe
int current_T_ref[8] = {31, 21, 0, 0, 0, 0, 0, 0};              ////  Reference temperature [C] at which the tamura sensor null current was measured (temperature compensation)  

#endif // CURRENT_COEFFICIENTS_H