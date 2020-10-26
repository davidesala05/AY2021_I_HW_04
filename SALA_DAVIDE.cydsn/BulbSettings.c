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

#include "BulbSettings.h"
#include "PWM.h"

void Set_BULB(int32 dc){
    PWM_Start();
    dc = (dc*255)/65535;
    PWM_WriteCompare(dc);
}

/* [] END OF FILE */
