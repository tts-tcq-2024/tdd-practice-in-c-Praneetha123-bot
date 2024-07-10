#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


bool is_custom_delimiter(const char* input) {
    return (input[0] == '/' && input[1] == '/') || (input[0] == '\n');
}

void find_custom_delimiter(const char* input, const char** start_pos, const char** end_pos) {
    if (input[0] == '/') {
        *start_pos = input + 2; // Skip over '//'
        *end_pos = strchr(*start_pos, '\n');
    } else if (input[0] == '\n') {
        *start_pos = input + 1; // Skip '\n'
        *end_pos = NULL; // No delimiter after '\n'
    }
}

void extract_custom_delimiter(const char* input, char* delimiter) {
    const char* start_pos;
    const char* end_pos;
    find_custom_delimiter(input, &start_pos, &end_pos);

    if (end_pos) {
        strncpy(delimiter, start_pos, end_pos - start_pos);
        delimiter[end_pos - start_pos] = '\0';
    } else {
        strcpy(delimiter, ",");
    }
}

const char* skip_double_slash(const char* input) {
    if (input[0] == '/' && input[1] == '/') {
        return strchr(input, '\n') + 1; // Skip over '//'
    }
    return input;
}

const char* skip_newline(const char* input) {
    if (input[0] == '\n') {
        return input + 1; // Skip '\n'
    }
    return input;
}

const char* get_start_position(const char* input) {
    return skip_double_slash(skip_newline(input));
}

void extract_numbers(const char* input, char* numbers) {
    const char* start_pos = get_start_position(input);
    strcpy(numbers, start_pos);
}

void parse_input(const char* input, char* delimiter, char* numbers) {
    if (is_custom_delimiter(input)) {
        extract_custom_delimiter(input, delimiter);
    } else {
        strcpy(delimiter, ",");
    }
    extract_numbers(input, numbers);
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
    parse_input(input, delimiter, numbers);

    int num_array[1000];
    int num_count = 0;
    split_numbers(numbers, delimiter, num_array, &num_count);

    check_negatives(num_array, num_count);

    int sum = 0;
    sum_valid_numbers(num_array, num_count, &sum);

    return sum;
}
