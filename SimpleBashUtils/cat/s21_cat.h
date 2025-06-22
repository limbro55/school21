#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
} Config;

Config *alloc_config(void);
void init_config(Config *cfg);
Config *get_config(int argc, char **argv);
void free_config(Config *cfg);

bool should_skip_line(int ch, int prev_ch, bool *prev_blank, const Config *cfg);

void print_line_number(int ch, int prev_ch, const Config *cfg,
                       int *line_number);

void print_visible_char(int ch, const Config *cfg);

void process_file(FILE *file, const Config *cfg, int *line_number);
FILE *open_file(const char *filename);
void print_file(const char *filename, const Config *cfg, int *line_number);

void s21_cat(int argc, char **argv);

#endif
