// Created by Vadim on 07.02.2024.

#ifndef UNTITLED_ALGORITHMS_H
#define UNTITLED_ALGORITHMS_H

// меняет местами указатели.
void swap(int *a, int *b);

// возвращает максимальный элемент массива a размера n.
int get_max(int *a, int n);


// возвращает минимальный элемент массива a размера n.
int get_min(int *a, int n);

// возвращает сумму элементов массива a размера n.
long long get_sum(int *a, int n);

// возвращает макс элемент из двух эл.
int max(int a, int b);

// возвращает мин элемент из двух эл.
int min(int a, int b);

// возвращает расстояние вектора a размера n, до начала координат
float get_distance(int *a, int n);

// возвращает максимальное абсолютное значение в массиве a размера n
int get_max_abs_value(const int *a, int n);

// возвращает истина, если элемент по индексу index в массиве a размера n является особенным
// элемент особенный, если в строке слева от него находятся только меньшие элементы, иначе ложь.
bool is_special_element(int *a, int n, int index);

// возвращает длину вектора a размера n.
double get_vector_length(int *a, int n);

// возвращает косинус между вектором a размера n и вектором b размера n.
double get_cosine(int *a, int *b, int n);

#endif //UNTITLED_ALGORITHMS_H