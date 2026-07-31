#include <stdio.h>

int main(void) {
  int phone1, phone2, phone3;
  printf("enter phone number [(xxx) xxx-xxxx]: ");
  scanf("(%d) %d-%d", &phone1, &phone2, &phone3);

  printf("you entered %d.%d.%d\n", phone1, phone2, phone3);
  return 0;
}
