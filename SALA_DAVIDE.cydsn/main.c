/* ========================================
 *
 * FOURTH ASSIGNMENT
 * DAVIDE SALA
 * 
 * ========================================
*/
#include "project.h"
#include "InterruptRoutines_UART.h"
#include "InterruptRoutines_ADC.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_Start();
  
    isr_ADC_StartEx(Custom_ADC_ISR);
    isr_UART_StartEx(Custom_UART_RX_ISR);
    
    //HEADER and TAIL are added to the packet to send
    Data[0] = HEADER; 
    Data[TRANSMIT_SIZE-1] = TAIL;
    
    for(;;)
    {
        switch (state){
        
            case ON : //If the character "B" or "b" is write
                LED_UART_Write(HIGH); //LED of the UART's status is powered ON
                Timer_Start(); //Timer is let started to start the sampling
                ADC_DelSig_Start(); //The ADC is started
                state = IDLE;
                break;
                
            case OFF : //If the character "S" or "s" is write
                LED_UART_Write(LOW); //The LED of the UART's status is powered OFF
                UART_Init(); //Initialization of the UART
                PWM_Stop(); //PWM, TIMER and ADC are stopped
                Timer_Stop();
                ADC_DelSig_Stop();
                state = IDLE;
                break;
                
            case DARK : //If the luminosity is below the threshold
                PWM_Start(); //PWM ON to switch ON the BULB
                state = IDLE;
                break;
            
            case LIGHT : //If the luminosity is above the threshold
                PWM_Stop(); //PWM OFF to switch OFF the BULB
                state = IDLE;
                break;
                
            case ERROR : //In case the character sent is not one of the expected ones
                UART_PutString("ERROR in the transmission, character is unknown\r\n");
                UART_Init();
                state = IDLE;
                break;
                
        }
        
        if(flag_send){ //If the sampling of both the channels are finished
            UART_PutArray(Data, TRANSMIT_SIZE); //The array with the values is put on the UART
            flag_send = 0;
        }
        if(flag_dark){ //If the ambient luminosity is under the threshold (BULB ON) the BULB is modulated by the potentiometer
            Set_BULB(); //Function used to write the compare value of the PWM in order to modulate the intensity of the bulb (defined in the GlobalVariables.c file)
        }
    }
}

/* [] END OF FILE */
