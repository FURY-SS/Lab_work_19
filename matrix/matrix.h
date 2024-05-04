// Created by vadim on 13.03.2024.

#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

#include <stdbool.h>

typedef struct matrix {
    int **values; // элементы матрицы
    int n_rows; // количество рядов
    int n_cols; // количество столбцов
} matrix;

typedef struct position {
    int row_index;
    int col_index;
} position;

// размещает в динамической памяти матрицу размером n_rows на n_cols. Возвращает матрицу.
matrix get_mem_matrix(int n_rows, int n_cols);

// размещает в динамической памяти массив из n_matrices матриц размером n_rows на n_cols.
// Возвращает указатель на нулевую матрицу.
matrix *get_mem_array_of_matrices(int n_matrices, int n_rows, int n_cols);

// освобождает память, выделенную под хранение матрицы m.
void free_mem_matrix(matrix *m);

// освобождает память, выделенную под хранение массива ms из n_matrices матриц.
void free_mem_matrices(matrix *ms, int n_matrices);

// ввод матрицы m.
void input_matrix(matrix *m);

// ввод массива из n_matrices матриц, хранящейся по адресу ms.
void input_matrices(matrix *ms, int n_matrices);

// вывод матрицы m.
void output_matrix(matrix *m);

// вывод массива из n_matrices матриц, хранящейся по адресу ms.
void output_matrices(matrix *ms, int n_matrices);

// обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swap_rows(matrix *m, int i1, int i2);

//  обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swap_columns(matrix *m, int j1, int j2);

// выполняет сортировку вставками строк матрицы m по неубыванию значения функции criteria применяемой для строк.
void insertion_sort_rows_matrix_by_row_criteria(matrix *m, int (*criteria)(int*, int));

// выполняет сортировку выбором столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов.
void selection_sort_cols_matrix_by_col_criteria(matrix *m, int (*criteria)(int*, int));

// возвращает значение ’истина’, если матрица m является квадратной, ложь – в противном случае.
bool is_square_matrix(matrix *m);

// возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае.
bool are_two_matrices_equal(matrix *m1, matrix *m2);

// возвращает значение ’истина’, если матрица m является единичной, ложь – в противном случае.
bool is_e_matrix(matrix *m);

// возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае.
bool is_symmetric_matrix(matrix *m);

// транспонирует квадратную матрицу m.
void transpose_square_matrix(matrix *m);

// транспонирует матрицу m.
void transpose_matrix(matrix *m);

// возвращает позицию минимального элемента матрицы m.
position get_min_value_pos(matrix m);

// возвращает позицию максимального элемента матрицы m.
position get_max_value_pos(matrix m);

// возвращает матрицу размера n_rows на n_cols, построенную из элементов массива a.
matrix create_matrix_from_array(const int *a, int n_rows, int n_cols);

// возвращает указатель на нулевую матрицу массива из n_matrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a.
matrix* create_array_of_matrix_from_array(const int *values, size_t n_matrices, size_t n_rows, size_t n_cols);

//***********************************************************

// меняет местами строки матрицы m, в которых находятся максимальный и минимальный элемент
void swap_min_max_rows(matrix *m);

// сортирует строки матрицы m по не убыванию наибольших элементов строк
void sort_rows_by_max_element(matrix *m);

// сортирует столбцы матрицы m по не убыванию наименьших элементов столбцов
void sort_cols_by_min_element(matrix *m);

// возвращает матрицу, равную перемножению матрицы m1 на матрицу m2
matrix mul_matrices(matrix m1, matrix m2);

// заменяет исходную матрицу m, если она является симметричной, на её квадрат
void get_square_of_matrix_if_symmetric(matrix *m);

// возвращает истину, если массив a размера n состоит только из уникальных элементов
bool is_unique(long long *a, int n);

// транспонирует матрицу, если суммы строк различны
void transpose_if_matrix_has_not_equal_sum_of_rows(matrix *m);

// возвращает истина, если матрицы m1 и m2 являются взаимно обратными
bool is_mutually_inverse_matrices(matrix m1, matrix m2);

// возвращает сумму максимальных положительный элементов псевдодиагоналей матрицы m
long long find_sum_of_maxes_of_pseudo_diagonal(matrix m);

// возвращает истина, если элемент по индексу i,j находится в области элемента max.
bool value_in_area(position max, int i, int j);

// возвращает минимальный положительный элемент матрицы m, который находится в зоне.
int get_min_in_area(matrix m);

// сортирует строки матрицы m по не убыванию, по критерию.
void insertion_sort_rows_matrix_by_row_criteria_f(matrix* m, float (*criteria)(int*, int));

// сортирует строки матрицы m, относительно их удалённости от начала координат
void sort_by_distance(matrix* m);

// возвращает количество уникальных элементов массива a размера n
int count_n_unique(long long int *a, int n);

// возвращает количество уникальных сумм строк матрицы m
int count_eq_classes_by_rows_sum(matrix m);

// возвращает количество "особых" элементов матрицы m, элемент считается особенным, если он больше суммы остальных элементов своего столбца
int get_n_special_element(matrix m);

// возвращает position минимального элемента левого столбца.
position get_left_min(matrix m);

// меняет местами предпоследнюю строку матрицы m, на n столбец.
void swap_penultimate_row(matrix* m);

// возвращает количество элементов value в массиве a размера n.
int count_values(const int *a, int n, int value);

// возвращает количество нулевых строк в матрицы m.
int count_zero_rows(matrix m);

// выводит матрицы, из массива матриц ms размера n_matrix, с максимальным числом нулевых строк.
void print_matrix_with_max_zero_rows(matrix ms[], int n_matrix);

// возвращает истина, если массив a размера n отсортирован по неубыванию, иначе ложь.
bool is_non_descending_sorted(const int *a, int n);

// возвращает истина, если все строки матрицы m отсортированы по неубыванию, иначе ложь.
bool has_all_non_descending_rows(matrix m);

// возвращает количество матриц, из массива матриц ms размера n_matrix, строки в которых упорядочены по не убыванию.
int count_non_descending_rows_matrices(matrix *ms, int n_matrix);

// возвращает максимальное абсолютное значение в матрице m
int get_max_abs_value_in_matrix(matrix m);

// выводит матрицы, из массива матриц ms размера n_matrix,с минимальной нормой.
// норма - максимум из абсолютных величин матрицы.
void print_matrix_with_min_standard(matrix *ms, int n_matrix);

// возвращает количество "особых" элементов матрицы m
// элемент считается особенным, если в строке слева от него находятся только меньшие элементы, а справа большие.
int get_n_special_element_2(matrix m);

// возвращает скалярное произведение массива a размера n на массив b размера n.
double get_scalar_product(int *a, int *b, int n);

// возвращает индекс строки матрицы m, которая образует максимальный угол с данным вектором b.
int get_vector_index_with_max_angle(matrix m, int *b);

// возвращает скалярное произведение i-ой строки матрицы m, на j-ый столбец матрицы m.
long long get_scalar_product_row_and_col(matrix m, int i, int j);

// возвращает скалярное произведение строки матрицы m, в которой находится наибольший элемент матрицы, на столбец матрицы m с минимальным элементом.
long long get_special_scalar_product(matrix m);

#endif //UNTITLED_MATRIX_H