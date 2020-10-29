/* ========================================
 *
 * Here all the global variables, states and masks are declared.
 * Even some functions used in the main are declared.
 * 
 * ========================================
*/

#include "cytypes.h"
#include "project.h"

#define IDLE 0 //State used to do nothing
#define ON 1 //If the system is power ON
#define OFF 2 //If the system is power OFF
#define DARK 3 //If the luminosity is below the threshold
#define BRIGHT 4 //If the luminosity is above the threshold

#define HIGH 1
#define LOW 0

#define HEADER 0xA0
#define TAIL 0xC0

/*The threshold defined below is the one that corresponds more or less
  to the luminosity ridden by the sensor in a closed ambient without light entering by the windows*/
#define THRESHOLD 40000

extern uint8_t ch_received; //Where the char received is saved in the UART's isr
extern uint8_t state; //Used to switch between different states in the program
extern int32 value; //Used to save the sampled values
extern int32 value_photo; //Used to accumulate the values of photoresistor
extern int32 value_pot; //Used to accumulate the values of potentiometer
extern uint8_t flag_send; //Flag used to send the packet after the sampling is completed
extern uint8_t flag_dark; //Flag used to modulate the BULB (ONLY ONE TIME PER STATUS CHANGE) if the luminosity is below the threshold
extern uint8_t flag_bright; //Flag used to modulate the BULB (ONLY ONE TIME PER STATUS CHANGE) if the luminosity is above the threshold
extern uint8_t count_dark; //Count variables used to implement a debouncer for the DARK state
extern uint8_t count_bright; //Count variables used to implement a debouncer for the BRIGHT state
extern uint8_t count_sample; //Used to count the number of acquisition, compared then to REPETITIONS

void Set_BULB(); //Function used to set the BULB intensity via the PWM control

void Normalize_value(); //Function used to normalize the value within the usable range

void Reset_ALL (); //Function used to STOP all the components and reset the variables

void Reset_flags(uint8_t state); //Function used to reset the flags and the count variable according to the state

/* [] END OF FILE */
