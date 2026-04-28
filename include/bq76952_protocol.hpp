#pragma once

#include <cstdint>

// Direct Commands
#define CMD_ALARM_ENABLE 0x66

// mV
#define CMD_CELL1_VOLTAGE 0x14
#define CMD_CELL2_VOLTAGE 0x16
#define CMD_CELL3_VOLTAGE 0x18
#define CMD_CELL4_VOLTAGE 0x1A
#define CMD_CELL5_VOLTAGE 0x1C
#define CMD_CELL6_VOLTAGE 0x1E
#define CMD_CELL7_VOLTAGE 0x20
#define CMD_CELL8_VOLTAGE 0x22
#define CMD_CELL9_VOLTAGE 0x24
#define CMD_CELL10_VOLTAGE 0x26
#define CMD_CELL11_VOLTAGE 0x28
#define CMD_CELL12_VOLTAGE 0x2A
#define CMD_CELL13_VOLTAGE 0x2E
#define CMD_CELL14_VOLTAGE 0x30
#define CMD_CELL15_VOLTAGE 0x32
#define CMD_CELL16_VOLTAGE 0x34
#define CMD_STACK_VOLTAGE 0x36
#define CMD_PACK_PIN_VOLTAGE 0x38
#define CMD_LD_PIN_VOLTAGE 0x31

#define CMD_CC2_CURRENT 0x3A

#define CMD_INTERNAL_TEMP 0x68 // unit 0.1K
#define CMD_TS1_TEMP 0x70      // unit 0.1K
#define CMD_TS2_TEMP 0x72      // unit 0.1K
#define CMD_TS3_TEMP 0x74      // unit 0.1K

// Subcommands
#define SUB_CMD_DEVICE_NUM 0x0001
#define SUB_CMD_MANUFACTURING_STATUS 0x0057
#define SUB_CMD_FET_ENABLE 0x0022
#define SUB_CMD_RESET 0x0012

// Command Subcommand
#define SET_CFGUPDATE 0x0090
#define EXIT_CFGUPDATE 0x0092
#define FET_ENABLE 0x0022
#define RESET 0x0012
//
#define READ 0  // Read
#define WRITE 1 // Write

void BQ76952_init();

void direct_command(uint8_t command, uint16_t data,
                    uint8_t type, unsigned char *rx_result);
void subcommand(uint16_t command, uint16_t data,
                uint8_t type, unsigned char *rx_result);
void command_subcommand(uint16_t command);