#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void line_fields(
  char *line,
  char **fields,
  unsigned char fields_count,
  unsigned char *field_index
) {
  char sep[3] = ": ";
  char *token = strtok(line, sep);
  unsigned char index = 0;

  while(token != NULL) {
    if (index % 2 == 0 && *field_index < fields_count) {
      const size_t len = strlen(token);
      fields[*field_index] = (char *)malloc(len * sizeof(char));
      (void)strcpy(fields[*field_index], token);
      (*field_index)++;
    }
    token = strtok(NULL, sep);
    index++;
  }
}

unsigned char check_fields(
  char **fields,
  unsigned char fields_count,
  const char *required_fields[7],
  const char *optional_fields[1]
) {
  const size_t len = 8;
  char *checks = (char *)malloc(len * sizeof(char));
  for (unsigned char i = 0; i < len; i++) {
    const char *pattern = i < 7 ? required_fields[i] : optional_fields[0];
    checks[i] = 0;
    if (i == 7) {
      checks[i] = 1;
      continue;
    }
    for (unsigned char j = 0; j < fields_count; j++) {
      if ((int)fields[j] && !strcmp(pattern, fields[j])) {
        checks[i] = 1;
      }
    }
  }
  for (unsigned char i = 0; i < len; i++) {
    if (!checks[i]) {
      return 0;
    }
  }
  free(checks);
  return 1;
}

void solve_part_one(
  FILE *file,
  const char *required_fields[7],
  const char *optional_fields[1]
) {
  char line[256];
  unsigned int valid_count = 0;
  const unsigned char fields_count = 8;
  unsigned char field_index = 0;
  char **fields = malloc((size_t)fields_count * sizeof(char *));

  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '\n') {
      if (field_index < fields_count) {
        for (int j = field_index; j < fields_count; j++) {
          fields[j] = 0;
        }
      }

      const unsigned char valid = check_fields(
        fields,
        fields_count,
        required_fields,
        optional_fields
      );
      if (valid) {
        valid_count++;
      }

      field_index = 0;
      continue;
    }
    line_fields(line, fields, fields_count, &field_index);
  }

  printf("Part 1: %d\n", valid_count);

  for (int i = 0; i < fields_count; i++) {
    free(fields[i]);
  }
  free(fields);
}

void solve_part_two(
  FILE *file,
  const char *required_fields[1],
  const char *optional_fields[7]
) {
  puts("Part 2: Not implemented");
}

int main(int argc, char *argv[]) {
  const char *optional_fields[1] = {
    "cid"
  };
  const char *required_fields[7] = {
    "byr",
    "iyr",
    "eyr",
    "hgt",
    "hcl",
    "ecl",
    "pid"
  };

  if (argc < 2) {
    puts("Missing 'filename' parameter");
    return 1;
  }

  FILE *file = fopen(argv[1], "r");

  if (file == NULL) {
    printf("%s file does not exists", argv[1]);
    return 1;
  }

  solve_part_one(file, required_fields, optional_fields);
  rewind(file);
  solve_part_two(file, required_fields, optional_fields);

  fclose(file);

  return 0;
}
