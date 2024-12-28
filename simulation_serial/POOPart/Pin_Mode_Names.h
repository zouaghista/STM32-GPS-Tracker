#ifndef __PIN_MODE_NAMES_H
#define __PIN_MODE_NAMES_H

typedef enum{
	
	PA_0=0x00,	PA_1=0x01, PA_2=0x02, PA_3=0x03,
	PA_4=0x04,	PA_5=0x05, PA_6=0x06,	PA_7=0x07,
	PA_8=0x08,	PA_9=0x09,	PA_10=0x0A,	PA_11=0x0B,
	PA_12=0x0C,	PA_13=0x0D,	PA_14=0x0E,	PA_15=0x0F,
	
	PB_0=0x10,	PB_1=0x11, PB_2=0x12, PB_3=0x13,
	PB_4=0x14,	PB_5=0x15, PB_6=0x16,	PB_7=0x17,
	PB_8=0x018,	PB_9=0x19,	PB_10=0x1A,	PB_11=0x1B,
	PB_12=0x1C,	PB_13=0x1D,	PB_14=0x1E,	PB_15=0x1F,

	PC_0=0x20,	PC_1=0x21, PC_2=0x22, PC_3=0x23,
	PC_4=0x24,	PC_5=0x25, PC_6=0x26,	PC_7=0x27,
	PC_8=0x28,	PC_9=0x29,	PC_10=0x2A,	PC_11=0x2B,
	PC_12=0x2C,	PC_13=0x2D,	PC_14=0x2E,	PC_15=0x2F,

}
PinName;

typedef enum{
	Floating=0,
	PullUp=1,
	PullDown=2,
	Analog=3,
	
	InDefault=Floating
}
PinInMode;

typedef enum{
	LowSpeed=0,
	MediumSpeed=1,
	HighSpeed=2,
	VeryHighSpeed=3,
	SpeedDefault=LowSpeed
}
PinSpeed;

typedef enum{
  PPull = 0,
  ODrain = 1,
  AF_PPull = 2,
  AF_ODrain = 3,
  OutDefault = PPull
} 
PinOutMode;



# endif //__PIN_MODE_NAMES_H
