TARGET = s21_cat

CC = gcc
CFLAGS = -Werror -Wall -Wextra -std=c11 -std=c11

SRC = s21_cat.c

s21_cat: $(TARGET)

$(TARGET): $(SRC) 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean: 
	rm -rf: $(TARGET)

rebuild: clean all