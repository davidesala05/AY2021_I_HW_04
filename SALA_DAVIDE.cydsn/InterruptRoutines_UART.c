/* ========================================
 *
 * In this isr of the UART the character received is used to power ON or OFF the system
 * Moreover, a status LED is switched ON (UART is trasmitting) or OFF (UART is silent)
 * 
 * ========================================
*/

#include "InterruptRoutines_UART.h"

CY_ISR(Custom_UART_RX_ISR) {
    
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) {
        
        ch_received = UART_GetChar(); //The character's value is saved
        
        switch(ch_received){
            
            case 'B':
            case 'b':
                state = ON; //State used in the main to start all the components
                break;      //and switch ON the LED status of the UART
            
            case 'S':
            case 's':
                state = OFF; //State used in the main to stop all the components,
                break;       //initialize the UART and switch OFF the LED status of the UART
            
            default:
                break;
        }
    } 
}

/* [] END OF FILE */
