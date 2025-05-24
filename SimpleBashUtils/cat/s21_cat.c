#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_num_all(FILE *file);
void process_num_zero(FILE *file);
void print_file_contents(FILE *file);
void process_show_ends(FILE *file);
void process_show_tab(FILE *file);
void process_squeeze_blank(FILE *file);
char *read_string(int *length);

enum { FLAG_B = 0, FLAG_E, FLAG_N, FLAG_S, FLAG_T, FLAG_COUNT };

int main(int argc, char **argv){

    bool flags[FLAG_COUNT] = {false};

    char *filename = NULL;
    bool dynamic_allocation = false;

    if(argc < 2){
        int len = 0;
        filename = read_string(&len);
        if(filename == NULL){
            printf("Ошибка: Невозмоно считать путь файла. \n");
            return 1;
        }

        dynamic_allocation = true;
    }else{
        int file_st = 0;

        for(int i = 1; i<argc; ++i){
            if(argv[i][0] == '-'){
                for(size_t j = 1; argv[i][j] != '\0'; ++j){
                    switch (argv[i][j]) {
                        case 'b':
                            flags[FLAG_B] = true;
                            break;
                        case 'e':
                            flags[FLAG_E] = true;
                            break;
                        case 'n':
                            flags[FLAG_N] = true;
                            break;
                        case 's':
                            flags[FLAG_S] = true;
                            break;
                        case 't':
                            flags[FLAG_T] = true;
                            break;
                        default:
                            printf("Ошибка, неверный флаг -%c\n", argv[i][j]);
                            return 1;
                    }

                }
            } else{
                file_st = i;
                break;
            }
        }
        if(file_st>=argc){
            printf("Ошибка, не удалось указать путь.\n");
            return 1;
        }
        filename = argv[file_st];
    }
    FILE *file = fopen(filename, "r");
    if(!file){
        printf("Ошибка, невозможно открыть файл \"%s\"\n", filename);
        if(dynamic_allocation){
            free(filename);
        }
        return 1;
    }
    //Если не указали флаги просто выводим содиржимое

    bool no_flags = true;
    for(int i = 0; i < FLAG_COUNT; i++){
        if(flags[i]){
            no_flags = false;
            break;
        }
    }

    if (no_flags) {
    print_file_contents(file);
  } else {
    if (flags[FLAG_S]) {
      rewind(file);
      process_squeeze_blank(file);
    }
    if (flags[FLAG_B]) {
      rewind(file);
      process_num_zero(file);
    }
    if (flags[FLAG_N]) {
      rewind(file);
      process_num_all(file);
    }
    if (flags[FLAG_E]) {
      rewind(file);
      process_show_ends(file);
    }
    if (flags[FLAG_T]) {
      rewind(file);
      process_show_tab(file);
    }
  }

    fclose(file);
    if (dynamic_allocation) {
        free(filename);
  }

    return 0;
}

void process_num_all(FILE *file){
    char line[4096];
    int line_num = 1;
    while(fgets(line, sizeof(line), file)){
        printf("%6d\t%s", line_num++, line);
    }
}

void process_num_zero(FILE *file){
    char line [4096];
    int line_num = 1;
    while(fgets(line, sizeof(line), file)){
        if(line[0]!='\n'){
            printf("%6d\t%s", line_num++, line);
        }
        else{
            printf("%s", line);
        }
    }
}

void print_file_contents(FILE *file){
    char ch;
    while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
  }
}

void process_show_ends(FILE *file){
    char ch;
    while((ch = fgetc(file))!= EOF){
        if(ch == '\n'){
            printf("$\n");
        }else{
            putchar(ch);
        }
    }
}

void process_show_tab(FILE *file) {
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\t') {
      printf("^I");
    } else if (ch == '\n') {
      printf("\n");
    } else {
      putchar(ch);
    }
  }
}

void process_squeeze_blank(FILE *file) {
  char line[4096];
  bool last_was_blank = false;

  while (fgets(line, sizeof(line), file)) {
    if (line[0] == '\n') {
      if (!last_was_blank) {
        printf("%s", line);
      }
      last_was_blank = true;
    } else {
      printf("%s", line);
      last_was_blank = false;
    }
  }
}

char *read_string(int *length) {
  int size = 1;
  char *str = (char *)malloc(size * sizeof(char));
  if (str == NULL) {
    printf("Ошибка выделения памяти.\n");
    return NULL;
  }

  int len = 0;
  printf("Введите путь к файлу: ");
  while (1) {
    char ch = getchar();
    if (ch == '\n') {
      break;
    }
    if (len >= size) {
      size *= 2;
      char *temp = (char *)realloc(str, size * sizeof(char));
      if (temp == NULL) {
        printf("Ошибка переаллокации памяти.\n");
        free(str);
        return NULL;
      }
      str = temp;
    }
    str[len++] = ch;
  }
  str[len] = '\0';
  *length = len;
  return str;
}