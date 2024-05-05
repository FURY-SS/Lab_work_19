// Created by vadim on 25.02.2024.

#ifndef UNTITLED_VECTOR_H
#define UNTITLED_VECTOR_H

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;

// возвращает структуру-дескриптор вектор из n значений.
vector create_vector(size_t capacity);

// изменяет количество памяти, выделенное под хранение элементов вектора.
void reserve(vector *v, size_t new_capacity);

// удаляет элементы из контейнера, но не освобождает выделенную память.
void clear(vector *v);

// освобождает память, выделенную поднеиспользуемые элементы.
void vector_shrink_to_fit(vector *v);

// освобождает память, выделенную вектору.
void delete_vector(vector *v);

// проверки на то, является ли вектор пустым.
bool is_empty(vector *v);

// проверки на то, является ли вектор полным.
bool is_full(vector *v);

// возвращает i-ый элемент вектора v.
int get_vector_value(vector *v, size_t i);

// добавляет элемент x в конец вектора.
void push_back(vector *v, int x);

// удаляет последний элемент из вектора.
void pop_back(vector *v);

// возвращает указатель на index-ый элемент вектора.
int* at_vector(vector *v, size_t index);

// возвращает указатель на последний элемент вектора.
int* back(vector *v);

// возвращает указатель на нулевой элемент вектора.
int* front(vector *v);

#endif //UNTITLED_VECTOR_H