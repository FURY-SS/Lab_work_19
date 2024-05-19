// Created by Vadim on 19.05.2024.

#ifndef LAB_WORK_19_BIN_TREE_H
#define LAB_WORK_19_BIN_TREE_H

#include <stdio.h>
#include "../vector/vector.h"

void print_vector(vector* v) {
    for (int i = 0; i < v->size; i++)
        printf("%d ", get_vector_value_(*v, i));
    printf("\n");
}

int get_max_vector(vector* v) {
    if (v->size == 0)
        return (int) -1e4;

    int max = get_vector_value_(*v, 0);
    for (int i = 1; i < v->size; i++) {
        int x = get_vector_value_(*v, i);
        if (max < x)
            max = x;
    }

    return max;
}

int get_index_vector(vector* v, int x) {
    int i = -1;
    for (int j = 0; j < v->size; j++)
        if (get_vector_value_(*v, j) == x)
            i = j;
    return i;
}

void _generate_tree(vector* nums, vector* result) {
    if (nums->size == 0) {
        push_back(result, -1);
        return;
    } else if (nums->size == 1) {
        int x = get_vector_value_(*nums, 0);
        push_back(result, x);
        return;
    }

    int mx = get_max_vector(nums);
    int ind = get_index_vector(nums, mx);
    push_back(result, mx);

    vector left = create_vector(ind + 1);
    for (int i = 0; i < ind; i++)
        push_back(&left, get_vector_value_(*nums, i));

    vector right = create_vector(nums->size - ind + 1);
    for (int i = ind + 1; i < nums->size; i++)
        push_back(&right, get_vector_value_(*nums, i));

    _generate_tree(&left, result);
    _generate_tree(&right, result);

    delete_vector(&left);
    delete_vector(&right);
}

vector generate_tree(vector* v) {
    vector result = create_vector(32);
    _generate_tree(v, &result);

    return result;
}

void test_generate_tree() {
    vector v = create_vector(12);
    push_back(&v, 3);
    push_back(&v, 2);
    push_back(&v, 1);
    push_back(&v, 6);
    push_back(&v, 0);
    push_back(&v, 5);

    v = generate_tree(&v);

    assert(get_vector_value_(v, 0) == 6);
    assert(get_vector_value_(v, 1) == 3);
    assert(get_vector_value_(v, 2) == -1);
    assert(get_vector_value_(v, 3) == 2);
    assert(get_vector_value_(v, 4) == -1);
    assert(get_vector_value_(v, 5) == 1);
    assert(get_vector_value_(v, 6) == 5);
    assert(get_vector_value_(v, 7) == 0);
    assert(get_vector_value_(v, 8) == -1);

    delete_vector(&v);
}

#endif //LAB_WORK_19_BIN_TREE_H