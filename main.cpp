#include "bq76952_protocol.hpp"
#include "i2c.hpp"

#include <unistd.h>

int main() {
  int err;
  err = i2c_init("/dev/i2c-1");
  if (err != 0) { return 1; }

  // while (1) {
  BQ76952_init();
  usleep(1000);
  // }

  return 0;
}