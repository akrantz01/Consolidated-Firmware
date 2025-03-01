#include "states/App_AllStates.h"
#include "states/App_ChargeState.h"
#include "states/App_FaultState.h"

#include "App_SetPeriodicCanSignals.h"
#include "App_SharedMacros.h"

static void ChargeStateRunOnEntry(struct StateMachine *const state_machine)
{
    struct BmsWorld *world = App_SharedStateMachine_GetWorld(state_machine);
    struct BmsCanTxInterface *can_tx_interface = App_BmsWorld_GetCanTx(world);
    App_CanTx_SetPeriodicSignal_STATE(
        can_tx_interface, CANMSGS_BMS_STATE_MACHINE_STATE_CHARGE_CHOICE);
}

static void ChargeStateRunOnTick1Hz(struct StateMachine *const state_machine)
{
    App_AllStatesRunOnTick1Hz(state_machine);
}

static void ChargeStateRunOnTick100Hz(struct StateMachine *const state_machine)
{
    App_AllStatesRunOnTick100Hz(state_machine);

    struct BmsWorld *world = App_SharedStateMachine_GetWorld(state_machine);
    struct BmsCanTxInterface *can_tx  = App_BmsWorld_GetCanTx(world);
    struct Charger *          charger = App_BmsWorld_GetCharger(world);

    if (!App_Charger_IsConnected(charger))
    {
        App_CanTx_SetPeriodicSignal_CHARGER_DISCONNECTED_IN_CHARGE_STATE(
            can_tx, true);
        App_SharedStateMachine_SetNextState(state_machine, App_GetFaultState());
    }
}

static void ChargeStateRunOnExit(struct StateMachine *const state_machine)
{
    UNUSED(state_machine);
}

const struct State *App_GetChargeState(void)
{
    static struct State charge_state = {
        .name              = "CHARGE",
        .run_on_entry      = ChargeStateRunOnEntry,
        .run_on_tick_1Hz   = ChargeStateRunOnTick1Hz,
        .run_on_tick_100Hz = ChargeStateRunOnTick100Hz,
        .run_on_exit       = ChargeStateRunOnExit,
    };

    return &charge_state;
}
