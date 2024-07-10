#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function to check if the input has a custom delimiter
bool is_custom_delimiter(const char* input) {
    return (input[0] == '/' && input[1] == '/') || (input[0] == '\n');
}

// Function to find custom delimiter and its end position
void find_custom_delimiter(const char* input, const char** start_pos, const char** end_pos) {
    if (input[0] == '/') {
        *start_pos = input + 2; // Skip over '//'
        *end_pos = strchr(*start_pos, '\n');
    } else if (input[0] == '\n') {
        *start_pos = input + 1; // Skip '\n'
        *end_pos = NULL; // No delimiter after '\n'
    }
}

// Function to extract custom delimiter
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

// Function to skip over double slash custom delimiter
const char* skip_double_slash(const char* input) {
    if (input[0] == '/' && input[1] == '/') {
        return strchr(input, '\n') + 1; // Skip over '//'
    }
    return input;
}

// Function to skip newline custom delimiter
const char* skip_newline(const char* input) {
    if (input[0] == '\n') {
        return input + 1; // Skip '\n'
    }
    return input;
}

// Function to get starting position for numbers after skipping delimiters
const char* get_start_position(const char* input) {
    return skip_double_slash(skip_newline(input));
}

// Function to extract numbers after skipping delimiters
void extract_numbers(const char* input, char* numbers) {
    const char* start_pos = get_start_position(input);
    strcpy(numbers, start_pos);
}

// Function to parse input and extract delimiter and numbers
void parse_input(const char* input, char* delimiter, char* numbers) {
    if (is_custom_delimiter(input)) {
        extract_custom_delimiter(input, delimiter);
    } else {
        strcpy(delimiter, ",");
    }
    extract_numbers(input, numbers);
}

// Function to split numbers based on delimiter and convert to integers
void split_numbers(const char* str, const char* delimiter, int* numbers, int* count) {
    char* copy_str = strdup(str);
    char* token = strtok(copy_str, delimiter);
    while (token) {
        numbers[(*count)++] = atoi(token);
        token = strtok(NULL, delimiter);
    }
    free(copy_str);
}

// Function to check if there are negative numbers in the array
bool has_negatives(int* numbers, int size) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] < 0) {
            return true;
        }
    }
    return false;
}

// Function to construct message for negative numbers
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

// Function to check for negatives and print error message if found
void check_negatives(int* numbers, int size) {
    if (has_negatives(numbers, size)) {
        char message[256];
        construct_negative_message(numbers, size, message);
        fprintf(stderr, "%s\n", message);
        exit(EXIT_FAILURE);
    }
}

// Function to sum valid numbers (less than or equal to 1000)
void sum_valid_numbers(int* num_array, int num_count, int* sum) {
    for (int i = 0; i < num_count; i++) {
        if (num_array[i] <= 1000) {
            *sum += num_array[i];
        }
    }
}

// Main function to add numbers based on input string
int add(const char* input) {
    if (!input || !*input) {
        return 0; // Handle empty input
    }

    char delimiter[10] = {0};
    char numbers[1000] = {0};
    parse_input(input, delimiter, numbers); // Parse input to get delimiter and numbers

    int num_array[1000];
    int num_count = 0;
    split_numbers(numbers, delimiter, num_array, &num_count); // Split numbers using delimiter

    check_negatives(num_array, num_count); // Check for negative numbers

    int sum = 0;
    sum_valid_numbers(num_array, num_count, &sum); // Calculate sum of valid numbers

    return sum;
}

