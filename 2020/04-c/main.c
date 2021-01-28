#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *keys[8] = {
  "byr",
  "iyr",
  "eyr",
  "hgt",
  "hcl",
  "ecl",
  "pid",
  "cid"
};

int get_key_index(char *key) {
  for(int i = 0; i < 8; i++) {
    if (!strcmp(key, keys[i])) {
      return i;
    }
  }
  return -1;
};

unsigned int prepare_input(char *line, char **fields) {
  if (line[0] == '\n') {
    return 1;
  }

  const size_t line_length = strlen(line);
  if (line[line_length - 1] == '\n') {
    line[line_length - 1] = '\0';
  }

  char sep[3] = ": ";
  char *token = strtok(line, sep);
  unsigned int index = 0;
  int key_index = -1;

  while(token != NULL) {
    if (index % 2 == 0) {
      key_index = get_key_index(token);
    } else {
      if (key_index != -1) {
        (void)strcpy(fields[key_index], token);
      }
      key_index = -1;
    }
    token = strtok(NULL, sep);
    (void)index++;
  }

  return 0;
};

int check_is_hex_color(char *field) {
  if (strlen(field) != 7) {
    return 0;
  }
  const char prefix;
  char *color = malloc(6 * sizeof(char));
  (void)strncpy(color, field + 1, 6);
  if (color[strspn(color, "0123456789abcdef")] == 0) {
    return 1;
  }
  return 0;
}

int check_is_eye_color(char *field) {
  const char *variants[7] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
  for (int i = 0; i < 7; i++) {
    if (!strcmp(variants[i], field)) {
      return 1;
    }
  }
  return 0;
}

int check_is_passport_id(char *field) {
  size_t length = strlen(field);
  if (length != 9) {
    return 0;
  }
  for (int i = 0; i < length; i++) {
    if (!isdigit(field[i])) {
      return 0;
    }
  }
  return 1;
}

void solve_part_one(char **fields, unsigned int *answer) {
  size_t valid_count = 0;
  for(int i = 0; i < 8; i++) {
    if (fields[i] != NULL && strlen(fields[i]) > 0) {
      valid_count++;
    }
  }
  if (valid_count == 8 || (valid_count == 7 && strlen(fields[7]) == 0)) {
    (*answer)++;
  }
};

void solve_part_two(char **fields, unsigned int *answer) {
  unsigned int result[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int is_valid = 1;
  int numeric_value = 0;

  for (int i = 0; i < 8; i++) {
    switch (i) {
      case 0:
        numeric_value = atoi(fields[i]);
        if (numeric_value > 1919 && numeric_value < 2003) {
          result[i] = 1;
        }
        numeric_value = 0;
        break;
      case 1:
        numeric_value = atoi(fields[i]);
        if (numeric_value > 2009 && numeric_value < 2021) {
          result[i] = 1;
        }
        numeric_value = 0;
        break;
      case 2:
        numeric_value = atoi(fields[i]);
        if (numeric_value > 2019 && numeric_value < 2031) {
          result[i] = 1;
        }
        numeric_value = 0;
        break;
      case 3:
        if ((strstr(fields[i], "cm")) != NULL) {
          int value = atoi(fields[i]);
          if (value > 149 && value < 194) {
            result[i] = 1;
          }
        } else if ((strstr(fields[i], "in")) != NULL) {
          int value = atoi(fields[i]);
          if (value > 58 && value < 77) {
            result[i] = 1;
          }
        }
        break;
      case 4:
        if (check_is_hex_color(fields[i])) {
          result[i] = 1;
        }
        break;
      case 5:
        if (check_is_eye_color(fields[i])) {
          result[i] = 1;
        }
        break;
      case 6:
        if (check_is_passport_id(fields[i])) {
          result[i] = 1;
        }
        break;
      case 7:
      default:
        break;
    }
  }

  for (int i = 0; i < 7; i++) {
    if (!result[i]) {
      is_valid = 0;
    }
  }

  if (is_valid) {
    (*answer)++;
  }
};

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

  char line[256];
  char *fields[8];
  unsigned int part_one_answer = 0;
  unsigned int part_two_answer = 0;

  for (int i = 0; i < 8; i++) {
    fields[i] = malloc(16 * sizeof(char));
  }

  while (fgets(line, sizeof(line), file)) {
    unsigned int new_input = prepare_input(line, fields);
    if (!new_input) {
      continue;
    }

    solve_part_one(fields, &part_one_answer);
    solve_part_two(fields, &part_two_answer);

    for (int i = 0; i < 8; i++) {
      (void)strncpy(fields[i], "", 16);
    }
  }

  for (int i = 0; i < 8; i++) {
    free(fields[i]);
  }

  fclose(file);

  printf("Part one answer: %d\n", part_one_answer);
  printf("Part two answer: %d\n", part_two_answer);

  return 0;
}
