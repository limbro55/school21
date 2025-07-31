TARGET = string
SOURCES = $(wildcard ./sources/*.c)
OBJ_LIBRARY = $(patsubst %.c, %.o, $(SOURCES))
TEST_C_FILES = tests/s21_test.c
TEST_FLAGS = $(shell pkg-config --cflags --libs check)
BUILD_PATH = ./build/
COVERAGE_INFO = coverage.info
REPORT_DIR = report/
GCC_FLAGS = -Wall -Werror -Wextra -std=c11 -pthread -pthread -lrt -lm -lsubunit -lcheck
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	TEST_FLAGS += $(shell pkg-config --cflags --libs check)
endif

all:
	make clean
	make gcov_report
	make test
	make s21_string.a

test: $(OBJ_LIBRARY) $(TEST_C_FILES)
	gcc $(GCC_FLAGS) $(TEST_C_FILES) $(OBJ_LIBRARY) -o s21_test $(TEST_FLAGS)
	./s21_test

clean:
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +
	find . -type f \( -name "*.o" -o -name "*.gcda" -o -name "*.gcno" \) -exec rm -f {} +
	rm -rf s21_test s21_string.a
	rm -rf build

s21_string.a: $(OBJ_LIBRARY)
	ar rcs s21_string.a $(OBJ_LIBRARY)
	ranlib s21_string.a

gcov_report: $(OBJ_LIBRARY) $(TEST_C_FILES)
	mkdir -p $(BUILD_PATH)$(REPORT_DIR)
	gcc $(GCC_FLAGS) $(GCOV_FLAGS) $(TEST_C_FILES) ./sources/*.c -o $(BUILD_PATH)s21_test $(TEST_FLAGS)
	$(BUILD_PATH)s21_test
	lcov -t "Coverage Report" -c -d . --output-file $(BUILD_PATH)$(COVERAGE_INFO)
	genhtml $(BUILD_PATH)$(COVERAGE_INFO) --output-directory $(BUILD_PATH)$(REPORT_DIR)
ifeq ($(UNAME_S), Darwin)
	open $(BUILD_PATH)$(REPORT_DIR)/index.html
else
	@echo "Откройте отчет вручную: $(BUILD_PATH)$(REPORT_DIR)/index.html"
endif
