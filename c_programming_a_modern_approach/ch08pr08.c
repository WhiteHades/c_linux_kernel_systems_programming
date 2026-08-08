#include <stdio.h>

#define STUDENTS 5
#define QUIZZES 5

int main(void) {
  int grades[STUDENTS][QUIZZES];

  for (int student = 0; student < STUDENTS; student++) {
    printf("Enter grades for student %d: ", student + 1);
    for (int quiz = 0; quiz < QUIZZES; quiz++)
      scanf("%d", &grades[student][quiz]);
  }

  for (int student = 0; student < STUDENTS; student++) {
    int total = 0;
    for (int quiz = 0; quiz < QUIZZES; quiz++)
      total += grades[student][quiz];
    printf("Student %d: total %d, average %.1f\n", student + 1, total,
           (double)total / QUIZZES);
  }

  for (int quiz = 0; quiz < QUIZZES; quiz++) {
    int total = 0, high = grades[0][quiz], low = grades[0][quiz];
    for (int student = 0; student < STUDENTS; student++) {
      int grade = grades[student][quiz];
      total += grade;
      if (grade > high)
        high = grade;
      if (grade < low)
        low = grade;
    }
    printf("Quiz %d: average %.1f, high %d, low %d\n", quiz + 1,
           (double)total / STUDENTS, high, low);
  }

  return 0;
}
