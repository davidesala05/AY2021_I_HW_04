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

void Set_BULB(){
    PWM_WriteCompare(DC_PWM);
}

/* [] END OF FILE */
