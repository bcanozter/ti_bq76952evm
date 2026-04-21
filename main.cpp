#include "i2c.hpp"

#include <iostream>

#define BQ_I2C_ADDR 0x08
#define CMD_INTERNAL_TEMP 0x68

int main() {
  if (!i2c_open("/dev/i2c-1")) {
    std::cerr << "I2C open failed\n";
    return 1;
  }

  if (!i2c_set_addr(BQ_I2C_ADDR)) {
    std::cerr << "BQ_I2C_ADDR set failed\n";
    return 1;
  }

  uint8_t buf[2];

  // Test
  if (!i2c_read(CMD_INTERNAL_TEMP, buf, 2)) {
    std::cerr << "CMD_INTERNAL_TEMP read failed\n";
    return 1;
  }

  uint16_t raw = (buf[1] << 8) | buf[0];

  std::cout << "RAW: " << raw << std::endl;
  std::cout << "Temp (C approx): " << (raw / 10.0 - 273.15)
            << std::endl;

  return 0;
}