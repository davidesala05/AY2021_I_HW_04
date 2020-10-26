/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "InterruptRoutines_UART.h"
#include "UART.h"
#include "Timer.h"
#include "LED_UART.h"


CY_ISR(Custom_UART_RX_ISR) {
    
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) {
        
        ch_received = UART_GetChar();
        
        switch(ch_received){
            
            case 'B':
            case 'b':
                Timer_Start();
                LED_UART_Write(HIGH);
                state = START;
                break;
            
            case 'S':
            case 's':
                Timer_Stop();
                LED_UART_Write(LOW);
                state = STOP;
                break;
            
            default:
                state = ERROR;
                break;
        }
    } 
}

/* [] END OF FILE */
