/* ========================================
 *
 * This is the header file of the interrupt of the TIMER
 * The TIMER isr is called every 100 milliseconds
 * This isr is used to sample both the channels sequentially
 * 
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_ADC_H
    
    #define __INTERRUPT_ROUTINES_ADC_H
    
    #include "cytypes.h"
    #include "GlobalVariables.h"
    #include "Timer.h"
    #include "ADC_DelSig.h"
    #include "AMux.h"
    
    #define PHOTO_CHANNEL 0 //Channel of the photoresistor used by the MUX
    #define POT_CHANNEL 1 //Channel of the potentiometer used by the MUX
    
    #define BYTE_TO_SEND 4 //The bytes are 4 : 2 for the PHOTORESISTOR (MSB + LSB) and 2 for the POTENTIOMETER (MSB + LSB)
    #define TRANSMIT_SIZE 1+BYTE_TO_SEND+1 //This is the sixe of the packet to send
    
    uint8_t Data[TRANSMIT_SIZE]; //The packet that will be sent in the main
    
    CY_ISR_PROTO(Custom_ADC_ISR);
    
#endif

/* [] END OF FILE */
