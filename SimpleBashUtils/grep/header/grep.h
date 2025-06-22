#ifndef GREP_H
#define GREP_H

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool flag_e;  // Шаблон
  bool flag_i;  // Игнорировать регистр
  bool flag_v;  // Инвертировать совпадения
  bool flag_c;  // Подсчитывать совпадения
  bool flag_l;  // Выводить только имена файлов
  bool flag_n;  // Нумерация строк
  bool flag_h;  // Не показывать имена файлов
  bool flag_s;  // Подавлять ошибки
  bool flag_f;  // Чтение шаблонов из файла
  bool flag_o;  // Печать совпадений

  char *pattern;   // Основной шаблон
  char **files;    // Список файлов
  int file_count;  // Количество файлов
} GrepOptions;

int parse_and_execute(int argc, char *argv[]);
void execute_grep(const GrepOptions *options);
char *load_patterns_from_file(const char *filename);
int handle_flag(char flag, GrepOptions *options);

#endif
