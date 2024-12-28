#include "stm32_wrapper_uart.h"

namespace OOPLayer{

class Serial{
	private:
			PinName Rxpin;
		  PinName Txpin;
   public:
	   // Constructor for Serial class with auto initialization
			Serial(PinName TxPin, PinName RxPin):Rxpin(RxPin),Txpin(TxPin){
				init_Rx_pin(RxPin);
				init_Tx_pin(TxPin);
				init_Usart();
			}
			
	   // Print function for Serial class prints a single character
			void Printchar(uint8_t data){
				SendChar(data);
			}
			
	  // Getchar function for Serial class, returns a single character
			uint8_t Getchar(){
				return ReadChar();
			}
	};
}
