#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <Arduino.h>

void wire_begin(void);
void wire_set_timeout(unsigned int amount, bool x);
bool wire_get_timeout_flag(void);
void wire_clear_timeout_flag(void);

#endif
