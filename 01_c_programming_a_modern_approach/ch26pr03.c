#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int compare_ints(const void *p, const void *q) {
  int left = *(const int *) p;
  int right = *(const int *) q;

  return (left > right) - (left < right);
}

int main(void) {
  const int sizes[] = {1000, 10000, 100000};
  int size_index;

  for (size_index = 0; size_index < 3; size_index++) {
    int n = sizes[size_index];
    int *values = malloc((size_t) n * sizeof(*values));
    clock_t start;
    int i;

    if (values == NULL) {
      printf("Unable to allocate %d integers\n", n);
      return 1;
    }

    for (i = 0; i < n; i++)
      values[i] = n - i;

    start = clock();
    qsort(values, (size_t) n, sizeof(*values), compare_ints);
    printf("%6d integers: %.6f seconds%s\n", n,
           (clock() - start) / (double) CLOCKS_PER_SEC,
           values[0] == 1 && values[n - 1] == n ? "" : " (sort failed)");
    free(values);
  }

  return 0;
}
