/* ========================================
 *
 * This is the header file of the interrupt of the UART
 * The UART isr is called every time a character is send on the serial port
 * 
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_UART_H
    
    #define __INTERRUPT_ROUTINES_UART_H
    
    #include "cytypes.h"
    #include "Global.h"
    #include "project.h"
    
    CY_ISR_PROTO(Custom_UART_RX_ISR);
    
#endif

/* [] END OF FILE */
