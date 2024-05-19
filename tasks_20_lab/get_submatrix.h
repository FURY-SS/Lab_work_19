// Created by Vadim on 19.05.2024.

#ifndef LAB_WORK_19_GET_SUBMATRIX_H
#define LAB_WORK_19_GET_SUBMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../matrix/matrix.h"

int get_submatrix(matrix mat) {
    int m = mat.n_rows;
    int n = mat.n_cols;
    int res = 0;

    for (int i = 1; i < m; i++)
        for (int j = 0; j < n; j++)
            if (mat.values[i][j])
                mat.values[i][j] += mat.values[i - 1][j];

    for (int i = 0; i < m; i++) {
        int stack[n];
        int top = -1;
        int sums[n + 1];
        sums[0] = 0;

        for (int j = 0; j < n; j++) {
            while (top != -1 && mat.values[i][stack[top]] >= mat.values[i][j])
                top--;
            if (top != -1) {
                int k = stack[top];
                sums[j + 1] = sums[k + 1] + mat.values[i][j] * (j - k);
            } else
                sums[j + 1] = mat.values[i][j] * (j + 1);
            stack[++top] = j;
        }

        for (int j = 0; j <= n; j++)
            res += sums[j];
    }
    return res;
}

void test_num_submatrices() {
    matrix m = create_matrix_from_array((int[]) {1, 0, 1,
                                                 1, 1, 0,
                                                 1, 1, 0}, 3, 3);

    int res = get_submatrix(m);

    free_mem_matrix(&m);

    assert(res == 13);
}

#endif //LAB_WORK_19_GET_SUBMATRIX_H