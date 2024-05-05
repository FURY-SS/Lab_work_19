// Created by Vadim on 05.05.2024.

#ifndef LAB_WORK_19_SPECIAL_WORD_H
#define LAB_WORK_19_SPECIAL_WORD_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../string/string.h"

#define LETTERS_SHIFT 97

int compare_letters(const void* s1, const void* s2) {
    return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}

void sort_word_letters(word_descriptor* word) {
    qsort(word->begin, word->end - word->begin + 1, sizeof(char), compare_letters);
}

bool letters_belong_word(word_descriptor sub_word, word_descriptor word) {
    bool include[26] = {0};

    char* start = word.begin;
    char* end = word.end + 1;

    while (start != end) {
        if (isalpha(*start))
            include[*start - LETTERS_SHIFT] = true;

        start++;
    }

    while (sub_word.begin <= sub_word.end) {
        if (!include[*sub_word.begin - LETTERS_SHIFT])
            return false;

        sub_word.begin++;
    }

    return true;
}

void generate_string(const char* filename, char* source_string) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    size_t string_length = strlen_(source_string);

    for (size_t i = 0; i <= string_length; i++)
        fprintf(file, "%c", source_string[i]);

    fclose(file);
}

void special_word(const char* filename, char* source_word) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length == 0)
        return;

    fread(_string_buffer, sizeof(char), length, file);
    _string_buffer[length] = '\0';

    fclose(file);

    word_descriptor word;
    get_word_without_space(source_word, &word);
    sort_word_letters(&word);

    bag_of_words words = {.size = 0};
    char* begin_search = _string_buffer;
    while (get_word_without_space(begin_search, &words.words[words.size])) {
        begin_search = words.words[words.size].end + 1;
        words.size++;
    }

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < words.size; i++) {
        if (letters_belong_word(word, words.words[i])) {
            while (words.words[i].begin <= words.words[i].end) {
                fprintf(file, "%c", *words.words[i].begin);
                words.words[i].begin++;
            }
            fprintf(file, " ");
        }
    }

    fprintf(file, "%c", '\0');

    free_string(_string_buffer);
    free_bag(&words);

    fclose(file);
}

void test_filter_word_1_empty_file() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_4_test_1.txt";

    generate_string(filename, "");
    char source_word[] = "adcde";
    special_word(filename, source_word);

    FILE* file = fopen(filename, "r");
    char data[10] = "";
    fscanf(file, "%s", data);
    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_filter_word_2_sequence_not_in_line() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_4_test_2.txt";

    generate_string(filename, "abcd jkl");
    char source_word[] = "sqr";
    special_word(filename, source_word);

    FILE* file = fopen(filename, "r");
    char data[10] = "";
    fscanf(file, "%s", data);
    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_filter_word_3_sequence_in_line() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_4_test_3.txt";

    generate_string(filename, "abcde ghj abc");
    char source_word[] = "abc";
    special_word(filename, source_word);

    FILE* file = fopen(filename, "r");
    char data[40] = "";
    fgets(data, sizeof(data), file);
    fclose(file);

    assert(strcmp_(data, "abcde abc ") == 0);
}

void test_filter_word() {
    test_filter_word_1_empty_file();
    test_filter_word_2_sequence_not_in_line();
    test_filter_word_3_sequence_in_line();
}

#endif //LAB_WORK_19_SPECIAL_WORD_H
