/* ========================================
 *
 * In this function both the channels (PHOTO and POT) are sampled
 * 
 * ========================================
*/

#include "InterruptRoutines_ADC.h"

CY_ISR(Custom_ADC_ISR) {
    
    Timer_ReadStatusRegister();
    
    AMux_FastSelect(PHOTO_CHANNEL); //Mux set to the PHOTORESISTOR's channel
    value = ADC_DelSig_Read32(); //Sampled value is saved
    
    Normalize_value(); //The value is normalized within the possible range
    
    //The value is written in the array to send
    Data[1] = value >> 8;
    Data[2] = value & 0xFF;
    
    /*If the luminosity is below the threshold
      (the flag_dark is used to not enter every cycle)*/
    if ((flag_dark == 0) && (value <= THRESHOLD_LIGHT)){
        state = DARK; //State used in the main to start the PWM
        flag_dark = 1;
        flag_light = 0;
    }
    /*If the luminosity is above the threshold
      (the flag_light is used to not enter every cycle)*/
    if ((flag_light == 0) && (value > THRESHOLD_LIGHT)){
        state = LIGHT; //State used in the main to stop the PWM
        flag_light = 1;
        flag_dark = 0;
    }
    
    AMux_FastSelect(POT_CHANNEL); //Mux set to the POTENTIOMETER's channel
    value = ADC_DelSig_Read32();
    
    Normalize_value(); //The value is normalized within the possible range
    
    //The value is written in the array to send
    Data[3] = value >> 8;
    Data[4] = value & 0xFF;
    
    flag_send = 1; //Flag used in the main to send the packet with all the values

}

/* [] END OF FILE */
