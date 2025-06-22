#include "../header/grep.h"

// Загрузка шаблонов из файла для флага -f
char *load_patterns_from_file(const char *filename) {
  FILE *pattern_file = fopen(filename, "r");
  if (!pattern_file) {
    perror("Error opening pattern file");
    return NULL;
  }

  char *patterns = NULL;
  size_t total_size = 0;
  char line[1024];

  while (fgets(line, sizeof(line), pattern_file)) {
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
      line[len - 1] = '\0';  // Убираем перенос строки

    total_size += len + 1;
    char *new_patterns = realloc(patterns, total_size);
    if (!new_patterns) {
      perror("Memory allocation failed");
      fclose(pattern_file);
      free(patterns);
      return NULL;
    }

    patterns = new_patterns;
    if (total_size == len + 1) {
      strcpy(patterns, line);
    } else {
      strcat(patterns, "|");
      strcat(patterns, line);
    }
  }

  fclose(pattern_file);

  if (!patterns) {
    fprintf(stderr, "Pattern file is empty\n");
    return NULL;
  }

  return patterns;
}

// Основная функция разбора аргументов и выполнения grep
int parse_and_execute(int argc, char *argv[]) {
  GrepOptions options = {0};
  options.files = malloc(argc * sizeof(char *));
  if (!options.files) {
    perror("Memory allocation failed");
    return EXIT_FAILURE;
  }
  int file_index = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      for (size_t j = 1; argv[i][j] != '\0'; j++) {
        int result = handle_flag(argv[i][j], &options);
        if (result == -1) {
          if (!options.flag_s)
            fprintf(stderr, "Unknown flag: -%c\n", argv[i][j]);
          free(options.files);
          return EXIT_FAILURE;
        }
      }
    } else if (!options.pattern && !options.flag_f) {
      options.pattern = argv[i];
    } else if (options.flag_f && !options.pattern) {
      options.pattern = argv[i];
    } else {
      options.files[file_index++] = argv[i];
    }
  }
  options.file_count = file_index;
  if (!options.pattern) {
    if (!options.flag_s) fprintf(stderr, "Pattern is required\n");
    free(options.files);
    return EXIT_FAILURE;
  }
  if (options.flag_f) {
    char *patterns = load_patterns_from_file(options.pattern);
    if (!patterns) {
      free(options.files);
      return EXIT_FAILURE;
    }
    options.pattern = patterns;
  }
  execute_grep(&options);
  if (options.flag_f) free((void *)options.pattern);
  free(options.files);
  return EXIT_SUCCESS;
}

// Выполнение grep с заданными параметрами
void execute_grep(const GrepOptions *options) {
  regex_t regex;
  int regex_flags = REG_EXTENDED;
  if (options->flag_i) regex_flags |= REG_ICASE;

  // Оптимизация: если -o не указан, используем REG_NOSUB для ускорения
  if (!options->flag_o) regex_flags |= REG_NOSUB;

  if (regcomp(&regex, options->pattern, regex_flags)) {
    if (!options->flag_s) fprintf(stderr, "Failed to compile regex\n");
    return;
  }

  for (int i = 0; i < options->file_count; i++) {
    FILE *file = fopen(options->files[i], "r");
    if (!file) {
      if (!options->flag_s) perror(options->files[i]);
      continue;
    }

    char buffer[1024];
    int line_number = 0, match_count = 0;
    bool file_matched = false;

    while (fgets(buffer, sizeof(buffer), file)) {
      line_number++;
      bool match_found = false;

      if (options->flag_o) {
        // Режим -o: ищем все совпадения в строке
        const char *cursor = buffer;
        regmatch_t match;
        while (regexec(&regex, cursor, 1, &match, 0) == 0) {
          match_found = true;
          file_matched = true;
          match_count++;

          // Вывод для каждого совпадения:
          if (!options->flag_c && !options->flag_l) {
            if (!options->flag_h && options->file_count > 1)
              printf("%s:", options->files[i]);
            if (options->flag_n) printf("%d:", line_number);
            printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                   cursor + match.rm_so);
          }

          cursor += match.rm_eo;  // Перемещаем курсор дальше
        }
      } else {
        // Обычный режим (без -o)
        regmatch_t match;
        match_found = regexec(&regex, buffer, 1, &match, 0) == 0;
        if (options->flag_v) match_found = !match_found;

        if (match_found) {
          file_matched = true;
          match_count++;
          if (!options->flag_c && !options->flag_l) {
            if (options->flag_n) printf("%d:", line_number);
            if (!options->flag_h && options->file_count > 1)
              printf("%s:", options->files[i]);
            printf("%s", buffer);
          }
        }
      }
    }

    if (options->flag_c) printf("%d\n", match_count);
    if (options->flag_l && file_matched) printf("%s\n", options->files[i]);
    fclose(file);
  }

  regfree(&regex);
}

// Определение флага
int handle_flag(char flag, GrepOptions *options) {
  switch (flag) {
    case 'e':
      options->flag_e = true;
      break;
    case 'i':
      options->flag_i = true;
      break;
    case 'v':
      options->flag_v = true;
      break;
    case 'c':
      options->flag_c = true;
      break;
    case 'l':
      options->flag_l = true;
      break;
    case 'n':
      options->flag_n = true;
      break;
    case 'h':
      options->flag_h = true;
      break;
    case 's':
      options->flag_s = true;
      break;
    case 'f':
      options->flag_f = true;
      break;
    case 'o':
      options->flag_o = true;
      break;
    default:
      return -1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: s21_grep [OPTIONS] PATTERN [FILE...]\n");
    return EXIT_FAILURE;
  }

  return parse_and_execute(argc, argv);
}
