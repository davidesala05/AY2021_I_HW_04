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
                Timer_WritePeriod(PERIOD_TIMER); //The custom period must reset every time the TIMER is started (otherwise the TimerStart() function set the configuration pannel parameters)
                ADC_DelSig_Start(); //ADC is let started
                state = IDLE;
                break;
                
            case OFF : //If the character "S" or "s" is write
                LED_UART_Write(LOW); //The LED of the UART's status is powered OFF
                Reset_ALL(); //Function used to STOP all the components and reset the variables
                state = IDLE;
                break;
                
            case DARK : //If the luminosity is below the threshold (after debouncing)
                PWM_Start(); //PWM ON to switch ON the BULB
                Reset_flags(DARK); //Function used to reset the flags and count for the DARK state
                state = IDLE;
                break;
            
            case BRIGHT : //If the luminosity is above the threshold (after debouncing)
                PWM_Stop(); //PWM OFF to switch OFF the BULB
                Reset_flags(BRIGHT); //Function used to reset the flags and count for the BRIGHT state
                state = IDLE;
                break;
            
            default:
                break;
        }
        if(flag_send){ //If the sampling of both the channels is done
            UART_PutArray(Data, TRANSMIT_SIZE); //The array with the values is put on the UART
            flag_send = 0;
        }
        /*If the ambient luminosity is under the threshold (BULB ON)
          the BULB is modulated by the potentiometer*/
        if(flag_dark){
            Set_BULB(); //Function used to write the compare value of the PWM in order to modulate
        }               // the intensity of the bulb (defined in the GlobalVariables.c file)
    }
}

/* [] END OF FILE */
