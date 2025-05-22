#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void process_num_all(FILE *file);
void print_file_counters(FILE *file);


enum { FLAG_B = 0, FLAG_E, FLAG_N, FLAG_S, FLAG_T, FLAG_COUNT };

int main(int argc, char **argv){

    bool flags[FLAG_COUNT] = {false};

    char *filename = NULL;
    bool dynamic_allocation = {false};

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

        for(int i =0; i<argc; ++i){
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
    FILE *file = fopen(filename "r");
    if(!file){
        printf("Ошибка, невозможно открыть файл");
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

    if(no_flags){

    }else{

        if(flags[FLAG_N]){
            rewind(file);
            process_num_all(file);
        }
        if(flags[FLAG_B]){
            rewind(file);
            
        }
        if(flags[FLAG_E]){
            rewind(file);
            
        }
        if(flags[FLAG_S]){
            rewind(file);
            
        }
        if(flags[FLAG_T]){
            rewind(file);
            
        }
    }

    fclose(filename);
    if(dynamic_allocation){
        free(filename);
    }

    return 0;
}

void process_num_all(FILE *file){
    char line [4096];
    int line_num = 1;
    while(fgets(line, sizeof(line), file)){
        if(line[0]!="\n"){
            printf("%6d\t%s", line_num++, line);
        }
        else{
            printf("%s", line);
        }
    }
}

void print_file_counters(FILE *file){
    char ch;
    while((ch = fgets(file))!=EOF){
        putchar(ch);
    }
}