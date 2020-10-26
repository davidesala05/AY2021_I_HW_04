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



CY_ISR(Custom_ADC_ISR) {
    
    Timer_ReadStatusRegister();
    
    ADC_DelSig_StopConvert();
    AMux_FastSelect(PHOTO_CHANNEL);
    ADC_DelSig_StartConvert();
    
    value_photo = ADC_DelSig_Read32();

    if (value_photo < 0){
        value_photo = 0;
    }
    if (value_photo > 65535){
        value_photo = 65535;
    }
    
    // Write bytes in data
    Data[1] = value_photo >> 8;
    Data[2] = value_photo & 0xFF;
    
    if ((flag_dark == 0) && (value_photo <= THRESHOLD_LIGHT)){
        state = DARK;
        flag_dark = 1;
    }
    else if ((flag_dark) && (value_photo > THRESHOLD_LIGHT)) {
        state = LIGHT;
        flag_dark = 0;
    }
    
    ADC_DelSig_StopConvert();
    AMux_FastSelect(POT_CHANNEL);
    ADC_DelSig_StartConvert();
    
    value_pot = ADC_DelSig_Read32();
    
    if (value_pot < 0){
        value_pot = 0;
    }
    if (value_pot > 65535){
        value_pot = 65535;
    }
    // Write bytes in data
    Data[3] = value_pot >> 8;
    Data[4] = value_pot & 0xFF;
    
    DC_PWM = Data[3];
    
    flag_send = 1;

}

/* [] END OF FILE */
