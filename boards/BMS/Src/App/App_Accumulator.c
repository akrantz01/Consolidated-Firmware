#include <stdlib.h>
#include <assert.h>
#include "App_Accumulator.h"

enum AccumulatorMonitorState
{
    GET_CELL_VOLTAGE_STATE = 0U,
};

struct Accumulator
{
    // Configure the cell monitoring chip
    bool (*config_monitoring_chip)(void);

    // Cell voltage monitoring functions
    bool (*start_cell_voltage_conv)(void);
    bool (*read_cell_voltages)(void);
    void (*get_min_cell_loc)(uint8_t *, uint8_t *);
    void (*get_max_cell_loc)(uint8_t *, uint8_t *);
    float (*get_min_cell_voltage)(void);
    float (*get_max_cell_voltage)(void);
    float (*get_segment_voltage)(AccumulatorSegments_E);
    float (*get_pack_voltage)(void);
    float (*get_avg_cell_voltage)(void);
};

struct Accumulator *App_Accumulator_Create(
    bool (*config_monitoring_chip)(void),
    bool (*start_voltage_conv)(void),
    bool (*read_cell_voltages)(void),
    void (*get_min_cell_loc)(uint8_t *, uint8_t *),
    void (*get_max_cell_loc)(uint8_t *, uint8_t *),
    float (*get_min_cell_voltage)(void),
    float (*get_max_cell_voltage)(void),
    float (*get_segment_voltage)(AccumulatorSegments_E),
    float (*get_pack_voltage)(void),
    float (*get_avg_cell_voltage)(void))
{
    struct Accumulator *accumulator = malloc(sizeof(struct Accumulator));
    assert(accumulator != NULL);

    accumulator->config_monitoring_chip = config_monitoring_chip;

    // Cell voltage monitoring functions
    accumulator->read_cell_voltages      = read_cell_voltages;
    accumulator->start_cell_voltage_conv = start_voltage_conv;
    accumulator->get_min_cell_voltage    = get_min_cell_voltage;
    accumulator->get_max_cell_voltage    = get_max_cell_voltage;
    accumulator->get_min_cell_loc        = get_min_cell_loc;
    accumulator->get_max_cell_loc        = get_max_cell_loc;
    accumulator->get_segment_voltage     = get_segment_voltage;
    accumulator->get_pack_voltage        = get_pack_voltage;
    accumulator->get_avg_cell_voltage    = get_avg_cell_voltage;

    return accumulator;
}

void App_Accumulator_Destroy(struct Accumulator *accumulator)
{
    free(accumulator);
}

void App_Accumulator_InitRunOnEntry(const struct Accumulator *const accumulator)
{
    // Configure the cell monitoring chips. Disable discharge at startup
    accumulator->config_monitoring_chip();
}

void App_Accumulator_RunOnTick100Hz(
    struct Accumulator *      accumulator,
    struct BmsCanTxInterface *can_tx)
{
    static enum AccumulatorMonitorState state = GET_CELL_VOLTAGE_STATE;

    switch (state)
    {
        case GET_CELL_VOLTAGE_STATE:

            // Read cell voltages
            accumulator->read_cell_voltages();

            // TODO: Add broadcast BMS CAN messages when fixed pt. CAN PR has
            // been merged in

            // Start cell temperature voltage conversions for the next cycle
            accumulator->start_cell_voltage_conv();
            break;

        default:
            break;
    }
}
