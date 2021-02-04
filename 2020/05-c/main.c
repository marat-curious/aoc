#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting.h"

#define RAW_INPUT_LENGTH 11
#define ROW_INPUT_LENGTH 8
#define COL_INPUT_LENGTH 4

unsigned int get_row(char line[RAW_INPUT_LENGTH]) {
  char input[ROW_INPUT_LENGTH];
  (void)strncpy(input, line, sizeof(input) - 1);
  input[ROW_INPUT_LENGTH - 1] = '\0';

  unsigned int result = 0;
  unsigned int power = 0;
  for (int i = (ROW_INPUT_LENGTH - 2); i >= 0; --i) {
    result += input[i] == 'B' ? (unsigned int)pow(2, power) : 0;
    (void)power++;
  }

  return result;
}

unsigned int get_col(char line[RAW_INPUT_LENGTH]) {
  char input[COL_INPUT_LENGTH];
  (void)strncpy(input, line + (RAW_INPUT_LENGTH - sizeof(input)), sizeof(input) - 1);
  input[COL_INPUT_LENGTH - 1] = '\0';

  unsigned int result = 0;
  unsigned int power = 0;
  for (int i = (COL_INPUT_LENGTH - 2); i >= 0; --i) {
    result += input[i] == 'R' ? (unsigned int)pow(2, power) : 0;
    (void)power++;
  }
  
  return result;
}

unsigned int get_seat_number(char line[RAW_INPUT_LENGTH]) {
  const unsigned int row = get_row(line);
  const unsigned int col = get_col(line);
  return row * 8 + col;
}

int get_missing_seat_with_xor(unsigned int *seats, unsigned int *seats_count) {
  const unsigned int min = seats[0];
  const unsigned int max = seats[*seats_count - 1];

  unsigned int template = 0;
  unsigned int current = min;

  for (int i = min; i <= max; i++) {
    template ^= i;
  }

  for (int i = 1; i < *seats_count; i++) {
    current ^= seats[i];
  }

  return (template ^ current);
}

void solve_part_one(const unsigned int *seat, unsigned int *part_one_answer) {
  if ((*seat) > (*part_one_answer)) {
    (*part_one_answer) = (*seat);
  }
}

void solve_part_two(unsigned int *seats, unsigned int *seats_count, unsigned int *part_two_answer) {
  if (!*seats_count) {
    return;
  }

  comb_sort(*seats_count, (int*)seats);
  *part_two_answer = get_missing_seat_with_xor(seats, seats_count);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("Missing 'filename' parameter");
    return 1;
  }

  FILE *file = fopen(argv[1], "r");

  if (file == NULL) {
    printf("%s file does not exists", argv[1]);
    return 1;
  }

  size_t count = argv[2] != NULL ? (size_t)atoi(argv[2]) : 1024;
  unsigned int index = 0;
  unsigned int seats[count];

  unsigned int part_one_answer = 0;
  unsigned int part_two_answer = 0;

  char line[RAW_INPUT_LENGTH + 1];

  while (fgets(line, sizeof(line), file)) {
    line[RAW_INPUT_LENGTH - 1] = '\0';
    const unsigned int seat = get_seat_number(line);
    seats[index] = seat;
    (void)++index;
    solve_part_one(&seat, &part_one_answer);
  }

  solve_part_two(seats, &index, &part_two_answer);

  fclose(file);

  printf("Part one answer: %d\n", part_one_answer);
  printf("Part two answer: %d\n", part_two_answer);

  return 0;
}
