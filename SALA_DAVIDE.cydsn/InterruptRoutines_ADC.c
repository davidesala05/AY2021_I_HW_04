/* ========================================
 *
 * In this function both the channels (PHOTO and POT) are sampled
 * As explaned in the TopDesign, a software debouncer is implemented for both
 * the DARK and BRIGHT condition. This allows to not change the state
 * of the BULB every (f = frequency of acquisition) if the lumonisity measured
 * by the PHOTORESISTOR is close to the THRESHOLD.
 * This is necessary because the signal acquired is quite noisy,
 * especially if the ambient light is artificial!
 * 
 * ========================================
*/

#include "InterruptRoutines_ADC.h"

CY_ISR(Custom_ADC_ISR) {
    
    Timer_ReadStatusRegister();
     /*Variable to count the acquisition is incremented*/
    count_sample++;
    
    /*Acquisition of the PHOTORESISTOR*/
    AMux_FastSelect(PHOTO_CHANNEL); //Channel is switched
    value = ADC_DelSig_Read32();
    Normalize_value(); //Value is normalized within the admissible range
    value_photo += value; //New value is accumulated to perform after the average
    
    /*Acquisition of the POTENTIOMETER*/
    AMux_FastSelect(POT_CHANNEL);
    value = ADC_DelSig_Read32();
    Normalize_value();
    value_pot += value;
    
    if(count_sample == REPETITIONS){ //This condition if verified every 100msec independently by the number of REPETITIONS
        count_sample = 0;
        value = value_photo/REPETITIONS; //This is the value of luminosity used for the control and then sent by the UART
    
        /*The value is written in the array to send*/
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
            if ((count_dark == DEBOUNCER_PERIOD) && (flag_dark == 0)) { //the flag_dark is used to set the state only one time
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
            if ((count_bright == DEBOUNCER_PERIOD) && (flag_bright == 0)){
                state = BRIGHT; //State used in the main to stop the PWM
            }
        }
        
        value = value_pot/REPETITIONS; //This is the value of the potentiometer used for control the BULB and then sent by the UART
        
        /*The value is written in the array to send*/
        Data[3] = value >> 8;
        Data[4] = value & 0xFF;
        
        flag_send = 1; //Flag used in the main to send the packet with all the values
        
        /*Variables used to accumulate the values are reset*/
        value_photo = 0;
        value_pot = 0;
    }
}

/* [] END OF FILE */
