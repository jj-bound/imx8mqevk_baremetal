#ifndef GPIO_H_
#define GPIO_H_

#include "common_type.h"

typedef enum
{
	GPIO1 = 0,
	GPIO2,
	GPIO3,
	GPIO4,
	GPIO5
} E_GPIO_GROUP;

typedef enum
{
	GPIO_IN = 0,
	GPIO_OUT,
} E_GPIO_DIR;

typedef enum
{
	GPIO_SPEED_SLOW = 0,
	GPIO_SPEED_MEDIUM,
	GPIO_SPEED_FAST,
	GPIO_SPEED_MAX,
} E_GPIO_SPEED;

typedef enum
{
	GPIO_DSE_HI_Z = 0,
	GPIO_DSE_255_OHM,
	GPIO_DSE_105_OHM,
	GPIO_DSE_75_OHM,
	GPIO_DSE_85_OHM,
	GPIO_DSE_65_OHM,
	GPIO_DSE_45_OHM,
	GPIO_DSE_40_OHM,
} E_GPIO_DSE;

typedef struct
{
	E_GPIO_GROUP eGpioGroup;
	E_GPIO_DIR eGpioDir;
	UINT8 ucGpioNum;
	UINT8 ucMuxMode;
	UINT8 ucIsPullUp;
	UINT8 ucIsOpenDrain;
	E_GPIO_SPEED eGpioSpeed;
	E_GPIO_DSE eGpioDse;
} T_GPIO_TYPEDEF;

#endif
