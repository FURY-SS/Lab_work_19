#include "tasks/matrix_transposition.h"
#include "tasks/convert_float_num.h"

int main() {
    // 1
    generate_random_matrix_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_1_test_0.txt", 3);
    test_matrix_transpose();
    // 2
    generate_float_file("C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_2_test_0.txt", 10);
    test_convert_float();
    // 3

}