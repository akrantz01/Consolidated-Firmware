/*****************************************************************************
 * Includes
 ******************************************************************************/
#include "Io_Can.h"
#include "SharedMacros.h"

/******************************************************************************
 * Module Variable Definitions
 ******************************************************************************/
// clang-format off
static CanMaskFilterConfig_Struct mask_filters[] =
{
   INIT_MASK_FILTER(MASKMODE_16BIT_ID_SHARED, MASKMODE_16BIT_MASK_SHARED)
};
// clang-format on

/******************************************************************************
 * Function Definitions
 ******************************************************************************/
CanMaskFilterConfig_Struct *Io_Can_GetCanMaskFilters(void)
{
    return mask_filters;
}

uint32_t Io_Can_GetNumberOfCanMaskFilters(void)
{
    return NUM_ELEMENTS_IN_ARRAY(mask_filters);
}
