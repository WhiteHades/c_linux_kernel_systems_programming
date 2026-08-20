#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

char contents[STACK_SIZE];
int top = 0;

void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(char ch);
char pop(void);

int main(void) {
  int ch;
  bool proper = true;

  make_empty();
  printf("Enter parentheses and/or braces: ");
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (ch == '(' || ch == '{')
      push((char)ch);
    else if (ch == ')' || ch == '}') {
      if (is_empty()) {
        proper = false;
        break;
      }
      char opening = pop();
      if ((ch == ')' && opening != '(') || (ch == '}' && opening != '{')) {
        proper = false;
        break;
      }
    }
  }

  if (!is_empty())
    proper = false;
  printf(proper ? "Parentheses/braces are nested properly\n"
                : "Parentheses/braces are not nested properly\n");
  return 0;
}

void make_empty(void) { top = 0; }
bool is_empty(void) { return top == 0; }
bool is_full(void) { return top == STACK_SIZE; }

void push(char ch) {
  if (is_full()) {
    printf("Stack overflow\n");
    exit(EXIT_FAILURE);
  }
  contents[top++] = ch;
}

char pop(void) { return contents[--top]; }
