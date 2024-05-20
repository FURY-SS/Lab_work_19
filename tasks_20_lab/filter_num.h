// Created by Vadim on 20.05.2024.

#ifndef LAB_WORK_19_FILTER_NUM_H
#define LAB_WORK_19_FILTER_NUM_H

#include <stdio.h>

#include "../vector/vector.h"

void filter_nums(const char* filename, const int n) {
    FILE* file = fopen(filename, "r");

    int x;
    vector v = create_vector(16);
    while (fscanf(file, "%d ", &x) == 1)
        if (x < n)
            push_back(&v, x);

    fclose(file);


    file = fopen(filename, "w");

    for (int i = 0; i < v.size; i++) {
        x = get_vector_value_(v, i);
        fprintf(file, "%d ", x);
    }

    fprintf(file, "\n");

    fclose(file);
}

#endif //LAB_WORK_19_FILTER_NUM_H