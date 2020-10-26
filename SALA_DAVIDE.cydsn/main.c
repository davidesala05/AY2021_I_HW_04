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
#include "project.h"
#include "InterruptRoutines_UART.h"
#include "InterruptRoutines_ADC.h"
#include "BulbSettings.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    ADC_DelSig_Start();
    UART_Start();
  
    isr_ADC_StartEx(Custom_ADC_ISR);
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
    Data[0] = HEADER;
    Data[5] = TAIL;
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        
        switch (state){
        
            case DARK :
                Set_BULB(value_pot);
                break;
            
            case LIGHT :
                UART_PutString("Buld powered ON\r\n");
                PWM_Stop();
                break;
            case ERROR :
                UART_PutString("ERROR in the transmission, character is unknown\r\n");
                UART_Init();
                state = IDLE;
                break;
            
            case STOP :
                UART_PutString("Bulb powered OFF\r\n");
                UART_Init();
                PWM_Stop();
                state = IDLE;
                break;

        }
        
        if(flag_send){
            UART_PutArray(Data, TRANSMIT_SIZE);
            flag_send = 0;
        }
    }
}

/* [] END OF FILE */
