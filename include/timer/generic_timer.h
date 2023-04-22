#ifndef ARM_GENERIC_TIMER
#define ARM_GENERIC_TIMER

int arm_generic_timer_init(void);

void udelay(unsigned int uiDelayUs);

void mdelay(unsigned int uiDelayMs);

int delay(unsigned int uiDelayS);

#endif