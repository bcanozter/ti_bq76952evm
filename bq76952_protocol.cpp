#include "bq76952_protocol.hpp"

#include "i2c.hpp"

#include <cstdint>
#include <cstring>
#include <iostream>
#include <unistd.h>

void BQ76952_init() {
  // Testing..
  unsigned char RX_data[2] = {0x00};
  direct_command(CMD_INTERNAL_TEMP, 0x00, READ, RX_data);
  uint16_t raw = (RX_data[1] << 8) | RX_data[0];

  std::cout << "RAW: " << raw << std::endl;
  std::cout << "Temp (C approx): " << (raw / 10.0 - 273.15)
            << std::endl;

  usleep(2000);
  unsigned char RX_32Byte[32] = {0x00};
  subcommand(SUB_CMD_DEVICE_NUM, 0x00, READ, RX_32Byte);
  raw = (RX_32Byte[1]) << 8 | RX_32Byte[0];
  std::cout << "Device Number: 0x" << std::hex << raw
            << std::endl;
}

void direct_command(uint8_t command, uint16_t data,
                    uint8_t type, unsigned char *rx_result)
// Direct Commands
{
  uint8_t TX_data[2] = {0x00, 0x00};

  // little endian format
  TX_data[0]               = data & 0xff;
  TX_data[1]               = (data >> 8) & 0xff;
  unsigned char RX_data[2] = {0x00};
  if (type == READ) { // Read
    i2c_read(command, RX_data, 2);
    if (rx_result != NULL) {
      memcpy(rx_result, RX_data, sizeof(RX_data));
    }
  }
}

void subcommand(uint16_t command, uint16_t data,
                uint8_t type, unsigned char *rx_result) {
  uint8_t TX_Reg[4]    = {0x00, 0x00, 0x00, 0x00};
  uint8_t TX_Buffer[2] = {0x00, 0x00};

  // TX_Reg in little endian format
  TX_Reg[0] = command & 0xff;
  TX_Reg[1] = (command >> 8) & 0xff;

  if (type == READ) {
    unsigned char RX_32Byte[32] = {0x00};
    i2c_write(0x3E, TX_Reg, 2);
    usleep(2000);
    i2c_read(0x40, RX_32Byte, 32);
    if (rx_result != NULL) {
      memcpy(rx_result, RX_32Byte, sizeof(RX_32Byte));
    }
  }
}