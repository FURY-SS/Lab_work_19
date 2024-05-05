// Created by vadim on 26.02.2024.

#ifndef UNTITLED_VECTOR_VOID_H
#define UNTITLED_VECTOR_VOID_H

#include <limits.h>
#include <stdbool.h>

typedef struct vector_void {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t base_type_size; // размер базового типа:
} vector_void;

// возвращает структуру-дескриптор вектор из n значений.
vector_void create_vector_void(size_t capacity, size_t base_type_size);

// изменяет количество памяти, выделенное под хранение элементов вектора.
void reserve_v(vector_void *v, size_t new_capacity);

// удаляет элементы из контейнера, но не освобождает выделенную память.
void clear_v(vector_void *v);

// освобождает память, выделенную поднеиспользуемые элементы.
void vector_shrink_to_fit_v(vector_void *v);

// освобождает память, выделенную вектору.
void delete_vector_v(vector_void *v);

// проверки на то, является ли вектор пустым.
bool is_empty_v(vector_void *v);

// проверки на то, является ли вектор полным.
bool is_full_v(vector_void *v);

// записывает по адресу destination index-ый элемент вектора v.
void get_vector_value_v(vector_void *v, size_t index, void *destination);

// записывает на index-ый элемент вектора v значение, расположенное по адресу source;
void set_vector_value_v(vector_void *v, size_t index, void *source);

// удаляет последний элемент из вектора.
void pop_back_v(vector_void *v);

// добавляет элемент x в конец вектора.
void push_back_v(vector_void *v, void *source);

#endif //UNTITLED_VECTOR_VOID_H