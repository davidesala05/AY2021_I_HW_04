/* ========================================
 *
 * This is the header file of the interrupt of the TIMER
 * The TIMER isr is called every PERIOD_TIMER
 * This isr is used to sample both the channels sequentially
 * 
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_ADC_H
    
    #define __INTERRUPT_ROUTINES_ADC_H
    
    #include "cytypes.h"
    #include "Global.h"
    #include "project.h"
    
    #define PHOTO_CHANNEL 0 //Channel of the photoresistor used by the MUX
    #define POT_CHANNEL 1 //Channel of the potentiometer used by the MUX
    
    /*If REPETISTIONS is greater than 1, the values sampled by both the sensors are accumulated
      for REPETITIONS-times and then averaged, only after this passage the new mean values are used
      for data transmission and for all the other purposes.
      Thanks to that we are able to obtain and use a more stable measure and a signal that is denoised.
      In this condition below the values are sampled for 10 times and after the mean is done*/
    #define REPETITIONS 10
    
    /*The period of the TIMER is changed according to the value of the REPETITIONS,
      this allows to have always the same frequency of acquisition and data transmission.
      In this case the period of the data transmission and data control (with the threshold)
      is maintained constantly equal to 100 msec (PERIOD_DATA_STORAGE).
      So, for instance, if the value of REPETITIONS is 1, thus the period of the TIMER is 100msec*/
    #define PERIOD_DATA_STORAGE 1000 //100msec
    #define PERIOD_TIMER PERIOD_DATA_STORAGE/REPETITIONS
    
    /*Below there is the number of times that the comparison with the threshold must be
      unchanged before that the status change of the BULB occur.
      For example, in this case since the DEBOUNCER_PERIOD is 10 
      and the condition is controlled every 100msec, the period of debouncing is 1 second*/
    #define DEBOUNCER_PERIOD 10
    
    /*The bytes are 4 : 2 for the PHOTORESISTOR (MSB + LSB)
      and 2 for the POTENTIOMETER (MSB + LSB)*/
    #define BYTE_TO_SEND 4
    #define TRANSMIT_SIZE 1+BYTE_TO_SEND+1 //This is the size of the packet to send
    
    uint8_t Data[TRANSMIT_SIZE]; //The packet that will be sent in the main
    
    CY_ISR_PROTO(Custom_ADC_ISR);
    
#endif

/* [] END OF FILE */
