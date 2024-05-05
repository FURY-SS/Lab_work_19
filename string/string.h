
// Created by Vadim on 08.04.2024.

#ifndef LAB_WORK_17_STRING__H
#define LAB_WORK_17_STRING__H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ASSERT_STRING(expected, got) assert_string(expected, got, __FILE__, __FUNCTION__, __LINE__)

#define MAX_WORD_SIZE 20
#define MAX_N_WORDS_IN_STRING 100
#define MAX_STRING_SIZE 100

extern char _string_buffer[MAX_STRING_SIZE + 1];

typedef struct word_descriptor {
    char* begin;
    char* end;
} word_descriptor;

typedef struct bag_of_words {
    word_descriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} bag_of_words;

extern bag_of_words _bag;
extern bag_of_words _bag2;

// возвращает длину строки
int length_of_string(const char *str);

// возвращает количество символов в строке
size_t strlen_(char* begin);

// возвращает указатель на первый элемент, расположенным между адресами begin и end не включая end.
char* find(char *begin, char *end, int ch);

//  возвращает указатель на первый символ, если символ не найден, возвращается адрес первого ноль-символа.
char* find_non_space(char *begin);

// возвращает указатель на первый пробельный символ или на первый ноль-символ.
char* find_space(char *begin);

// возвращает указатель на первый справа символ, отличный от пробельных, еслисимвол не найден, возвращается адрес rend.
char* find_non_space_reverse(char *rbegin, const char *rend);

// возвращает указатель на первый пробельный символ справа, tсли символ не найден, возвращается адрес rend.
char* find_space_reverse(char *rbegin, const char *rend);

// Функция возвращает отрицательное значение, если lhs располагается до rhs
// значение 0, если lhs и rhs равны,
// иначе – положительное значение
int strcmp_(const char *lhs, const char *rhs);

// записывает по адресу beginDestination фрагмент памяти, начиная с адреса beginSource до endSource
// Возвращает указатель на следующий свободный фрагмент памяти в destination.
char* copy(const char *begin_source, const char *end_source, char *begin_destination);

// записывает по адресу beginDestination элементы начиная с beginSource заканчивая endSource, удовлетворяющие функции-предикату f.
// Функция возвращает указатель на следующий свободный для записи фрагмент в памяти.
char* copy_if(const char *begin_source, const char *end_source, char *begin_destination, int (*f)(int));

// записывает по адресу beginDestination элементы из фрагмента памяти начиная с rbeginSource
// заканчивая rendSource, удовлетворяющие функции-предикату f.
// Функция возвращает значение beginDestination по окончанию работы функции.
char* copy_if_reverse(char *r_begin_source, char *r_end_source, char *begin_destination, int (*f)(int));

// возвращает конец строки
char* get_end_of_string(char* s);

// функция тестирования
void assert_string(const char* expected, char* got, char const* file_name, char const* func_name, int line);

// возвращает значение 0, если слово не было считано, иначе возвращено значение 1 и в переменную word типа WordDescriptor
//будут записаны позиции начала слова, и первого символа после конца слова.
bool get_word(char* begin_search, word_descriptor* word);

//
bool get_word_without_space(char* begin_search, word_descriptor* word);

//
bool get_word_reverse(char* r_begin, char* r_end, word_descriptor* word);

//
void free_string(char* string);

//
void print_word(word_descriptor word);

//
void free_bag(bag_of_words* bag);

//
bool is_palindrome_word(word_descriptor* word);

//
bool is_word_equal(const word_descriptor word1, const word_descriptor word2);

//
void word_descriptor_to_string(word_descriptor word, char* dest);

#endif //LAB_WORK_17_STRING__H
