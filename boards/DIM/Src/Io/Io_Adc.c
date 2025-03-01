#include <stm32f3xx.h>
#include "Io_SharedAdc.h"
#include "Io_Adc.h"

// In STM32 terminology, each ADC pin corresponds to an ADC channel (See:
// ADCEx_channels). If there are multiple ADC channels being measured, the ADC
// measures them based on "rank" (See: ADCEx_regular_rank). The rank starts
// counting at 1, and the lower the rank, the higher the measurement priority.
//
// For example, suppose we are measuring ADC channel 2, 4, and 7, which have
// rank 3, 1, and 2 respectively. The ADC will measure the channel 4, then
// channel 7, and finally channel 2. This order is important because it
// determines the order in which the DMA writes data to our raw_adc_values
// buffer.
//
// The following enum is used to index into raw_adc_values, which means it must
// be ordered in ascending ranks. If we were writing an enum for the earlier
// example, it would look like:
//
// enum
// {
//     CHANNEL_4, // Rank 1
//     CHANNEL_7, // Rank 2
//     CHANNEL_2, // Rank 3
//     NUM_ADC_CHANNELS,
// };
enum
{
    CHANNEL_12,
    NUM_ADC_CHANNELS
};

static uint16_t raw_adc_values[NUM_ADC_CHANNELS];
static float    adc_voltages[NUM_ADC_CHANNELS];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    adc_voltages[CHANNEL_12] = Io_SharedAdc_ConvertRawAdcValueToVoltage(
        hadc, false, raw_adc_values[CHANNEL_12]);
}

uint16_t *Io_Adc_GetRawAdcValues(void)
{
    return raw_adc_values;
}

float Io_Adc_GetChannel12Voltage(void)
{
    return adc_voltages[CHANNEL_12];
}
