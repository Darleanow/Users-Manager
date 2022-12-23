#include "../include/sanitize.h"


int sanitize_number_input(char* input) {
  // Check if the input is NULL
    if (input == NULL) {
        return 0;
    }

    // Check if the input is too long
    if (strlen(input) > MAX_INPUT_LENGTH) {
        return 0;
    }

    // Check if the input contains any non-numeric characters
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit((unsigned char)input[i])) {
            return 0;
        }
    }

    // Check if the input is within the range of an int
    long long num = strtoll(input, NULL, 10);
    if (num < INT_MIN || num > INT_MAX) {
        return 0;
    }

    // If none of the above checks failed, the input is considered sanitized
    return 1;
}

float string_to_float(const char* str) {
    char* end;
    float val = strtof(str, &end);

    if (end == str || *end != '\0') {
      // str was not a valid float, so check if it's an integer
        long int val = strtol(str, &end, 10);
        if (end == str || *end != '\0') {
          // str was not a valid integer either
            return -1;
        }
        else {
       // str was a valid integer, so convert it to a float and return it
            return (float)val / 100;
        }
    }

    // Round val to two decimal places
    val = (int)(val * 100 + 0.5) / 100.0;

    return val;
}

int sanitize_string_input(char* input) {
    // Check if the input is NULL
    if (input == NULL) {
        return 0;
    }

    // Check if the input is too long
    if (strlen(input) > MAX_INPUT_LENGTH) {
        return 0;
    }

    // Check if the input contains any non-printable characters or control characters
    for (int i = 0; i < strlen(input); i++) {
        if (!isprint((unsigned char)input[i]) || iscntrl((unsigned char)input[i])) {
            return 0;
        }
    }

    // If none of the above checks failed, the input is considered sanitized
    return 1;
}

void no_bug_inpt(char** str)
{
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    // Remove the newline character at the end of the string
    buffer[strcspn(buffer, "\n")] = '\0';
    // Allocate memory for the input string and copy the buffer to the input string
    *str = malloc(strlen(buffer) + 1);
    strcpy(*str, buffer);
    while (strlen(&str) == 0)
    {
        fgets(buffer, sizeof(buffer), stdin);
        // Remove the newline character at the end of the string
        buffer[strcspn(buffer, "\n")] = '\0';
        // Allocate memory for the input string and copy the buffer to the input string
        *str = malloc(strlen(buffer) + 1);
        strcpy(*str, buffer);
    }
}