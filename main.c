#include "tasks/matrix_transposition.h"
#include "tasks/convert_float_num.h"
#include "tasks/evaluate_expression.h"
#include "tasks/special_word.h"
#include "tasks/leave_longest_word .h"
#include "tasks/remove_polynomial.h"
#include "tasks/rearrange_numbers.h"
#include "tasks/transpose_non_symmetric_matrix.h"

int main() {
    // 1
    generate_random_matrix_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_1_test_0.txt", 3);
    test_matrix_transpose();
    printf("Exercise 1 - OK\n");
    // 2
    generate_float_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_2_test_0.txt", 10);
    test_convert_float();
    printf("Exercise 2 - OK\n");
    // 3
    generate_expression("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_3_test_0.txt");
    test_evaluate();
    printf("Exercise 3 - OK\n");
    // 4
    generate_string("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_4_test_0.txt", "abcde abcde");
    test_filter_word();
    printf("Exercise 4 - OK\n");
    // 5
    generate_text_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_5_test_0.txt",5, 5, 5);
    test_leave_longest();
    printf("Exercise 5 - OK\n");
    // 6
    printf("Exercise 6\n");
    generate_polynomial("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_6_test_0.txt");
    print_polynomial("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_6_test_0.txt");
    test_remove_true_polynomial();
    printf("Exercise 6 - OK\n");
    // 7
    printf("Exercise 7\n");
    generate_numbers_array("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_7_test_0.txt");
    print_numbers_array("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_7_test_0.txt");
    test_rearrange_numbers();
    printf("Exercise 7 - OK\n");
    // 8
    printf("Exercise 8\n");
    generate_non_symmetric_matrix("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_8_test_0.txt");
    print_bin_file_matrix("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_8_test_0.txt");
    test_transpose_non_symmetric_matrix();
    printf("Exercise 8 - OK\n");
    // 9

}

