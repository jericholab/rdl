
// wrapper lib
// if it detects the board it triggers macros to change libs or version of 
// it will return error if the board is unsupported and support will have to be provided
// You can check detected hardware with BOARD_NAME

#include "z_TEST_Sketch.h"
#include <Arduino.h>

#ifdef ARDUINO_AVR_UNO 
#include<Wire.h>
      void wire_begin(void){
            Wire.begin(); 
      }
      void wire_set_timeout(unsigned int amount, bool x){
            Wire.setWireTimeout(amount, x); 
      }
      bool wire_get_timeout_flag() {
            return Wire.getWireTimeoutFlag();
      }
      void wire_clear_timeout_flag(){
            Wire.clearWireTimeoutFlag();
      }
#elif defined(__AVR_ATmega4809__)
#include<Wire.h>

      void wire_begin(void){
            Wire.begin(); 
      }
      void wire_set_timeout(unsigned int amount, bool x){
            Wire.setTimeout(amount);
      }
      //doesn't have a timeout flag
      bool wire_get_timeout_flag() {
            return false;
      }
      void wire_clear_timeout_flag(){
      }
#else
      #error "Unsupported board target!"
#endif


