#include "stm32f10x.h"
#include "Pin_Mode_Names.h"

#ifndef __STM32_WRAPPER_UART_H
#define __STM32_WRAPPER_UART_H

#ifdef __cplusplus
extern "C" {
#endif
/* init functions */
	void init_Rx_pin(PinName RxPin); //initialiazes Rx pin for USART2 in Input Floating mode
	void init_Tx_pin(PinName TxPin); //initialiazes Tx pin for USART2 in Alternate Function Push Pull mode
	void init_Usart(void); //initialiazes USART2 with 9600 baud rate, 8 data bits, 1 stop bit, no parity, no flow control, RX/Tx mode
/* Read/Write functions*/
	void SendChar(uint8_t data); //sends a character through USART2
	uint8_t ReadChar(void); //reads a character from USART2
	
	
/* Common Function : To get GPIOx From PinName Value */
	static GPIO_TypeDef* get_gpioport (PinName pin);
	
#ifdef __cplusplus
}
#endif


#endif //__STM32_WRAPPER_UART_H
