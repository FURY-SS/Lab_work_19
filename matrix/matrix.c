// Created by Vadim on 13.03.2024.

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "matrix.h"
#include "../matrix//algorithms/algorithms.h"

matrix get_mem_matrix(int n_rows, int n_cols) {
    int **values = (int **) malloc(sizeof(int *) * n_rows);

    for (int i = 0; i < n_rows; i++)
        values[i] = (int *) malloc(sizeof(int) * n_cols);

    return (matrix) {values, n_rows, n_cols};
}

matrix *get_mem_array_of_matrices(int n_matrices, int n_rows, int n_cols) {
    matrix *ms = (matrix *) malloc(sizeof(matrix) * n_matrices);

    for (int i = 0; i < n_matrices; i++)
        ms[i] = get_mem_matrix(n_rows, n_cols);

    return ms;
}

void free_mem_matrix(matrix *m) {
    for (int i = 0; i < m->n_rows; i++)
        free(m->values[i]);

    free(m->values);
    m->values = NULL;
    m->n_rows = 0;
    m->n_cols = 0;
}

void free_mem_matrices(matrix *ms, int n_matrices) {
    for (int i = 0; i < n_matrices; i++) {
        free_mem_matrix(ms + i);
    }

    free(ms->values);
    ms->values = NULL;
    ms->n_rows = 0;
    ms->n_cols = 0;
}

void input_matrix(matrix *m) {
    for (int i = 0; i < m->n_rows; i++) {
        printf("input %d row:", i + 1);
        for (int j = 0; j < m->n_cols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void input_matrices(matrix *ms, int n_matrices) {
    for (int i = 0; i < n_matrices; i++) {
        printf("input %lld matrix\n", i + 1);
        input_matrix(ms + i);
        printf("\n");
    }
}

void output_matrix(matrix *m) {
    for (int i = 0; i < m->n_rows; i++) {
        for (int j = 0; j < m->n_cols; j++) {
            printf("%d ", m->values[i][j]);
        }

        printf("\n");
    }
    printf("\n");
}

void output_matrices(matrix *ms, int n_matrices) {
    for (int i = 0; i < n_matrices; i++) {
        output_matrix(ms + i);
    }
}

void swap_rows(matrix *m, int i1, int i2) {
    int* temp = m->values[i1];
    m->values[i1] = m->values[i2];
    m->values[i2] = temp;
}

void swap_columns(matrix *m, int j1, int j2) {
    for (int i = 0; i < m->n_rows; i++) {
        swap(&m->values[i][j1], &m->values[i][j2]);

    }
}

void insertion_sort_rows_matrix_by_row_criteria(matrix *m, int (*criteria)(int*, int)) {
    int res_criteria[m->n_rows];

    for(int i = 0; i < m->n_rows; i++)
        res_criteria[i] = criteria(m->values[i], m->n_cols);

    for (int i = 1; i < m->n_rows; i++) {
        int key = res_criteria[i];
        int *address_key = m->values[i];
        int j = i - 1;

        while (j >= 0 && res_criteria[j] > key) {
            res_criteria[j + 1] = res_criteria[j];
            swap_rows(m, j + 1, j);

            j -= 1;
        }

        res_criteria[j + 1] = key;
        m->values[j + 1] = address_key;
    }
}

void selection_sort_cols_matrix_by_col_criteria(matrix *m, int (*criteria)(int*, int)) {
    int res_criteria[m->n_cols];

    for (size_t i = 0; i < m->n_cols; i++) {
        int temp[m->n_rows];
        for (size_t j = 0; j < m->n_rows; j++) {
            temp[j] = m->values[j][i];
        }

        res_criteria[i] = criteria(temp, m->n_rows);
    }

    int value_min_idx;
    for (int i = 0; i < m->n_cols; i++) {
        value_min_idx = i;

        for (int j = i + 1; j < m->n_cols; j++) {
            if (res_criteria[j] < res_criteria[value_min_idx]) {
                value_min_idx = j;
            }
        }

        swap(&res_criteria[value_min_idx], &res_criteria[i]);
        swap_columns(m, value_min_idx, i);
    }
}

bool is_square_matrix(matrix *m) {
    return m->n_rows == m->n_cols;
}

bool are_two_matrices_equal(matrix *m1, matrix *m2) {
    if (m1->n_rows != m2->n_rows || m1->n_cols != m2->n_cols) {
        return false;
    }

    for (int i = 0; i < m1->n_rows; i++) {
        for (int j = 0; j < m1->n_cols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool is_e_matrix(matrix *m) {
    if (m->n_rows != m->n_cols) {
        fprintf(stderr, "Is not square matrix");
        exit(1);
    }

    for (int i = 0; i < m->n_rows; i++) {
        for (int j = 0; j < m->n_cols; j++) {
            if (i == j && m->values[i][j] != 1) {
                return false;
            } else if (i != j && m->values[i][j] != 0) {
                return false;
            }
        }
    }

    return true;
}

bool is_symmetric_matrix(matrix *m) {
    for (int i = 0; i < m->n_rows; i++) {
        for (int j = i + 1; j < m->n_cols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }

    return true;
}

void transpose_square_matrix(matrix *m) {
    if (m->n_rows != m->n_cols) {
        fprintf(stderr, "Is not square matrix");
        exit(1);
    }

    for (int i = 0; i < m->n_rows; i++) {
        for (int j = i + 1; j < m->n_cols; j++) {
            if (i != j) {
                swap(&m->values[i][j], &m->values[j][i]);
            }
        }
    }
}

void transpose_matrix(matrix *m) {
    int** new_value = (int**) malloc(sizeof(int*) * m->n_cols);

    for (int i = 0; i < m->n_cols; i++) {
        new_value[i] = (int*) malloc(sizeof(int) * m->n_rows);

        for (int j = 0; j < m->n_rows; j++) {
            new_value[i][j] = m->values[j][i];
        }
    }

    for (int i = 0; i < m->n_rows; i++)
        free(m->values[i]);
    free(m->values);

    m->values = new_value;
    swap(&m->n_rows, &m->n_cols);
}

position get_min_value_pos(matrix m) {
    int min_value = m.values[0][0];
    position pos = {0, 0};

    for (int i = 1; i < m.n_rows; i++) {
        for (int j = 1; j < m.n_cols; j++) {
            if (m.values[i][j] < min_value) {
                min_value = m.values[i][j];
                pos.row_index = i;
                pos.col_index = j;
            }
        }
    }

    return pos;
}

position get_max_value_pos(matrix m) {
    int max_value = m.values[0][0];
    position pos = {0, 0};

    for (int i = 0; i < m.n_rows; i++) {
        for (int j = 0; j < m.n_cols; j++) {
            if (m.values[i][j] > max_value) {
                max_value = m.values[i][j];
                pos.row_index = i;
                pos.col_index = j;
            }
        }
    }

    return pos;
}

matrix create_matrix_from_array(const int *a, int n_rows, int n_cols) {
    matrix m = get_mem_matrix(n_rows, n_cols);

    int k = 0;
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            m.values[i][j] = a[k++];
        }
    }

    return m;
}

matrix* create_array_of_matrix_from_array(const int *values, size_t n_matrices, size_t n_rows, size_t n_cols) {
    matrix* ms = get_mem_array_of_matrices(n_matrices, n_rows, n_cols);

    int l = 0;
    for (size_t k = 0; k < n_matrices; k++) {
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                ms[k].values[i][j] = values[l++];
            }
        }
    }

    return ms;
}

void swap_min_max_rows(matrix* m) {
    position max = get_max_value_pos(*m);
    position min = get_min_value_pos(*m);

    swap_rows(m, max.row_index, min.row_index);
}

void sort_rows_by_max_element(matrix *m) {
    insertion_sort_rows_matrix_by_row_criteria(m, get_max);
}

void sort_cols_by_min_element(matrix *m) {
    selection_sort_cols_matrix_by_col_criteria(m, get_min);
}

matrix mul_matrices(matrix m1, matrix m2) {
    if (m1.n_cols != m2.n_rows) {
        fprintf(stderr, "It is not a square matrix");
        exit(1);
    }

    matrix res = get_mem_matrix(m1.n_rows, m2.n_rows);
    for (int i = 0; i < m1.n_rows; i++)
        for (int j = 0; j < m2.n_cols; j++) {
            res.values[i][j] = 0;
            for (int k = 0; k < m1.n_cols; k++)
                res.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }

    return res;
}

void get_square_of_matrix_if_symmetric(matrix *m) {
    if (!is_symmetric_matrix(m)) {
        return;
    }

    matrix res = mul_matrices(*m, *m);

    free_mem_matrix(m);

    m->values = res.values;
    m->n_rows = res.n_rows;
    m->n_cols = res.n_cols;
}

bool is_unique(long long *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j]) {
                return false;
            }
        }
    }

    return true;
}

void transpose_if_matrix_has_not_equal_sum_of_rows(matrix *m) {
    long long sum[m->n_rows];

    for (int i = 0; i < m->n_rows; i++) {
        sum[i] = get_sum(m->values[i], m->n_cols);
    }

    if (is_unique(sum, m->n_rows))
        transpose_square_matrix(m);
}

bool is_mutually_inverse_matrices(matrix m1, matrix m2) {
    matrix res = mul_matrices(m1, m2);

    bool is_e_m = is_e_matrix(&res);

    free_mem_matrix(&res);

    return is_e_m;
}

long long find_sum_of_maxes_of_pseudo_diagonal(matrix m) {
    int r = m.n_rows;
    int c = m.n_cols;
    int* max_value =(int*)malloc(sizeof(int) * (r + c - 1));

    for (int i = 0; i < r + c - 1; i++) {
        max_value[i] = 0;
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i != j) {
                max_value[i - j + c - 1] = max(max_value[i - j + c - 1],m.values[i][j]);
            }
        }
    }

    long long sum = 0;
    for (int i = 0; i < r + c - 1; i++) {
        sum += max_value[i];
    }

    free(max_value);

    return sum;
}

bool value_in_area(position max, int i, int j) {
    position new_position = {i - max.row_index, j - max.col_index};

    return (new_position.row_index <= new_position.col_index) && (new_position.row_index <= -new_position.col_index);
}

int get_min_in_area(matrix m) {
    position max = get_max_value_pos(m);
    int min = INT_MAX;

    for (int i = 0; i <= max.row_index; i++) {
        for (int j = 0; j < m.n_cols; j++) {
            if (value_in_area(max,i,j) && m.values[i][j] < min) {
                min = m.values[i][j];
            }
        }
    }

    return min;
}

void insertion_sort_rows_matrix_by_row_criteria_f(matrix* m, float (*criteria)(int*, int)) {
    float res_criteria[m->n_rows];

    for (size_t i = 0; i < m->n_rows; i++)
        res_criteria[i] = criteria(m->values[i], m->n_cols);

    int i, j;
    float key;
    int* address_key;
    for (i = 1; i < m->n_rows; i++) {
        key = res_criteria[i];
        address_key = m->values[i];
        j = i - 1;

        while (j >= 0 && res_criteria[j] > key) {
            res_criteria[j + 1] = res_criteria[j];
            swap_rows(m, j + 1, j);

            j -= 1;
        }

        res_criteria[j + 1] = key;
        m->values[j + 1] = address_key;
    }
}

void sort_by_distance(matrix *m) {
    insertion_sort_rows_matrix_by_row_criteria_f(m, get_distance);
}

int cmp_long_long(const void* pa, const void* pb) {
    return (int)(*(long long int*) pa - *(long long int*) pb);
}

int count_n_unique(long long int *a, int n) {
    int amount = 1;

    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1])
            amount++;
    }

    return amount;
}

int count_eq_classes_by_rows_sum(matrix m) {
    long long int values[m.n_rows];

    for (int i = 0; i < m.n_rows; i++)
        values[i] = get_sum(m.values[i], m.n_cols);

    qsort(values, m.n_rows, sizeof(long long int), cmp_long_long);

    int result = count_n_unique(values, m.n_rows);

    return result;
}

int get_n_special_element(matrix m) {
    int amount = 0;

    for (int i = 0; i < m.n_cols; i++) {
        int sum = m.values[0][i];
        int max_value = m.values[0][i];

        for (int j = 1; j < m.n_rows; j++) {
            sum += m.values[j][i];

            if (m.values[j][i] > max_value) {
                max_value = m.values[j][i];
            }
        }

        if (max_value > (sum - max_value)) {
            amount++;
        }
    }

    return amount;
}

position get_left_min(matrix m) {
    int min = INT_MAX;
    position min_pos;

    for (int j = 0; j < m.n_rows; j++) {
        for (int i = 0; i < m.n_cols; i++) {
            if (m.values[j][i] < min) {
                min = m.values[i][0];
                min_pos.row_index = j;
                min_pos.col_index = i;
            }
        }
    }

    return min_pos;
}

void swap_penultimate_row(matrix* m) {
    if (m->n_rows != m->n_cols) {
        return;
    }

    position min_pos = get_left_min(*m);

    int* temp = (int*) malloc(sizeof(int) * m->n_rows);
    for (int i = 0; i < m->n_rows; i++)
        temp[i] = m->values[i][min_pos.col_index];

    for (int i = 0; i < m->n_cols; i++)
        m->values[m->n_rows - 2][i] = temp[i];

    free(temp);
}

int count_values(const int *a, int n, int value) {
    int amount = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] == value)
            amount++;
    }

    return amount;
}

int count_zero_rows(matrix m) {
    int amount = 0;

    for (int i = 0; i < m.n_rows; i++) {
        int amount_zero = count_values(m.values[i],m.n_cols, 0);

    }
}

void print_matrix_with_max_zero_rows(matrix *ms, int n_matrix) {
    int amount_zero[n_matrix];
    int max_zero_rows = 0;

    for (int i = 0; i < n_matrix; i++) {
        int amount_zero_rows = count_zero_rows(ms[i]);
        amount_zero[i] = amount_zero_rows;

        if (amount_zero_rows > max_zero_rows) {
            max_zero_rows = amount_zero_rows;
        }
    }

    for (int i = 0; i < n_matrix; i++) {
        if (amount_zero[i] == max_zero_rows) {
            output_matrix(ms + i);
        }
    }
}

bool is_non_descending_sorted(const int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) {
            return false;
        }
    }

    return true;
}

bool has_all_non_descending_rows(matrix m) {
    for (int i = 0; i < m.n_rows; i++) {
        if (!is_non_descending_sorted(m.values[i], m.n_cols)) {
            return false;
        }
    }

    return true;
}

int count_non_descending_rows_matrices(matrix *ms, int n_matrix) {
    int amount = 0;

    for (int i = 0; i < n_matrix; i++)
        if (has_all_non_descending_rows(ms[i]))
            amount++;

    return amount;
}

int get_max_abs_value_in_matrix(matrix m) {
    int max_abs = get_max_abs_value(m.values[0], m.n_cols);

    for (int i = 1; i < m.n_rows; i++) {
        int abs_value = get_max_abs_value(m.values[i], m.n_cols);

        if (abs_value > max_abs)
            max_abs = abs_value;
    }

    return max_abs;
}

void print_matrix_with_min_standard(matrix *ms, int n_matrix) {
    int max_value[n_matrix];
    int min_value = get_max_abs_value_in_matrix(ms[0]);

    for (int i = 0; i < n_matrix; i++) {
        int value = get_max_abs_value_in_matrix(ms[i]);
        max_value[i] = value;

        if (value < min_value)
            min_value = value;
    }

    for (int i = 0; i < n_matrix; i++)
        if (max_value[i] == min_value)
            output_matrix(ms + i);
}

int get_n_special_element_2(matrix m) {
    int amount = 0;

    for (int i = 0; i < m.n_rows; i++)
        for (int j = 0; j < m.n_cols; j++)
            if (is_special_element(m.values[i], m.n_cols, j))
                amount++;

    return amount;
}

double get_scalar_product(int *a, int *b, int n) {
    double res = 0.0;

    for (int i = 0; i < n; i++) {
        res += (double) a[i] * (double) b[i];
    }

    return res;
}

int get_vector_index_with_max_angle(matrix m, int *b) {
    double max_cosine = get_cosine(m.values[0], b, m.n_cols);
    int index_max_angle = 0;

    for (int i = 1; i < m.n_rows; i++) {
        double cosine = get_cosine(m.values[i], b, m.n_cols);

        if (cosine < max_cosine) {
            max_cosine = cosine;
            index_max_angle = i;
        }
    }

    return index_max_angle;
}

long long get_scalar_product_row_and_col(matrix m, int i, int j) {
    long long res = 0;

    for (int k = 0; k < m.n_rows; k++) {
        res += m.values[i][k] * m.values[k][j];
    }

    return res;
}

long long get_special_scalar_product(matrix m) {
    position max = get_max_value_pos(m);
    position min = get_min_value_pos(m);

    long long res = get_scalar_product_row_and_col(m, max.row_index, min.col_index);

    return res;
}