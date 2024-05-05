// Created by Vadim on 05.05.2024.

#ifndef LAB_WORK_19_CONVERT_FLOAT_NUM_H
#define LAB_WORK_19_CONVERT_FLOAT_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../string/string.h"
#include "../vector/vector_void.h"


void generate_float_file(const char* filename, int num_numbers) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < num_numbers; i++) {
        float number = ((float)rand() / (float)(RAND_MAX)) * 100.0;
        fprintf(file, "%.2f\n", number);
    }

    fclose(file);
}

void convert_float(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    vector_void v = create_vector_void(0, sizeof(float));

    while (!feof(file)) {
        float x;
        fscanf(file, "%f", &x);

        push_back_v(&v, &x);
    }

    fclose(file);

    file = fopen(filename, "w");

    for (size_t i = 0; i < v.size; i++) {
        float x;
        get_vector_value_v(&v, i, &x);
        fprintf(file, "%.2f ", x);
    }

    delete_vector_v(&v);
    fclose(file);
}

void test_convert_float_1_zero_quantity() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_2_test_1.txt";

    FILE* file = fopen(filename, "w");
    fclose(file);

    convert_float(filename);

    file = fopen(filename, "r");

    char data[10] = "";
    fscanf(file, "%s", data);

    fclose(file);

    assert(strcmp_(data, "0.00") == 0);
}

void test_convert_float_2_one_element() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_2_test_2.txt";

    float f1 = 1.123123;

    FILE* file = fopen(filename, "w");

    fprintf(file, "%f", f1);

    fclose(file);

    convert_float(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char check[100] = "1.12 ";

    assert(strcmp_(data, check) == 0);
}

void test_convert_float_3_more_element() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_2_test_3.txt";

    float f1 = 1.123123;
    float f2 = 2.232323;
    float f3 = 3.343434;
    FILE* file = fopen(filename, "w");

    fprintf(file, "%f %f %f", f1, f2,f3);

    fclose(file);

    convert_float(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char check[100] = "1.12 2.23 3.34 ";

    assert(strcmp_(data, check) == 0);
}

void test_convert_float() {
    test_convert_float_1_zero_quantity();
    test_convert_float_2_one_element();
    test_convert_float_3_more_element();
}

#endif //LAB_WORK_19_CONVERT_FLOAT_NUM_H