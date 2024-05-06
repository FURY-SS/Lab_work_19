// Created by Vadim on 06.05.2024.

#ifndef LAB_WORK_19_REARRANGE_NUMBERS_H
#define LAB_WORK_19_REARRANGE_NUMBERS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../vector/vector.h"

void generate_numbers_array(const char* filename) {
    srand(time(NULL));

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int amount_numbers = (int) rand() % 10 + 1;

    for (int i = 0; i < amount_numbers; i++) {
        int x = rand() % 200 - 100;
        fwrite(&x, sizeof(int), 1, file);
    }

    fclose(file);
}

void print_numbers_array(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int x;
    while(fread(&x, sizeof(int), 1, file))
        printf("%d ", x);
    printf("\n");

    fclose(file);
}

void rearrange_numbers(const char* filename) {
    vector positive_numbers = create_vector(2);
    vector negative_numbers = create_vector(2);

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int current_number;
    while (fread(&current_number, sizeof(int), 1, file) == 1) {
        if (current_number >= 0)
            push_back(&positive_numbers, current_number);
        else
            push_back(&negative_numbers, current_number);
    }

    fclose(file);


    file = fopen(filename, "wb");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (int i = 0; i < positive_numbers.size; i++)
        fwrite(positive_numbers.data + i, sizeof(int), 1, file);

    for (int i = 0; i < negative_numbers.size; i++)
        fwrite(negative_numbers.data + i, sizeof(int), 1, file);

    delete_vector(&positive_numbers);
    delete_vector(&negative_numbers);
    fclose(file);
}

void test_rearrange_numbers_1_empty_file() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_7_test_1.txt";
    FILE* file = fopen(filename, "wb");
    fclose(file);

    rearrange_numbers(filename);

    file = fopen(filename, "rb");

    char data[10] = "";
    fread(data, sizeof(data), 1, file);

    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_rearrange_numbers_2_only_negative_numbers() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_7_test_2.txt";;

    int x1 = -1;
    int x2 = -2;
    int x3 = -3;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);

    fclose(file);

    rearrange_numbers(filename);

    file = fopen(filename, "rb");

    int res_x1, res_x2, res_x3;
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);
    fread(&res_x3, sizeof(int), 1, file);

    fclose(file);

    assert(x1 == res_x1);
    assert(x2 == res_x2);
    assert(x3 == res_x3);
}


void test_rearrange_numbers_3_only_positive_numbers() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_7_test_3.txt";;

    int x1 = 1;
    int x2 = 2;
    int x3 = 3;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);

    fclose(file);

    rearrange_numbers(filename);

    file = fopen(filename, "rb");

    int res_x1, res_x2, res_x3;
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);
    fread(&res_x3, sizeof(int), 1, file);

    fclose(file);

    assert(x1 == res_x1);
    assert(x2 == res_x2);
    assert(x3 == res_x3);
}

void test_rearrange_numbers_4_mixed_numbers() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_7_test_4.txt";;

    int x1 = -1;
    int x2 = 2;
    int x3 = -3;
    int x4 = 3;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);
    fwrite(&x4, sizeof(int), 1, file);

    fclose(file);

    rearrange_numbers(filename);

    file = fopen(filename, "rb");

    int res_x1, res_x2, res_x3, res_x4;
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);
    fread(&res_x3, sizeof(int), 1, file);
    fread(&res_x4, sizeof(int), 1, file);

    fclose(file);

    assert(res_x1 == x2);
    assert(res_x2 == x4);
    assert(res_x3 == x1);
    assert(res_x4 == x3);
}

void test_rearrange_numbers() {
    test_rearrange_numbers_1_empty_file();
    test_rearrange_numbers_2_only_negative_numbers();
    test_rearrange_numbers_3_only_positive_numbers();
    test_rearrange_numbers_4_mixed_numbers();
}

#endif //LAB_WORK_19_REARRANGE_NUMBERS_H