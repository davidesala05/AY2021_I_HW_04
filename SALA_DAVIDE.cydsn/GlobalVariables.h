/* ========================================
 *
 * Here all the global variables, states and masks are declared
 * Even the function used to set the BULB intensity is declared
 * 
 * ========================================
*/

#include "cytypes.h"

#define IDLE 0 //State used to do nothing
#define ON 1 //If the system is power ON
#define OFF 2 //If the system is power OFF
#define DARK 3 //If the luminosity is below the threshold
#define LIGHT 4 //If the luminosity is above the threshold
#define ERROR 5 //If the character is wrong

#define HIGH 1
#define LOW 0

#define HEADER 0xA0
#define TAIL 0xC0

#define THRESHOLD_LIGHT 30000 //This threshold is the one that corresponds more or less to the luminosity ridden by the sensor if it is covered by an hand is a close ambient (my bedroom :D)

extern uint8_t ch_received;
extern uint8_t state; //Used to switch between different states in the program
extern int32 value; //Used to save the sampled values
extern uint8_t flag_send; //Flag used to send the packet after complete the sampling
extern uint8_t flag_dark; //Flag used to modulate the BULB if the luminosity is below the threshold

void Set_BULB(); //Function used to set the BULB intensity via the PWM control

/* [] END OF FILE */
