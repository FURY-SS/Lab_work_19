#include "tasks/matrix_transposition.h"
#include "tasks/convert_float_num.h"
#include "tasks/evaluate_expression.h"
#include "tasks/special_word.h"
#include "tasks/leave_longest_word .h"
#include "tasks/remove_polynomial.h"

int main() {
    // 1
    generate_random_matrix_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_1_test_0.txt", 3);
    test_matrix_transpose();
    // 2
    generate_float_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_2_test_0.txt", 10);
    test_convert_float();
    // 3
    generate_expression("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_3_test_0.txt");
    test_evaluate();
    // 4
    generate_string("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_4_test_0.txt", "abcde abcde");
    test_filter_word();
    // 5
    generate_text_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_5_test_0.txt",5, 5, 5);
    test_leave_longest();
    // 6
    generate_polynomial("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_6_test_0.txt");
    test_remove_true_polynomial();

}
