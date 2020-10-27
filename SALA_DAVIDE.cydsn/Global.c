/* ========================================
 *
 * Here all the global variables, states and masks are initialized
 * 
 * ========================================
*/

#include "Global.h"

uint8_t ch_received = 0;
uint8_t state = IDLE;
uint8_t flag_send = 0;
uint8_t flag_dark = 0;
uint8_t flag_PWM_ON = 0;

int32 value = 0;

void Set_BULB(){
    PWM_WriteCompare(value); /*value sampled by the POTENTIOMETER is used
                               to set the duty cycle of the PWM to change the intensity of the BULB*/
}

void Normalize_value(){ //Function used to normalized the value within the possible range
    if (value < 0){
        value = 0;
    }
    if (value > 65535){
        value = 65535;
    }
}
/* [] END OF FILE */