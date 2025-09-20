CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -I.
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CLIBS = -lcheck -lm -lsubunit -lpthread -lrt
else ifeq ($(UNAME_S), Darwin)
    CLIBS = -lcheck -lm
endif

SRC = $(wildcard s21_*.c)
OBJ_DIR = obj
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

TEST_DIR = tests
TESTS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TESTS))
TEST_TARGET = $(TEST_DIR)/s21_test.out

all: clean s21_decimal.a

s21_decimal.a: $(OBJ)
	ar rcs $@ $^

clean:
	rm -rf coverage_report $(OBJ_DIR) debug.dSYM
	rm -f s21_decimal.a debug $(TEST_TARGET) *.gcda *.gcno

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: clean s21_decimal.a $(TEST_OBJ)
	@mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_TARGET) s21_decimal.a $(CLIBS)
	@echo "-------------------------"
	@echo "\033[32mРезультаты тестов:\033[0m"
	@echo "-------------------------"
	@./$(TEST_TARGET)

gcov_report: clean
	@mkdir -p $(OBJ_DIR)
	$(foreach src, $(SRC), $(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(src) -o $(OBJ_DIR)/$(notdir $(src:.c=.o));)
	ar rcs s21_decimal.a $(OBJ)
	
	@mkdir -p $(OBJ_DIR) $(TEST_DIR)
	$(foreach test, $(TESTS), $(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(test) -o $(OBJ_DIR)/$(notdir $(test:.c=.o));)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_TARGET) s21_decimal.a $(GCOV_FLAGS) $(CLIBS)
	./$(TEST_TARGET)
	
	lcov --capture --directory . --output-file $(OBJ_DIR)/coverage.info
	lcov --remove $(OBJ_DIR)/coverage.info "/Library/Developer/CommandLineTools/SDKs/*" "/usr/include/*" --output-file $(OBJ_DIR)/filtered_coverage.info --ignore-errors unused
	genhtml $(OBJ_DIR)/filtered_coverage.info --output-directory coverage_report
	@echo "Генерация отчета gcov завершена."
	open ./coverage_report/index.html

.PHONY: all clean test gcov_report debug

debug: CFLAGS += -g
debug: test

clang:
	cp ../materials/linters/.clang-format ./ 
	clang-format -i *.c *.h $(TEST_DIR)/*.c 
	clang-format -n *.c *.h $(TEST_DIR)/*.c 
	rm .clang-format