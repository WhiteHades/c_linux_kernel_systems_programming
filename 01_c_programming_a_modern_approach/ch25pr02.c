#include <locale.h>
#include <stdio.h>

static void print_grouping(const char *name, const char *grouping) {
  const unsigned char *p = (const unsigned char *) grouping;

  printf("%s =", name);
  while (*p != '\0') {
    printf(" %u", *p);
    p++;
  }
  printf("\n");
}

static void print_char_value(const char *name, char value) {
  printf("%s = %u\n", name, (unsigned char) value);
}

int main(int argc, char *argv[]) {
  struct lconv *locale_data;

  if (argc != 2) {
    printf("usage: %s locale\n", argv[0]);
    return 1;
  }

  if (setlocale(LC_ALL, argv[1]) == NULL) {
    printf("Locale not available: %s\n", argv[1]);
    return 1;
  }

  locale_data = localeconv();
  printf("decimal_point = \"%s\"\n", locale_data->decimal_point);
  printf("thousands_sep = \"%s\"\n", locale_data->thousands_sep);
  print_grouping("grouping", locale_data->grouping);
  printf("mon_decimal_point = \"%s\"\n", locale_data->mon_decimal_point);
  printf("mon_thousands_sep = \"%s\"\n", locale_data->mon_thousands_sep);
  print_grouping("mon_grouping", locale_data->mon_grouping);
  printf("positive_sign = \"%s\"\n", locale_data->positive_sign);
  printf("negative_sign = \"%s\"\n", locale_data->negative_sign);
  printf("currency_symbol = \"%s\"\n", locale_data->currency_symbol);
  print_char_value("frac_digits", locale_data->frac_digits);
  print_char_value("p_cs_precedes", locale_data->p_cs_precedes);
  print_char_value("n_cs_precedes", locale_data->n_cs_precedes);
  print_char_value("p_sep_by_space", locale_data->p_sep_by_space);
  print_char_value("n_sep_by_space", locale_data->n_sep_by_space);
  print_char_value("p_sign_posn", locale_data->p_sign_posn);
  print_char_value("n_sign_posn", locale_data->n_sign_posn);
  printf("int_curr_symbol = \"%s\"\n", locale_data->int_curr_symbol);
  print_char_value("int_frac_digits", locale_data->int_frac_digits);
  print_char_value("int_p_cs_precedes", locale_data->int_p_cs_precedes);
  print_char_value("int_n_cs_precedes", locale_data->int_n_cs_precedes);
  print_char_value("int_p_sep_by_space", locale_data->int_p_sep_by_space);
  print_char_value("int_n_sep_by_space", locale_data->int_n_sep_by_space);
  print_char_value("int_p_sign_posn", locale_data->int_p_sign_posn);
  print_char_value("int_n_sign_posn", locale_data->int_n_sign_posn);

  return 0;
}
