/* ========================================
 *
 * Here all the global variables, states and masks are initialized
 * 
 * ========================================
*/

#include "GlobalVariables.h"
#include "PWM.h"

uint8_t ch_received = 0;
uint8_t state = IDLE;
uint8_t flag_send = 0;
uint8_t flag_dark = 0;
uint8_t flag_PWM_ON = 0;

int32 value = 0;

void Set_BULB(){
    PWM_WriteCompare(value); // da controllare
}
/* [] END OF FILE */
