/******************************************************************************
 * Includes
 ******************************************************************************/
#include "SharedGpio.h"

/******************************************************************************
 * Module Preprocessor Constants
 ******************************************************************************/

/******************************************************************************
 * Module Preprocessor Macros
 ******************************************************************************/

/******************************************************************************
 * Module Typedefs
 ******************************************************************************/

/******************************************************************************
 * Module Variable Definitions
 ******************************************************************************/

/******************************************************************************
* Private Function Prototypes
*******************************************************************************/

/******************************************************************************
 * Private Function Definitions
 ******************************************************************************/

/******************************************************************************
 * Function Definitions
 ******************************************************************************/
void SharedGpio_GPIO_WritePin(
    GPIO_TypeDef *GPIOx,
    uint16_t      GPIO_Pin,
    uint32_t      User_PinState)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, User_PinState);
}
