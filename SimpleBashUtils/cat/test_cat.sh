make s21_cat > /dev/null 2>&1
mkdir files > /dev/null 2>&1

compare_output() {
    local test_description=$1
    local flags=$2
    local input_file=$3

    echo "Тест: $test_description... "

    ./s21_cat $flags $input_file > my_cat_output.txt

    cat $flags $input_file > cat_output.txt

    if diff -u my_cat_output.txt cat_output.txt > diff_output.txt; then
        echo "Успешно"
    else
        echo "Ошибка"
        echo "Разница:"
        cat diff_output.txt
    fi

    rm -f my_cat_output.txt cat_output.txt diff_output.txt
}

echo "The first line\n\nThe second line\twith tabs\n\n" > files/test_input.txt
echo "\n\n\n" > files/test_blank.txt

compare_output "Без флагов" "" "files/test_input.txt"
compare_output "Флаг -b (нумерация непустых строк)" "-b" "files/test_input.txt"
compare_output "Флаг -e (показывает символы конца строки $)" "-e" "files/test_input.txt"
compare_output "Флаг -n (нумерация всех строк)" "-n" "files/test_input.txt"
compare_output "Флаг -s (удаление пустых строк)" "-s" "files/test_blank.txt"
compare_output "Флаг -t (отображение табуляций)" "-t" "files/test_input.txt"

rm -rf files > /dev/null 2>&1
make clean > /dev/null 2>&1
