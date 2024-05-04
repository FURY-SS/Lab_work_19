// Created by Vadim on 07.02.2024.

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "../matrix/matrix.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int get_max(int *a, int n) {
    int max = a[0];

    for (size_t i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    return max;
}

int get_min(int *a, int n) {
    int min = a[0];

    for (size_t i = 1; i < n; i++)
        if (a[i] < min)
            min = a[i];

    return min;
}

long long get_sum(int *a, int n) {
    long long res = 0;

    for (int i = 0; i < n; i++) {
        res += a[i];
    }

    return res;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

float get_distance(int *a, int n) {
    long long square_sum = 0;

    for (int i = 0; i < n; i++) {
        square_sum += a[i] * a[i];
    }

    return sqrt(square_sum);
}

int get_max_abs_value(const int *a, int n) {
    int max_abs = abs(a[0]);

    for (int i = 1; i < n; i++)
        if (abs(a[i]) > max_abs)
            max_abs = abs(a[i]);

    return max_abs;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

bool is_special_element(int *a, int n, int index) {
    for (int i = 0; i < index; i++)
        if (a[index] != max(a[i], a[index]))
            return false;

    for (int i = index + 1; i < n; i++)
        if (a[index] != min(a[i], a[index]))
            return false;

    return true;
}

double get_vector_length(int *a, int n) {
    double sum = get_scalar_product(a, a, n);

    double length = sqrt(sum);

    return length;
}

double get_cosine(int *a, int *b, int n) {
    double scalar_product = get_scalar_product(a, b, n);

    double mul_length = get_vector_length(a, n) * get_vector_length(b, n);

    double cosine = scalar_product / mul_length;

    return cosine;
}