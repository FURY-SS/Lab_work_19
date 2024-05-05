// Created by Vadim on 05.05.2024.

#ifndef LAB_WORK_19_LEAVE_LONGEST_WORD_H
#define LAB_WORK_19_LEAVE_LONGEST_WORD_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <time.h>
#include <string.h>
#include <assert.h>

#define MAX_LINE_SIZE 80

void generate_text_file(const char* filename, int lines, int word, int max_word_size) {
    srand(time(NULL));

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < word; j++) {
            for (int k = 0; k < rand() % max_word_size + 1; k++) {
                fprintf(file, "%c", 'a' + rand() % 26);
            }
            fprintf(file, " ");
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void leave_longest_word(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }


    char buff[MAX_LINE_SIZE] = "";
    char* rec_ptr = _string_buffer;

    fgets(buff, sizeof(buff), file);

    size_t length = strlen_(buff);
    length = length == 0 ? 1 : length;

    rec_ptr = copy(buff, buff + length - 1, rec_ptr);
    *rec_ptr++ = ' ';


    size_t amount_word_in_line = 0;
    char* begin_search = _string_buffer;
    while (get_word_without_space(begin_search, &_bag.words[_bag.size])) {
        begin_search = _bag.words[_bag.size].end + 1;
        amount_word_in_line++;
        _bag.size++;
    }


    while (fgets(buff, sizeof(buff), file)) {
        rec_ptr = copy(buff, buff + strlen_(buff) - 1, rec_ptr);
        *rec_ptr++ = ' ';

        while (get_word_without_space(begin_search, &_bag.words[_bag.size])) {
            begin_search = _bag.words[_bag.size].end + 1;
            _bag.size++;
        }
    }

    fclose(file);


    file = fopen(filename, "w");
    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < _bag.size; i += amount_word_in_line) {
        word_descriptor word_max_length = _bag.words[i];
        size_t max_length = word_max_length.end - word_max_length.begin + 1;

        for (size_t j = i + 1; j < i + amount_word_in_line; j++) {
            size_t current_length = _bag.words[j].end - _bag.words[j].begin + 1;

            if (current_length > max_length) {
                word_max_length = _bag.words[j];
                max_length = current_length;
            }
        }

        char* write_ptr = word_max_length.begin;
        while (write_ptr <= word_max_length.end) {
            fprintf(file, "%c", *write_ptr);
            write_ptr++;
        }

        fprintf(file, "\n");
    }

    free_bag(&_bag);
    fclose(file);
}

void test_leave_longest_word_1_empty_file() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_5_test_1.txt";


    FILE* file = fopen(filename, "w");
    fclose(file);

    leave_longest_word(filename);

    file = fopen(filename, "r");

    char data[MAX_LINE_SIZE] = "";
    fprintf(file, "%s", data);

    fclose(file);

    assert(strcmp_(data, "") == 0);
}

void test_leave_longest_word_2_one_element_in_line() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_5_test_2.txt";

    char line1[] = "abcd";
    char line2[] = "aaa";
    char line3[] = "go";

    FILE* file = fopen(filename, "w");

    fprintf(file, "%s \n", line1);
    fprintf(file, "%s \n", line2);
    fprintf(file, "%s \n", line3);

    fclose(file);

    leave_longest_word(filename);

    file = fopen(filename, "r");

    char res_line1[10] = "";
    fscanf(file, "%s\n", res_line1);

    char res_line2[10] = "";
    fscanf(file, "%s\n", res_line2);

    char res_line3[10] = "";
    fscanf(file, "%s\n", res_line3);

    fclose(file);

    assert(strcmp_(line1, res_line1) == 0);
    assert(strcmp_(line2, res_line2) == 0);
    assert(strcmp_(line3, res_line3) == 0);
}

void test_leave_longest_word_3_more_element_in_line() {
    const char filename[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_5_test_3.txt";

    char line1[] = "abcde aaa ";
    char line2[] = "efg qwert ";
    char line3[] = "hi my to aaa";

    FILE* file = fopen(filename, "w");

    fputs(line1, file);
    fprintf(file, "\n");
    fputs(line2, file);
    fprintf(file, "\n");
    fputs(line3, file);
    fprintf(file, "\n");

    fclose(file);

    leave_longest_word(filename);

    file = fopen(filename, "r");

    char res_line1[10] = "";
    fscanf(file, "%s\n", res_line1);

    char res_line2[10] = "";
    fscanf(file, "%s\n", res_line2);

    char res_line3[10] = "";
    fscanf(file, "%s\n", res_line3);

    fclose(file);

    char check1[] = "abcde";
    char check2[] = "qwert";
    char check3[] = "aaa";

    assert(strcmp_(check1, res_line1) == 0);
    assert(strcmp_(check2, res_line2) == 0);
    assert(strcmp_(check3, res_line3) == 0);
}

void test_leave_longest() {
    test_leave_longest_word_1_empty_file();
    test_leave_longest_word_2_one_element_in_line();
    test_leave_longest_word_3_more_element_in_line();
}

#endif //LAB_WORK_19_LEAVE_LONGEST_WORD_H