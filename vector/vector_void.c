
// Created by vadim on 26.02.2024.

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include "../vector/vector_void.h"

vector_void create_vector_void(size_t capacity, size_t base_type_size) {
    if (capacity <= UINT64_MAX) {
        return (vector_void) {malloc(base_type_size * capacity), 0, capacity, base_type_size};
    } else {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void delete_vector_v(vector_void *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void reserve_v(vector_void *v, size_t new_capacity) {
    if (new_capacity > 0) {

        int *new_data = realloc(v->data, new_capacity * new_capacity * v->base_type_size);
        if (new_data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }

        v->data = new_data;
        v->capacity = new_capacity;

        if (new_capacity < v->size) {
            v->size = new_capacity;
        }

    } else {
        delete_vector_v(v);
    }
}

void clear_v(vector_void *v) {
    v->size = 0;
}

void vector_shrink_to_fit_v(vector_void *v) {
    v->capacity = v->size;
}

bool is_empty_v(vector_void *v) {
    return v->size == 0;
}

bool is_full_v(vector_void *v) {
    return v->size == v->capacity;
}

void get_vector_value_v(vector_void *v, size_t index, void *destination) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    } else {
        char *source = (char *) v->data + index * v->base_type_size;
        memcpy(destination, source, v->base_type_size);
    }
}

void set_vector_value_v(vector_void *v, size_t index, void *source) {
    if (index >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        exit(1);
    } else {
        char *dst = (char *) v->data + index * v->base_type_size;
        memcpy(dst, source, v->base_type_size);
    }
}

void pop_back_v(vector_void *v) {
    if (is_empty_v(v)) {
        fprintf(stderr, "bad alloc");
        exit(1);
    } else {
        v->size--;
    }
}

void push_back_v(vector_void *v, void *source) {
    if (v->capacity == 0) {
        v->capacity++;
    } else if (is_full_v(v)) {
        reserve_v(v, v->capacity * 2);
    }

    char *dst = (char *) v->data + v->size * v->base_type_size;
    memcpy(dst, source, v->base_type_size);
    v->size++;
}
