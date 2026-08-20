#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

int contents[STACK_SIZE];
int top = 0;

void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(int value);
int pop(void);

int main(void) {
  char ch;

  for (;;) {
    make_empty();
    printf("Enter an RPN expression: ");
    for (;;) {
      scanf(" %c", &ch);
      if (ch >= '0' && ch <= '9') {
        push(ch - '0');
      } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        int right = pop();
        int left = pop();
        switch (ch) {
        case '+': push(left + right); break;
        case '-': push(left - right); break;
        case '*': push(left * right); break;
        case '/': push(left / right); break;
        }
      } else if (ch == '=') {
        printf("Value of expression: %d\n", pop());
        break;
      } else {
        return 0;
      }
    }
  }
}

void make_empty(void) { top = 0; }
bool is_empty(void) { return top == 0; }
bool is_full(void) { return top == STACK_SIZE; }

void push(int value) {
  if (is_full()) {
    printf("Expression is too complex\n");
    exit(EXIT_FAILURE);
  }
  contents[top++] = value;
}

int pop(void) {
  if (is_empty()) {
    printf("Not enough operands in expression\n");
    exit(EXIT_FAILURE);
  }
  return contents[--top];
}
