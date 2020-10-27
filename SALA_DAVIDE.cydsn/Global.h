/* ========================================
 *
 * Here all the global variables, states and masks are declared
 * Even the function used to set the BULB intensity
 * and the one used to normalize the value are declared
 * 
 * ========================================
*/

#include "cytypes.h"
#include "PWM.h"

#define IDLE 0 //State used to do nothing
#define ON 1 //If the system is power ON
#define OFF 2 //If the system is power OFF
#define DARK 3 //If the luminosity is below the threshold
#define LIGHT 4 //If the luminosity is above the threshold

#define HIGH 1
#define LOW 0

#define HEADER 0xA0
#define TAIL 0xC0

/*The threshold defined below is the one that corresponds more or less
  to the luminosity ridden by the sensor if it is covered by an hand in a closed ambient*/
#define THRESHOLD_LIGHT 40000

extern uint8_t ch_received; //Where the char received is saved in the UART's isr
extern uint8_t state; //Used to switch between different states in the program
extern int32 value; //Used to save the sampled values
extern uint8_t flag_send; //Flag used to send the packet after complete the sampling
extern uint8_t flag_dark; //Flag used to modulate the BULB if the luminosity is below the threshold
extern uint8_t flag_light;

void Set_BULB(); //Function used to set the BULB intensity via the PWM control

void Normalize_value(); //Function used to normalize the value within the usable range

/* [] END OF FILE */
