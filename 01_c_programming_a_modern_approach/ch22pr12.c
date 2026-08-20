#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fp;
  char line[256];

  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    return EXIT_FAILURE;
  }
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Can't open %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  printf("Item          Unit          Purchase\n");
  printf("              Price         Date\n");
  while (fgets(line, sizeof(line), fp) != NULL) {
    int item, month, day, year;
    double price;

    if (sscanf(line, "%d,%lf,%d/%d/%d", &item, &price, &month, &day,
               &year) == 5)
      printf("%-13d $%9.2f     %d/%d/%d\n", item, price, month, day, year);
    else
      fprintf(stderr, "Skipping malformed line: %s", line);
  }

  if (ferror(fp)) {
    fprintf(stderr, "Error reading %s\n", argv[1]);
    fclose(fp);
    return EXIT_FAILURE;
  }
  fclose(fp);
  return EXIT_SUCCESS;
}
