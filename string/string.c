// Created by Vadim on 08.04.2024.

#include <stdio.h>
#include <memory.h>
#include <ctype.h>
#include "string.h"
#include <stdbool.h>

char _string_buffer[MAX_STRING_SIZE + 1];

bag_of_words _bag = {.words = NULL, .size = 0};
bag_of_words _bag2 = {.words = NULL, .size = 0};

int length_of_string(const char *str) {
    int length = 0;

    while (*str) {
        length++;
        str++;
    }

    return length;
}

size_t strlen_(char *begin) {
    char *end = begin;

    while (*end != '\0') {
        end++;
    }

    return end - begin;
}

char* find(char *begin, char *end, int ch) {

    while (begin != end && *begin != ch) {
        begin++;
    }

    return begin;
}

char* find_non_space(char *begin) {
    while (*begin != '\0' && isspace(*begin)) {
        begin++;
    }

    return begin;
}

char* find_space(char *begin) {
    while (*begin != '\0' && !isspace(*begin)) {
        begin++;
    }

    return begin;
}

char* find_non_space_reverse(char *r_begin, const char *r_end) {
    while (r_begin != r_end && isspace(*r_begin)) {
        r_begin--;
    }

    return r_begin;
}

char* find_space_reverse(char *r_begin, const char *r_end) {
    while (r_begin != r_end && !isspace(*r_begin)) {
        r_begin--;
    }

    return r_begin;
}

int strcmp_(const char *lhs, const char *rhs) {
    while (*lhs != '\0' && *rhs != '\0' && *lhs == *rhs) {
        lhs++;
        rhs++;
    }

    return *(const unsigned char*) lhs - *(const unsigned char*) rhs;
}

char* copy(const char* begin_source, const char* end_source, char* begin_destination) {
    while (begin_source != end_source) {
        *begin_destination = *begin_source;
        ++begin_source;
        ++begin_destination;
    }

    return begin_destination;
}

char* copy_if(const char* begin_source, const char* end_source, char* begin_destination, int (*f)(int)) {

    while (begin_source != end_source) {
        if (f(*begin_source)) {
            *begin_destination = *begin_source;
            begin_destination++;
        }

        begin_source++;
    }

    return begin_destination;
}

char* copy_if_reverse(char *r_begin_source, char *r_end_source, char *begin_destination, int (*f)(int)) {
    char* start = r_begin_source;

    while (start != r_end_source) {
        if (f(*start)) {
            *begin_destination = *start;
            begin_destination++;
        }

        start--;
    }

    return begin_destination;
}

char* get_end_of_string(char* s) {
    char* start = s;
    while (*start != '\0')
        start++;

    return start;
}

void assert_string(const char* expected, char* got, char const* file_name, char const* func_name, int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", file_name);
        fprintf(stderr, "%s - failed on line %d\n", func_name, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", func_name);
}

bool get_word(char* begin_search, word_descriptor* word) {
    word->begin = find_non_space(begin_search);
    if (*word->begin == '\0')
        return false;

    word->end = find_space(word->begin);

    return true;
}

bool is_sub_word(const word_descriptor word1, const word_descriptor word2) {
    char* begin1 = word1.begin;
    char* begin2 = word2.begin;

    while (begin1 <= word1.end) {
        if (*begin1 != *begin2)
            return false;

        begin1++;
        begin2++;
    }

    if (word1.end - begin1 > 0)
        return false;

    return true;
}

bool get_word_without_space(char* begin_search, word_descriptor* word) {
    word->begin = find_non_space(begin_search);
    if (*word->begin == '\0')
        return false;

    word->end = find_space(word->begin) - 1;

    return true;
}

bool get_word_reverse(char* r_begin, char* r_end, word_descriptor* word) {
    if (word->begin == r_end)
        return false;

    word->end = find_non_space_reverse(r_begin, r_end);

    word->begin = find_space_reverse(r_begin, r_end);
    word->begin = word->begin == r_end ? word->begin : word->begin + 1;

    return true;
}

void free_string(char* string) {
    char* ptr = string;
    while (*ptr) {
        *ptr = '\0';
        ptr++;
    }
}

void print_word(word_descriptor word) {
    while (word.begin <= word.end) {
        printf("%c", *word.begin);
        word.begin++;
    }
    printf("\n");
}

void free_bag(bag_of_words* bag) {
    for (size_t i = 0; i < bag->size; i++) {
        bag->words[i].begin = NULL;
        bag->words[i].end = NULL;
    }

    bag->size = 0;
}

bool is_palindrome_word(word_descriptor* word) {
    char* start = word->begin;
    char* end = word->end - 1;

    while (start < end) {
        if (*start != *end)
            return false;

        start++;
        end--;
    }

    return true;
}

bool is_word_equal(const word_descriptor word1, const word_descriptor word2) {
    char* begin1 = word1.begin;
    char* begin2 = word2.begin;

    while (begin1 < word1.end && begin2 < word2.end) {
        if (*begin1 != *begin2)
            return false;

        begin1++;
        begin2++;
    }

    if (word1.end - begin1 > 0 || word2.end - begin2 > 0)
        return false;

    return true;
}

void word_descriptor_to_string(word_descriptor word, char* dest) {
    if (word.begin == NULL && word.end == NULL)
        return;

    while (word.begin <= word.end) {
        *dest = *word.begin;
        word.begin++;
        dest++;
    }

    *dest = '\0';
}