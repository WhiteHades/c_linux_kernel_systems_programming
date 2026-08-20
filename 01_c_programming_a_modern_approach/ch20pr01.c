#include <stdio.h>

struct ieee_float {
  unsigned int fraction : 23;
  unsigned int exponent : 8;
  unsigned int sign : 1;
};

union float_view {
  float value;
  struct ieee_float bits;
};

int main(void) {
  union float_view number = {0};

  number.bits.sign = 1;
  number.bits.exponent = 128;
  number.bits.fraction = 0;
  printf("Float value: %.1f\n", number.value);
  return 0;
}
