#include "stm32_wrapper_uart.h"
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

void init_Rx_pin(PinName RxPin){
	int gpioID = (RxPin & 0xF0) >> 4; 
	RCC_APB2PeriphClockCmd( 1<<(gpioID+2) , ENABLE);	
	GPIO_TypeDef* GPIOx = get_gpioport(RxPin);
	GPIO_InitStructure.GPIO_Pin = 1<<(RxPin & 0x0F);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void init_Tx_pin(PinName TxPin){
	int gpioID = (TxPin & 0xF0) >> 4; 
	RCC_APB2PeriphClockCmd( 1<<(gpioID+2) , ENABLE);	
	GPIO_TypeDef* GPIOx = get_gpioport(TxPin);
	GPIO_InitStructure.GPIO_Pin = 1<<(TxPin & 0x0F);
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void init_Usart(void){
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
  USART_Init(USART2 , &USART_InitStructure);
  USART_Cmd(USART2, ENABLE);
}

void SendChar(uint8_t data){
	USART_SendData(USART2, data);
	}

uint8_t ReadChar(void){
	return USART_ReceiveData(USART2)&0xFF;
	}

static GPIO_TypeDef* get_gpioport (PinName pin)
{
	int gpioID = (pin & 0xF0) >> 4; 
		
	GPIO_TypeDef* GPIOx;
	
	switch (gpioID){
		case 0x00: GPIOx=GPIOA; break;
		case 0x01: GPIOx=GPIOB; break;
		case 0x02: GPIOx=GPIOC; break;
		case 0x03: GPIOx=GPIOD; break;
		default: break;
		}
	return GPIOx;
}
