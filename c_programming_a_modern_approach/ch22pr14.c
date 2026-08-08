#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_line(char str[], int n) {
  int ch, i = 0;

  while ((ch = getchar()) != '\n' && ch != EOF)
    if (i < n)
      str[i++] = (char)ch;
  str[i] = '\0';
  return i;
}

int main(void) {
  char input_name[FILENAME_MAX];
  char *output_name;
  FILE *input, *output;
  int shift, ch;

  printf("Enter name of file to be encrypted: ");
  if (read_line(input_name, (int)sizeof(input_name) - 1) == 0)
    return EXIT_FAILURE;
  printf("Enter shift amount (1-25): ");
  if (scanf("%d", &shift) != 1 || shift < 1 || shift > 25) {
    fprintf(stderr, "Invalid shift amount\n");
    return EXIT_FAILURE;
  }

  output_name = malloc(strlen(input_name) + 5);
  if (output_name == NULL)
    return EXIT_FAILURE;
  sprintf(output_name, "%s.enc", input_name);
  input = fopen(input_name, "r");
  if (input == NULL) {
    fprintf(stderr, "Can't open %s\n", input_name);
    free(output_name);
    return EXIT_FAILURE;
  }
  output = fopen(output_name, "w");
  if (output == NULL) {
    fprintf(stderr, "Can't open %s\n", output_name);
    fclose(input);
    free(output_name);
    return EXIT_FAILURE;
  }

  while ((ch = getc(input)) != EOF) {
    if (isupper((unsigned char)ch))
      ch = (ch - 'A' + shift) % 26 + 'A';
    else if (islower((unsigned char)ch))
      ch = (ch - 'a' + shift) % 26 + 'a';
    if (putc(ch, output) == EOF)
      break;
  }
  if (ferror(input) || ferror(output) || fclose(output) == EOF) {
    fprintf(stderr, "File input/output error\n");
    fclose(input);
    free(output_name);
    return EXIT_FAILURE;
  }
  fclose(input);
  printf("Encrypted file: %s\n", output_name);
  free(output_name);
  return EXIT_SUCCESS;
}
