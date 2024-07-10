#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


bool is_custom_delimiter(const char* input) {
    return (input[0] == '/' && input[1] == '/');
}

void extract_custom_delimiter(const char* input, char* delimiter) {
    const char* start_pos = input + 2; // Skip over '//'
    const char* end_pos = strchr(start_pos, '\n');
    if (end_pos) {
        strncpy(delimiter, start_pos, end_pos - start_pos);
        delimiter[end_pos - start_pos] = '\0';
    } else {
        strcpy(delimiter, ",");
    }
}

void extract_delimiter(const char* input, char* delimiter) {
    if (is_custom_delimiter(input)) {
        extract_custom_delimiter(input, delimiter);
    } else {
        strcpy(delimiter, ",");
    }
}

void copy_number(char** input, char** numbers) {
    if (**input == ',' || **input == '\n') {
        *(*numbers)++ = ',';
        (*input)++;
    } else {
        while (**input && **input != ',' && **input != '\n') {
            *(*numbers)++ = *(*input)++;
        }
    }
}

void copy_numbers(const char* input, char* numbers) {
    char* numbers_start = numbers;
    while (*input) {
        copy_number(&input, &numbers);
    }
    *numbers = '\0';
}

void strip_newlines(char* numbers) {
    char* src = numbers;
    char* dst = numbers;
    while (*src) {
        if (*src != '\n') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

void copy_numbers_with_delimiters(const char* input, char* numbers) {
    copy_numbers(input, numbers);
    strip_newlines(numbers);
}

void extract_numbers(const char* input, char* numbers) {
    const char* start_pos = input;
    if (is_custom_delimiter(input)) {
        start_pos = strchr(input, '\n') + 1;
    }

    copy_numbers_with_delimiters(start_pos, numbers);
}

void split_numbers(const char* str, const char* delimiter, int* numbers, int* count) {
    char* copy_str = strdup(str);
    char* token = strtok(copy_str, delimiter);
    while (token) {
        numbers[(*count)++] = atoi(token);
        token = strtok(NULL, delimiter);
    }
    free(copy_str);
}

bool has_negatives(int* numbers, int size) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            return true;
        }
    }
    return false;
}

void construct_negative_message(int* numbers, int size, char* message) {
    strcpy(message, "negatives not allowed: ");
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            char num_str[12];
            snprintf(num_str, sizeof(num_str), "%d", numbers[i]);
            strcat(message, num_str);
            strcat(message, " ");
        }
    }
}

void check_negatives(int* numbers, int size) {
    if (has_negatives(numbers, size)) {
        char message[256];
        construct_negative_message(numbers, size, message);
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}

void sum_valid_numbers(int* num_array, int num_count, int* sum) {
    for (int i = 0; i < num_count; i++) {
        if (num_array[i] <= 1000) {
            *sum += num_array[i];
        }
    }
}

int add(const char* input) {
    if (!input || !*input) {
        return 0;
    }

    char delimiter[10] = {0};
    char numbers[1000] = {0};
    extract_delimiter(input, delimiter);
    extract_numbers(input, numbers);

    int num_array[1000];
    int num_count = 0;
    split_numbers(numbers, delimiter, num_array, &num_count);

    check_negatives(num_array, num_count);

    int sum = 0;
    sum_valid_numbers(num_array, num_count, &sum);

    return sum;
}
