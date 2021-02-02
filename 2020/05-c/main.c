#include <math.h>
#include <stdio.h>
#include <string.h>

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

int get_col(char line[RAW_INPUT_LENGTH]) {
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

void solve_part_one(char line[RAW_INPUT_LENGTH], unsigned int *part_one_answer) {
  const unsigned int row = get_row(line);
  const unsigned int col = get_col(line);
  const unsigned int max = row * 8 + col;
  if (max > (*part_one_answer)) {
    (*part_one_answer) = max;
  }
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

  unsigned int part_one_answer = 0;
  unsigned int part_two_answer = 0;

  char line[RAW_INPUT_LENGTH];

  while (fgets(line, sizeof(line) + 1, file)) {
    line[RAW_INPUT_LENGTH - 1] = '\0';
    solve_part_one(line, &part_one_answer);
  }

  fclose(file);

  printf("Part one answer: %d\n", part_one_answer);
  printf("Part two answer: %d\n", part_two_answer);

  return 0;
}
