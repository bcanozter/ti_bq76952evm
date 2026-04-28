#pragma once

#include <cstdint>

bool i2c_open(const char *dev);
bool i2c_set_addr(uint8_t addr);

bool i2c_write(uint8_t reg, const uint8_t *data,
               uint8_t len);
bool i2c_read(uint8_t reg, uint8_t *data, uint8_t len);
bool i2c_init(const char *device);