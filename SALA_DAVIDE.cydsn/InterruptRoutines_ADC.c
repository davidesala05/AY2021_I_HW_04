/* ========================================
 *
 * In this function both the channels (PHOTO and POT) are sampled
 * As explaned in the TopDesign, a software debouncer is implemented for both
 * the DARK and BRIGHT condition. This allows to not change the state
 * of the BULB every 100ms if the lumonisity measured by the PHOTORESISTOR
 * is close to the THRESHOLD.
 * This is necessary because the signal acquired is quite noisy,
 * especially if the ambient light is artificial!
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
    /*
    The following condition controls if the luminosity is below the THRESHOLD.
    The count variable is used to wait that the condition of DARK
    is verified for 1 second consecutively (10*100msec).
    If it is true, then the BULB is switched ON in the main.
    In this condition the count variable of the BRIGHT state is reset to 0,
    this allows to control both of the state simultaneously.
    */
    if (value <= THRESHOLD){
        count_dark++;
        count_bright = 0; //The count variable for the BRIGHT condition is reset to 0
        if ((count_dark == 10) && (flag_dark == 0)) { //the flag_dark is used to set the state only one time
            state = DARK; //State used in the main to start the PWM
        }
    }
    /*
    The following condition is the opposite of the previous one;
    it controls if the luminosity is above the THRESHOLD.
    The count variable is used to wait that the condition of BRIGHT
    is verified for 1 second consecutively (10*100msec).
    If it is true, then the BULB is switched OFF in the main.
    In this condition the count variable of the DARK state is reset to 0,
    this allows to control both of the state simultaneously.
    */
    if (value > THRESHOLD){
        count_bright ++;
        count_dark = 0; //The count variable for the DARK condition is reset to 0
        if ((count_bright == 10) && (flag_bright == 0)){
            state = BRIGHT; //State used in the main to stop the PWM
        }
    }
    
    AMux_FastSelect(POT_CHANNEL); //Mux set to the POTENTIOMETER's channel
    
    value = ADC_DelSig_Read32(); //New sampled value is saved
    
    Normalize_value(); //The value is normalized within the possible range
    
    //The value is written in the array to send
    Data[3] = value >> 8;
    Data[4] = value & 0xFF;
    
    flag_send = 1; //Flag used in the main to send the packet with all the values

}

/* [] END OF FILE */
