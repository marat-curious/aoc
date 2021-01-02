#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

#define SUM 2020

int get_lines_count(FILE *file) {
  int lines = 0;
  int ch;

  lines++;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      lines++;
    }
  }

  return lines - 1;
}

void read_lines_to_array(FILE *file, int *arr) {
  int num;
  int i = 0;
  while(fscanf(file, "%d", &num) == 1) {
    arr[i] = num;
    i++;
  }
}

void solve_part_one(int count, int *inputs) {
  int l = 0;
  int r = count - 1;

  while (l < r) {
    if ((inputs[l] + inputs[r]) == SUM) {
      printf("entries: %d, %d\n", inputs[l], inputs[r]);
      printf("answer: %d\n", inputs[l] * inputs[r]);
      break;
    }

    if (inputs[l] + inputs[r] < SUM) {
      l++;
    } else {
      r--;
    }
  }
}

void solve_part_two(int count, int *inputs) {
  int l;
  int r;

  for (int i = 0; i < count - 2; i++) {
    l = i + 1;
    r = count - 1;
    while (l < r) {
      if ((inputs[i] + inputs[l] + inputs[r]) == SUM) {
        printf("entries: %d, %d, %d\n", inputs[i], inputs[l], inputs[r]);
        printf("answer: %d\n", inputs[i] * inputs[l] * inputs[r]);
        break;
      }

      if (inputs[i] + inputs[l] + inputs[r] < SUM) {
        l++;
      } else {
        r--;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    puts("missing 'filename' parameter");
    return 1;
  }

  FILE *file = fopen(argv[1], "r");

  if (file == NULL) {
    printf("%s file does not exists", argv[1]);
    return 1;
  }

  int lines = get_lines_count(file);

  int *inputs = malloc(lines * sizeof(int));
  if (inputs== NULL) {
    puts("malloc failed");
    return 1;
  }

  rewind(file);
  read_lines_to_array(file, inputs);

  bubble_sort(lines, inputs);

  puts("Part 1:");
  solve_part_one(lines, inputs);

  puts("\nPart 2:");
  solve_part_two(lines, inputs);

  free(inputs);
  fclose(file);

  return 0;
}
