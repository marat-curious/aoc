#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void find_matches(const char *line, size_t *s_index, size_t *e_index, char *letter, char *password) {
  const char *pattern = "^(.*[0-9])-(.*[0-9]) ([a-z]): (.*[0-9a-zA-Z])";
  regex_t re;
  int rc;

  if ((rc = regcomp(&re, pattern, REG_EXTENDED))) {
    puts("Could not compile regex");
  }

  regmatch_t *matches = malloc(sizeof(regex_t) * (re.re_nsub + 1));

  if ((rc = regexec(&re, line, re.re_nsub + 1, matches, 0))) {
    puts("No match");
  } else {
    for (int i = 0; i < re.re_nsub + 1; i++) {
      size_t len = (size_t)(matches[i].rm_eo - matches[i].rm_so);
      char *buff = malloc(sizeof(char) * len + 1);
      (void)strncpy(buff, &line[matches[i].rm_so], len + 1);
      buff[len] = '\0';

      switch (i) {
        case 1:
          *s_index = atoi(buff);
          break;
        case 2:
          *e_index = atoi(buff);
          break;
        case 3:
          *letter = buff[0];
          break;
        case 4:
          strcpy(password, buff);
          break;
        default:
          continue;
      }
      free(buff);
    }
  }

  free(matches);
  regfree (&re);
}

void solve_part_one(FILE *file) {
  size_t valid = 0;
  char line[51];

  size_t s_index;
  size_t e_index;
  char letter;

  while(!feof(file)) {
    if (fgets(line, 50, file)) {
      char *password = malloc(sizeof(char) * 51);

      find_matches(line, &s_index, &e_index, &letter, password);

      size_t i = 0;
      size_t count = 0;
      while (password[i] != '\0') {
        if (password[i] == letter) {
          count++;
        }
        i++;
      }

      if (count >= s_index && count <= e_index) {
        valid++;
      }

      free(password);
    }
  }

  printf("Answer: %zu\n", valid);
}

void solve_part_two(FILE *file) {
  size_t valid = 0;
  char line[51];

  while(!feof(file)) {
    if (fgets(line, 50, file)) {
      size_t s_index;
      size_t e_index;
      char letter;
      char *password = malloc(sizeof(char) * 51);

      find_matches(line, &s_index, &e_index, &letter, password);

      if ((password[s_index - 1] == letter && password[e_index - 1] != letter)
        || (password[s_index - 1] != letter && password[e_index - 1] == letter)) {
        valid++;
      }

      free(password);
    }
  }

  printf("Answer: %zu\n", valid);
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

  puts("Part 1:");
  solve_part_one(file);

  rewind(file);

  puts("\nPart 2:");
  solve_part_two(file);

  fclose(file);

  return 0;
}
