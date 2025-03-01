#pragma once

#include <stdbool.h>
#include <stm32f3xx_hal.h>

// clang-format off
// Conversion factor used to convert raw voltages (100µV) to voltages (V)
#define V_PER_100UV                  (1E-4f)
#define NUM_REG_GROUP_PACKET_BYTES   (8U)
#define TOTAL_NUM_OF_REG_BYTES       (NUM_REG_GROUP_PACKET_BYTES * NUM_OF_ACCUMULATOR_SEGMENTS)
#define NUM_REG_GROUP_PACKET_WORDS   (NUM_REG_GROUP_PACKET_BYTES >> 1U)
#define TOTAL_NUM_OF_REG_GROUP_WORDS (NUM_REG_GROUP_PACKET_WORDS * NUM_OF_ACCUMULATOR_SEGMENTS)
#define NUM_CMD_PAYLOAD_BYTES        (2U)

// Indexing for data to write/read from the register group in word format
#define REG_GROUP_WORD_PEC_INDEX     (3U)
// clang-format on

enum CmdFormat
{
    CMD_WORD = 0U,
    CMD_PEC15,
    NUM_OF_CMD_WORDS,
};
#define TOTAL_NUM_CMD_BYTES (NUM_OF_CMD_WORDS << 1U)

// Indexes for data to write/read from the register group in byte format
enum RegGroupByteFormat
{
    REG_GROUP_BYTE_0 = 0U,
    REG_GROUP_BYTE_1,
    REG_GROUP_BYTE_2,
    REG_GROUP_BYTE_3,
    REG_GROUP_BYTE_4,
    REG_GROUP_BYTE_5,
    NUM_REG_GROUP_PAYLOAD_BYTES,
};

/**
 * Initialize the SPI handle used to communicate with the LTC6813
 * @param spi_handle The given SPI handle for the LTC6813 daisy chain.
 */
void Io_LTC6813Shared_InitSpiHandle(SPI_HandleTypeDef *spi_handle);

/**
 * Calculate and pack PEC15 bytes for commands sent to the LTC6813
 * @param tx_cmd The buffer containing the command used to calculate and pack
 * PEC15 bytes
 */
void Io_LTC6813Shared_PackCmdPec15(uint16_t *tx_cmd);

/**
 * Calculate and pack PEC15 bytes for data written to a given register groups
 * @param tx_cfg The buffer containing data used to calculate and pack PEC15
 * bytes
 */
void Io_LTC6813Shared_PackRegisterGroupPec15(uint8_t *tx_cfg);

/**
 * Calculate the PEC15 value for data to write/read back from a register group
 * on the LTC6813
 * @param data_buffer The buffer containing data to write/read to calculate the
 * PEC15 bytes from
 * @return The PEC15 code generated from the contents of data_buffer
 */
uint16_t Io_LTC6813Shared_CalculateRegGroupPec15(const uint8_t *data_buffer);

/**
 * Send a command to all LTC6813 chips on the daisy chain
 * @param cmd The command that is transmitted to the LTC6813 chips on
 * the daisy chain
 * @return True if the command was transmitted successfully. Else, false
 */
bool Io_LTC6813Shared_SendCommand(uint16_t cmd);

/**
 * Wait for the completion of all ADC conversions for the LTC6813 chips on the
 * daisy chain.
 * @return True if all ADC conversions have completed successfully. Else, false.
 */
bool Io_LTC6813Shared_PollAdcConversions(void);

/**
 * Set configuration register to default settings. Refer to ltc6813_configs in
 * Io_LTC6813.c for exact register configurations used. Users can also consult
 * Table 56 (Memory Bit Descriptions) of the LTC6813 datasheet for more
 * information.
 * @return True if configuration registers are set successfully. Else, false
 */
bool Io_LTC6813Shared_SetCfgRegsToDefaultSettings(void);

/**
 * Write to configuration registers, namely CFGRA and CFGRB
 * @return True if the commands used to write to the configuration registers can
 * be sent successfully. Else, false
 */
bool Io_LTC6813Shared_WriteConfigurationRegisters(void);

/**
 * Enable LTC6813 cell discharge
 * @return True if the command to enable cell discharge is sent successfully.
 * Else, false
 */
bool Io_LTC6813Shared_EnableDischarge(void);

/**
 * Disable LTC6813 cell discharge
 * @return True if the command to enable cell discharge is sent successfully.
 * Else, false
 */
bool Io_LTC6813Shared_DisableDischarge(void);
