#include <stdio.h>
#define PI 3.14159f

int main(void)
{
  int radius;
  printf("enter the radius value, only integer numbers: ");
  scanf("%d", &radius);
  float volume = (4.0f/3.0f) * PI * radius * radius * radius;
  printf("volume of sphere: %.2f\n", volume);

  return 0;
}
