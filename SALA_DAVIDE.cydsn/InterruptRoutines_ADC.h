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

#ifndef __INTERRUPT_ROUTINES_ADC_H
    
    #define __INTERRUPT_ROUTINES_ADC_H
    
    #include "cytypes.h"
    #include "GlobalVariables.h"
    
    #define PHOTO_CHANNEL 0
    #define POT_CHANNEL 1
    
    #define BYTE_TO_SEND 4
    #define TRANSMIT_SIZE 1+BYTE_TO_SEND+1
    
    uint8_t Data[TRANSMIT_SIZE];
    
    CY_ISR_PROTO(Custom_ADC_ISR);
    
#endif

/* [] END OF FILE */
