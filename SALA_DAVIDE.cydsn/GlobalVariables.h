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

#include "cytypes.h"

#define IDLE 0
#define ON 1
#define DARK 2
#define LIGHT 3
#define OFF 4
#define ERROR 5

#define HIGH 1
#define LOW 0

#define HEADER 0xA0
#define TAIL 0xC0

#define THRESHOLD_LIGHT 30000

extern uint8_t ch_received;
extern uint8_t state;
extern int32 value_photo;
extern int32 value_pot;
extern uint8_t DC_PWM;
extern uint8_t flag_send;
extern uint8_t flag_dark;
extern uint8_t flag_PWM_ON;


/* [] END OF FILE */
