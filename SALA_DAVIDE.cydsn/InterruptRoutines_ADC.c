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

#include "InterruptRoutines_ADC.h"
#include "Timer.h"
#include "ADC_DelSig.h"
#include "AMux.h"
#include "BULB.h"


CY_ISR(Custom_ADC_ISR) {
    
    Timer_ReadStatusRegister();

    AMux_Select(PHOTO_CHANNEL);
    
    value_photo = ADC_DelSig_Read32();
    
    if (value_photo < 0){
        value_photo = 0;
    }
    if (value_photo > 65535){
        value_photo = 65535;
    }
    // Write bytes in buffer
    Data[1] = value_photo >> 8;
    Data[2] = value_photo & 0xFF;

    if (value_photo <= THRESHOLD){
        state = DARK;
    }
    else {
        state = LIGHT;
    }
    
    AMux_Select(POT_CHANNEL);
    
    value_pot = ADC_DelSig_Read32();
    
    if (value_pot < 0){
        value_pot = 0;
    }
    if (value_pot > 65535){
        value_pot = 65535;
    }
    // Write bytes in buffer
    Data[3] = value_pot >> 8;
    Data[4] = value_pot & 0xFF;
    
    flag_send = 1;

}

/* [] END OF FILE */
