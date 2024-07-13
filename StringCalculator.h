#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool has_custom_delimiter(const char* input) {
    return input[0] == '/' && input[1] == '/';
}


void extract_custom_delimiter(const char* input, char* delimiter) {
    const char* start = input + 2; // Skip over "//"
    const char* end = strchr(start, '\n');
    if (end) {
        strncpy(delimiter, start, end - start);
        delimiter[end - start] = '\0';
    } 
}

const char* skip_delimiter_definition(const char* input) {
    if (has_custom_delimiter(input)) {
        return strchr(input, '\n') + 1; // Skip over "//[delimiter]\n"
    }
}

void split_numbers(const char* input, const char* delimiters, int* numbers, int* count) {
    char* copy = strdup(input);
    char* token = strtok(copy, delimiters);
    while (token) {
        numbers[(*count)++] = atoi(token);
        token = strtok(NULL, delimiters);
    }
    free(copy);
}

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

int calculate_sum(int* numbers, int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        if (numbers[i] <= 1000) {
            sum += numbers[i];
        }
    }
    return sum;
}

int parse_and_calculate(const char* input, const char* delimiters) {
    int numbers[1000];
    int count = 0;
    split_numbers(input, delimiters, numbers, &count);

    char message[256];
    if (check_negatives(numbers, count, message)) {
        return -1; // Indicate an error
    }

    return calculate_sum(numbers, count);
}

int add(const char* input) {
    if (*input == '\0') {
        return 0;
    }

    char delimiter[10] = ",\n";
    if (has_custom_delimiter(input)) {
        extract_custom_delimiter(input, delimiter);
        input = skip_delimiter_definition(input);
    }

    return parse_and_calculate(input, delimiter);
}
