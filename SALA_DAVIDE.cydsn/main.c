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
    
    UART_Start();
  
    isr_ADC_StartEx(Custom_ADC_ISR);
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
    Data[0] = HEADER;
    Data[TRANSMIT_SIZE-1] = TAIL;
    

    for(;;)
    {
        
        switch (state){
        
            case ON :
                LED_UART_Write(HIGH);
                Timer_Start();
                ADC_DelSig_Start();
                UART_PutString("System powered ON\r\n");
                state = IDLE;
                break;
                
            case OFF :
                LED_UART_Write(LOW);
                UART_Init();
                PWM_Stop();
                Timer_Stop();
                ADC_DelSig_Stop();
                UART_PutString("System powered OFF\r\n");
                state = IDLE;
                break;
                
            case DARK :
                UART_PutString("Bulb powered ON\r\n");
                PWM_Start();
                state = IDLE;
                break;
            
            case LIGHT :
                UART_PutString("Bulb powered OFF\r\n");
                PWM_Stop();
                state = IDLE;
                break;
                
            case ERROR :
                UART_PutString("ERROR in the transmission, character is unknown\r\n");
                UART_Init();
                state = IDLE;
                break;
                
        }
        
        if(flag_send){
            UART_PutArray(Data, TRANSMIT_SIZE);
            flag_send = 0;
        }
        if(flag_dark){
            Set_BULB();
        }
    }
}

/* [] END OF FILE */
