#include <stdio.h>
#include <string.h>

unsigned int traverse_map(FILE *file, unsigned char dx, unsigned char dy) {
  char line[256];
  unsigned int line_index = 0;
  unsigned int index = 0;
  size_t count = 0;

  while(fgets(line, sizeof(line), file)) {
    if ((line_index % dy) != 0) {
      line_index++;
      continue;
    }
    const size_t len = strlen(line);
    if (line[index] == '#') {
      count++;
    }
    index = (index + dx) % (len - 1);
    line_index++;
  }

  return count;
}

void solve_part_one(FILE *file) {
  const unsigned int answer = traverse_map(file, 3, 1);
  printf("Part 1: %d\n", answer);
}

void solve_part_two(FILE *file) {
  const unsigned char variants[5][2] = {{ 1, 1 }, { 3, 1 }, { 5, 1 }, { 7, 1 }, { 1, 2 }};
  unsigned int answer = 1;
  for (int i = 0; i < 5; i++) {
    const unsigned int count = traverse_map(file, variants[i][0], variants[i][1]);
    answer *= count;
    rewind(file);
  }
  printf("Part 2: %d\n", answer);
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

  solve_part_one(file);

  rewind(file);

  solve_part_two(file);

  fclose(file);

  return 0;
}
