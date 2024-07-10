#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void check_negatives(int* numbers, int size) {
    bool has_negative = false;
    char message[256] = "negatives not allowed: ";
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            char num_str[12];
            snprintf(num_str, sizeof(num_str), "%d", numbers[i]);
            strcat(message, num_str);
            strcat(message, " ");
            has_negative = true;
        }
    }
    if (has_negative) {
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}

void extract_delimiter_and_numbers(const char* input, char* delimiter, char* numbers) {
    if (input[0] == '/' && input[1] == '/') {
        const char* newline_pos = strchr(input, '\n');
        if (newline_pos) {
            strncpy(delimiter, input + 2, newline_pos - input - 2);
            delimiter[newline_pos - input - 2] = '\0';
            strcpy(numbers, newline_pos + 1);
        }
    } else {
        strcpy(delimiter, ",");
        strcpy(numbers, input);
    }
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

int add(const char* input) {
    if (!input || !*input) {
        return 0;
    }

    char delimiter[10] = {0};
    char numbers[1000] = {0};
    extract_delimiter_and_numbers(input, delimiter, numbers);

    int num_array[1000];
    int num_count = 0;
    split_numbers(numbers, delimiter, num_array, &num_count);

    check_negatives(num_array, num_count);

    int sum = 0;
    for (int i = 0; i < num_count; i++) {
        if (num_array[i] <= 1000) {
            sum += num_array[i];
        }
    }

    return sum;
}
