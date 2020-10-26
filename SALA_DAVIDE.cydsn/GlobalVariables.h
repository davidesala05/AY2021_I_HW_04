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
#define START 1
#define DARK 2
#define LIGHT 3
#define STOP 4
#define ERROR 5

#define HIGH 1
#define LOW 0

#define HEADER 0xA0
#define TAIL 0xC0

#define THRESHOLD_LIGHT 3000

extern int8_t ch_received;
extern int8_t state;
extern int32 value_photo;
extern int32 value_pot;
extern int8_t flag_send;
extern int8_t flag_change_status;


/* [] END OF FILE */
