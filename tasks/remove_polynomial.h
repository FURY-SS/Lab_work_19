// Created by Vadim on 06.05.2024.

#ifndef LAB_WORK_19_REMOVE_POLYNOMIAL_H
#define LAB_WORK_19_REMOVE_POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../vector/vector_void.h"

typedef struct monomial {
    size_t degree;
    double coefficient;
} monomial;

void generate_polynomial(const char* filename) {
    srand(time(NULL));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int amount_polynomial = rand() % 5 + 2;

    for (int k = 0; k < amount_polynomial; k++) {
        int amount_monomial = rand() % 5 + 1;

        monomial mono;
        for (int i = 0; i <= amount_monomial; i++) {
            mono.degree = amount_monomial - i;
            mono.coefficient = 2.0 * rand() / RAND_MAX - 1.0;

            fwrite(&mono, sizeof(monomial), 1, file);
        }
    }

    fclose(file);
}

double get_monomial_value(monomial mono, double x) {
    return pow(x, mono.degree) * mono.coefficient;
}

void remove_true_polynomial(const char* filename, double x) {
    vector_void v = create_vector_void(16, sizeof(monomial));

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial mono;
    while (fread(&mono, sizeof(monomial), 1, file) == 1)
        push_back_v(&v, &mono);

    fclose(file);


    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial m;
    vector_void temp = create_vector_void(8, sizeof(monomial));
    double result = 0;
    for (size_t i = 0; i < v.size; i++) {
        get_vector_value_v(&v, i, &m);
        push_back_v(&temp, &m);
        result += get_monomial_value(m, x);

        if (m.degree == 0) {
            if (fabs(result) >= 0.001) {
                monomial temp_mono;
                for (size_t j = 0; j < temp.size; j++) {
                    get_vector_value_v(&temp, j, &temp_mono);
                    fwrite(&temp_mono, sizeof(monomial), 1, file);
                }
            }

            clear_v(&temp);
            result = 0;
        }
    }

    delete_vector_v(&v);
    delete_vector_v(&temp);

    fclose(file);
}

void print_polynomial(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    monomial mono;
    while (fread(&mono, sizeof(monomial), 1, file) == 1) {
        printf("%5.2lf * x^%lld + ", mono.coefficient, mono.degree);

        if (mono.degree == 0)
            printf("\b\b \n");
    }

    fclose(file);
}

void test_remove_true_polynomial_1_empty_file() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_6_test_1.txt";

    FILE* file = fopen(filename, "wb");
    fclose(file);

    remove_true_polynomial(filename, 1.0);

    file = fopen(filename, "rb");

    char data[10] = "";
    fscanf(file, "%s", data);

    fclose(file);

    assert(strcmp_(data, "") == 0);
}

void test_remove_true_polynomial_2_not_true_expression() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_6_test_2.txt";

    double x = 2.0;
    monomial x_2 = {.coefficient = 1.0, .degree = 2};
    monomial x_1 = {.coefficient = -2.0, .degree = 1};
    monomial c = {.coefficient = 1.0, .degree = 0};

    FILE* file = fopen(filename, "wb");

    fwrite(&x_2, sizeof(monomial), 1, file);
    fwrite(&x_1, sizeof(monomial), 1, file);
    fwrite(&c, sizeof(monomial), 1, file);

    fclose(file);

    remove_true_polynomial(filename, x);


    file = fopen(filename, "rb");

    monomial res_x_2;
    fread(&res_x_2, sizeof(monomial), 1, file);

    monomial res_x_1;
    fread(&res_x_1, sizeof(monomial), 1, file);

    monomial res_c;
    fread(&res_c, sizeof(monomial), 1, file);

    fclose(file);

    assert(x_2.coefficient - res_x_2.coefficient <= 0.0001 && x_2.degree == res_x_2.degree);
    assert(x_1.coefficient - res_x_1.coefficient <= 0.0001 && x_1.degree == res_x_1.degree);
    assert(c.coefficient - res_c.coefficient <= 0.0001 && c.degree == res_c.degree);
}

void test_remove_true_polynomial_3_true_expression() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_6_test_3.txt";

    double x = 1.0;
    monomial x_2 = {.coefficient = 1.0, .degree = 2};
    monomial x_1 = {.coefficient = -2.0, .degree = 1};
    monomial c = {.coefficient = 1.0, .degree = 0};

    FILE* file = fopen(filename, "wb");

    fwrite(&x_2, sizeof(monomial), 1, file);
    fwrite(&x_1, sizeof(monomial), 1, file);
    fwrite(&c, sizeof(monomial), 1, file);

    fclose(file);

    remove_true_polynomial(filename, x);

    file = fopen(filename, "rb");

    char data[10] = "";
    fscanf(file, "%s", data);

    fclose(file);

    assert(strcmp_(data, "") == 0);
}

void test_remove_true_polynomial() {
    test_remove_true_polynomial_1_empty_file();
    test_remove_true_polynomial_2_not_true_expression();
    test_remove_true_polynomial_3_true_expression();
}

#endif //LAB_WORK_19_REMOVE_POLYNOMIAL_H