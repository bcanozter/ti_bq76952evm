#include "i2c.hpp"

#include <cstdint>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int     fd       = -1;
static uint8_t dev_addr = 0;

bool i2c_open(const char *dev) {
  fd = open(dev, O_RDWR);
  return fd >= 0;
}

bool i2c_set_addr(uint8_t addr) {
  dev_addr = addr;
  return ioctl(fd, I2C_SLAVE, addr) >= 0;
}

bool i2c_write(uint8_t reg, const uint8_t *data,
               uint8_t len) {
  uint8_t buf[1 + 32];

  if (len > 32) { return false; }

  buf[0] = reg;
  for (int i = 0; i < len; i++) { buf[1 + i] = data[i]; }

  return write(fd, buf, len + 1) == (len + 1);
}

bool i2c_read(uint8_t reg, uint8_t *data, uint8_t len) {
  if (write(fd, &reg, 1) != 1) { return false; }
  usleep(1000);
  return read(fd, data, len) == len;
}