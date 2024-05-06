// Created by Vadim on 06.05.2024.

#ifndef LAB_WORK_19_UPDATE_PRODUCT_H
#define LAB_WORK_19_UPDATE_PRODUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "string.h"
#include "../vector/vector_void.h"
#define MAX_LENGTH_STRING 200

typedef struct product {
    char product_name[MAX_LENGTH_STRING];
    int unit_price;
    int total_cost;
    int quantity;
} product;

typedef struct order {
    char order_name[MAX_LENGTH_STRING];
    int quantity;
} order;

void generate_product_and_order(const char* filename1, const char* filename2) {
    srand(time(NULL));

    FILE* file1 = fopen(filename1, "wb");
    if (file1 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    FILE* file2 = fopen(filename2, "wb");
    if (file2 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    int amount_product = rand() % 15 + 1;
    int amount_order = amount_product % 2 + 1;

    for (int i = 0; i < amount_product; i++) {
        product pr;
        order od;

        pr.unit_price = rand() % 100 + 1;
        pr.quantity = rand() % 20 + 1;
        pr.total_cost = pr.unit_price * pr.quantity;

        int name_length = rand() % 10 + 1;
        char* product_rec_ptr = pr.product_name;
        char* order_rec_ptr = od.order_name;

        for (int j = 0; j < name_length; j++) {
            char ch = rand() % 26 + 97;

            *product_rec_ptr = ch;
            product_rec_ptr++;

            if (amount_order > 0) {
                *order_rec_ptr = ch;
                order_rec_ptr++;
            }
        }

        *product_rec_ptr = '\0';
        if (amount_order > 0) {
            *order_rec_ptr = '\0';
            od.quantity = rand() % 25 + 1;
        }

        fwrite(&pr, sizeof(product), 1, file1);
        if (amount_order > 0)
            fwrite(&od, sizeof(order), 1, file2);

        amount_order--;
    }

    fclose(file1);
    fclose(file2);
}

void print_product_and_order(const char* filename1, const char* filename2) {
    printf("Product: \n");

    FILE* file1 = fopen(filename1, "rb");
    if (file1 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    product pr;
    while (fread(&pr, sizeof(product), 1, file1) == 1) {
        printf("name: %s unit price: %d total cost: %d quantity: %d\n", pr.product_name, pr.unit_price, pr.total_cost, pr.quantity);
    }

    fclose(file1);


    printf("Order: \n");

    FILE* file2 = fopen(filename2, "rb");
    if (file2 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    order od;
    while (fread(&od, sizeof(order), 1, file2) == 1)
        printf("name: %s quantity: %d\n", od.order_name, od.quantity);

    fclose(file2);
}

void update_product(const char* filename1, const char* filename2) {
    vector_void v1 = create_vector_void(16, sizeof(product));
    vector_void v2 = create_vector_void(16, sizeof(order));

    FILE* file1 = fopen(filename1, "rb");
    if (file1 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    product pr;
    while (fread(&pr, sizeof(product), 1, file1) == 1)
        push_back_v(&v1, &pr);

    fclose(file1);


    FILE* file2 = fopen(filename2, "rb");
    if (file2 == NULL) {
        printf("reading error\n");
        exit(1);
    }

    order od;
    while (fread(&od, sizeof(order), 1, file2) == 1)
        push_back_v(&v2, &od);

    for (size_t i = 0; i < v1.size; i++) {
        product curr_pr;
        get_vector_value_v(&v1, i, &curr_pr);
        for (size_t j = 0; j < v2.size; j++) {
            order curr_od;
            get_vector_value_v(&v2, j, &curr_od);

            if (strcmp_(curr_pr.product_name, curr_od.order_name) == 0) {
                curr_pr.quantity = pr.quantity > od.quantity ? pr.quantity - od.quantity : 0;
                curr_pr.total_cost = pr.unit_price * curr_pr.quantity;
                get_vector_value_v(&v1, i, &curr_pr);
            }
        }
    }

    file1 = fopen(filename1, "wb");

    for (size_t i = 0; i < v1.size; i++) {
        product read_pr;
        get_vector_value_v(&v1, i, &read_pr);
        if (read_pr.quantity != 0)
            fwrite(&read_pr, sizeof(product), 1, file1);
    }

    delete_vector_v(&v1);
    delete_vector_v(&v2);

    fclose(file1);
}

void test_update_product_1_empty_files() {
    const char filename1[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_11.txt";
    const char filename2[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_12.txt";

    FILE* file = fopen(filename1, "wb");
    fclose(file);

    file = fopen(filename2, "wb");
    fclose(file);

    update_product(filename1, filename2);

    char data1[10] = "";
    file = fopen(filename1, "rb");
    fread(data1, sizeof(data1), 1, file);
    fclose(file);

    char data2[10] = "";
    file = fopen(filename1, "rb");
    fread(data2, sizeof(data2), 1, file);
    fclose(file);

    assert(strcmp_(data1, "") == 0);
    assert(strcmp_(data2, "") == 0);
}


void test_update_product_2_first_file_empty() {
    const char filename1[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_21.txt";
    const char filename2[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_22.txt";

    FILE* file = fopen(filename1, "wb");
    fclose(file);

    file = fopen(filename2, "wb");

    order od = {.order_name="name", .quantity = 4};

    fwrite(&od, sizeof(order), 1, file);

    fclose(file);

    update_product(filename1, filename2);

    char data[10] = "";
    file = fopen(filename1, "rb");
    fread(data, sizeof(data), 1, file);
    fclose(file);

    file = fopen(filename2, "rb");

    order res_od;
    fread(&res_od, sizeof(order), 1, file);

    fclose(file);

    assert(strcmp_(data, "") == 0);
    assert(strcmp_(od.order_name, res_od.order_name) == 0 && od.quantity == res_od.quantity);
}


void test_update_product_3_second_file_empty() {
    const char filename1[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_31.txt";
    const char filename2[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_32.txt";

    FILE* file = fopen(filename1, "wb");
    product pr = {.product_name="name", .unit_price=10, .total_cost=20, .quantity=2};
    fwrite(&pr, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "wb");
    fclose(file);

    update_product(filename1, filename2);

    file = fopen(filename1, "rb");
    product res_pr;
    fread(&res_pr, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "rb");
    char data[10] = "";
    fread(data, sizeof(data), 1, file);
    fclose(file);

    assert(strcmp_(pr.product_name, res_pr.product_name) == 0);
    assert(pr.unit_price == res_pr.unit_price);
    assert(pr.total_cost == res_pr.total_cost);
    assert(pr.quantity == res_pr.quantity);
    assert(strcmp_(data, "") == 0);
}


void test_update_product_4_order_more_product() {
    const char filename1[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_41.txt";
    const char filename2[] = "C:\\Users\\Vadim\\CLionProjects\\lab_work_19\\tasks_tests\\task_10_test_42.txt";

    product pr1 = {.product_name="name1", .unit_price=10, .total_cost=30, .quantity=3};
    product pr2 = {.product_name="name2", .unit_price=20, .total_cost=40, .quantity=2};
    order od = {.order_name="name2", .quantity=10};

    FILE* file = fopen(filename1, "wb");
    fwrite(&pr1, sizeof(product), 1, file);
    fwrite(&pr2, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "wb");
    fwrite(&od, sizeof(order), 1, file);
    fclose(file);

    update_product(filename1, filename2);

    product res_pr;
    order res_od;

    file = fopen(filename1, "rb");
    fread(&res_pr, sizeof(product), 1, file);
    fclose(file);

    file = fopen(filename2, "rb");
    fread(&res_od, sizeof(order), 1, file);
    fclose(file);

    assert(strcmp_(pr1.product_name, res_pr.product_name) == 0);
    assert(pr1.unit_price == res_pr.unit_price);
    assert(pr1.total_cost == res_pr.total_cost);
    assert(pr1.quantity == res_pr.quantity);
    assert(strcmp_(od.order_name, res_od.order_name) == 0 && od.quantity == res_od.quantity);

}

void test_update_product() {
    test_update_product_1_empty_files();
    test_update_product_2_first_file_empty();
    test_update_product_3_second_file_empty();
    test_update_product_4_order_more_product();
}

#endif //LAB_WORK_19_UPDATE_PRODUCT_H