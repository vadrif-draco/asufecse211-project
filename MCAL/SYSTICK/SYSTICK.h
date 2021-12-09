// Include Guard
#ifndef SYSTICK_H
#define SYSTICK_H

#include "../../tm4c123gh6pm.h"
#include "../../macros.h"
#include "../../types.h"
#include <stdint.h>

void SysTickDisable(void);
void SysTickEnable(void);
void SysTickPeriodSet(uint32 millis);
uint8 SysTickTimeout(void);

#endif // SYSTICK_H