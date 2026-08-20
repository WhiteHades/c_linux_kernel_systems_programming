#include <stddef.h>
#include <stdio.h>

struct s {
  char a;
  int b[2];
  float c;
};

static void describe_gap(const char *after, size_t end, size_t next) {
  if (next > end)
    printf("Hole after %s: offset %zu, size %zu\n", after, end, next - end);
}

int main(void) {
  struct s value;
  size_t a_offset = offsetof(struct s, a);
  size_t b_offset = offsetof(struct s, b);
  size_t c_offset = offsetof(struct s, c);
  size_t end;

  printf("a: size %zu, offset %zu\n", sizeof(value.a), a_offset);
  printf("b: size %zu, offset %zu\n", sizeof(value.b), b_offset);
  printf("c: size %zu, offset %zu\n", sizeof(value.c), c_offset);
  printf("structure: size %zu\n", sizeof(value));

  describe_gap("a", a_offset + sizeof(value.a), b_offset);
  describe_gap("b", b_offset + sizeof(value.b), c_offset);
  end = c_offset + sizeof(value.c);
  describe_gap("c", end, sizeof(value));
  if (b_offset == a_offset + sizeof(value.a) &&
      c_offset == b_offset + sizeof(value.b) && sizeof(value) == end)
    printf("The structure has no holes.\n");

  return 0;
}
