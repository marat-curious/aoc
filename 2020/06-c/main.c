#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH 81
#define MIN_INPUT_LENGTH 11

/*
 * Each character is represented by a unique integer value in the range [0, 127].
 * This numeric value is also known as the ASCII value of character.
 */

int count_uniq_char(char *input) {
  const size_t input_length = strlen(input);

  int count = 0;
  int hash[128] = { 0 };

  for (int i = 0; i < input_length; i++) {
    hash[input[i]] = 1;
  }

  for (int i = 0; i < 128; i++) {
    count += hash[i];
  }

  return count;
}

void solve_part_one(char *input, unsigned int *answer) {
  const int uniq_chars = count_uniq_char(input);
  *answer += uniq_chars;
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

  char line[LINE_LENGTH];
  char *input = (char *)malloc(MIN_INPUT_LENGTH * sizeof(char));

  while(fgets(line, sizeof(line), file)) {
    const size_t len = strlen(line);
    if (len == 1 && line[0] == '\n') {
      solve_part_one(input, &part_one_answer);
      *input = '\0';
      continue;
    }
    if (len > 1 && line[len - 1] == '\n') {
      line[len - 1] = '\0';
    }
    if ((strlen(input) + len) >= MIN_INPUT_LENGTH) {
      input = (char *)realloc(input, (strlen(input) * sizeof(char)) + (len * sizeof(char)));
    }
    (void)strcat(input, line);
  }

  free(input);
  fclose(file);

  printf("Part 1 answer: %u\n", part_one_answer);
  printf("Part 2 answer: %u\n", part_two_answer);

  return 0;
}
