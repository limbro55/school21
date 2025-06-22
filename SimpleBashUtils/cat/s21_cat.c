#include "s21_cat.h"

Config *alloc_config(void) { return (Config *)malloc(sizeof(Config)); }

void init_config(Config *cfg) {
  if (!cfg) {
    fputs("error: cannot init config\n", stderr);
    return;
  }
  *cfg = (Config){0};
}

Config *get_config(int argc, char **argv) {
  Config *cfg = alloc_config();
  init_config(cfg);

  int opt;
  const struct option long_opts[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "eEtTbsnv", long_opts, NULL)) != -1) {
    switch (opt) {
      case 'e':
        cfg->e = cfg->v = true;
        break;
      case 'E':
        cfg->e = true;
        break;
      case 't':
        cfg->t = cfg->v = true;
        break;
      case 'T':
        cfg->t = true;
        break;
      case 'b':
        cfg->b = true;
        break;
      case 's':
        cfg->s = true;
        break;
      case 'n':
        cfg->n = true;
        break;
      case 'v':
        cfg->v = true;
        break;
      default:
        fprintf(stderr, "Unknown option: %s\n", argv[optind - 1]);
    }
  }
  if (cfg->b) cfg->n = false;
  return cfg;
}

void free_config(Config *cfg) { free(cfg); }

bool should_skip_line(int ch, int prev_ch, bool *prev_blank,
                      const Config *cfg) {
  if (!cfg->s) return false;

  if (prev_ch == '\n' && ch == '\n') {
    if (*prev_blank) return true;
    *prev_blank = true;
  } else {
    *prev_blank = false;
  }
  return false;
}

void print_line_number(int ch, int prev_ch, const Config *cfg,
                       int *line_number) {
  if (!(cfg->b || cfg->n)) return;
  if (prev_ch != '\n') return;
  if (cfg->b && ch == '\n') return;

  printf("%6d\t", *line_number);
  ++*line_number;
}

void print_visible_char(int ch, const Config *cfg) {
  if (cfg->e && ch == '\n') {
    putchar('$');
    putchar('\n');
  } else if (cfg->t && ch == '\t') {
    putchar('^');
    putchar('I');
  } else if (cfg->v && (ch < 32 || ch == 127) && ch != '\t' && ch != '\n') {
    putchar('^');
    putchar(ch == 127 ? '?' : ch + 64);
  } else {
    putchar(ch);
  }
}

void process_file(FILE *file, const Config *cfg, int *line_number) {
  if (!file) return;

  int ch, prev_ch = '\n';
  bool prev_blank = false;

  while ((ch = fgetc(file)) != EOF) {
    if (should_skip_line(ch, prev_ch, &prev_blank, cfg)) continue;

    print_line_number(ch, prev_ch, cfg, line_number);
    print_visible_char(ch, cfg);
    prev_ch = ch;
  }
}

FILE *open_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) perror(filename);
  return file;
}

void print_file(const char *filename, const Config *cfg, int *line_number) {
  FILE *file = open_file(filename);
  process_file(file, cfg, line_number);
  if (file) fclose(file);
}

void s21_cat(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [FILE...]\n", argv[0]);
    return;
  }

  Config *cfg = get_config(argc, argv);
  int line_number = 1;

  for (int i = optind; i < argc; ++i) print_file(argv[i], cfg, &line_number);

  free_config(cfg);
}

int main(int argc, char **argv) { s21_cat(argc, argv); }
