#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Helper function to check if the input has a custom delimiter
bool has_custom_delimiter(const char* input) {
    return input[0] == '/' && input[1] == '/';
}

// Helper function to extract the custom delimiter from the input
void extract_custom_delimiter(const char* input, char* delimiter) {
    const char* start = input + 2; // Skip over "//"
    const char* end = strchr(start, '\n');
    if (end) {
        strncpy(delimiter, start, end - start);
        delimiter[end - start] = '\0';
    } else {
        strcpy(delimiter, ",");
    }
}

// Helper function to skip the delimiter definition in the input
const char* skip_delimiter_definition(const char* input) {
    if (has_custom_delimiter(input)) {
        return strchr(input, '\n') + 1; // Skip over "//[delimiter]\n"
    }
    return input;
}

// Helper function to split numbers using the specified delimiter
void split_numbers(const char* input, const char* delimiter, int* numbers, int* count) {
    char* copy = strdup(input);
    char* token = strtok(copy, delimiter);
    while (token) {
        numbers[(*count)++] = atoi(token);
        token = strtok(NULL, delimiter);
    }
    free(copy);
}

// Helper function to check for negative numbers and build an error message
bool check_negatives(int* numbers, int count, char* message) {
    bool has_negatives = false;
    strcpy(message, "negatives not allowed: ");
    for (int i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            has_negatives = true;
            char num_str[12];
            snprintf(num_str, sizeof(num_str), "%d ", numbers[i]);
            strcat(message, num_str);
        }
    }
    return has_negatives;
}

// Helper function to calculate the sum of valid numbers
int calculate_sum(int* numbers, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        if (numbers[i] <= 1000) {
            sum += numbers[i];
        }
    }
    return sum;
}

// Main add function
int add(const char* input) {
    if (*input == '\0') {
        return 0;
    }

    char delimiter[10];
    extract_custom_delimiter(input, delimiter);

    const char* numbers_str = skip_delimiter_definition(input);
    int numbers[1000];
    int count = 0;
    split_numbers(numbers_str, delimiter, numbers, &count);

    char message[256];
    if (check_negatives(numbers, count, message)) {
        printf("%s\n", message);
        // Handle the error, e.g., throw an exception
        return -1; // Indicate an error
    }

    return calculate_sum(numbers, count);
}
