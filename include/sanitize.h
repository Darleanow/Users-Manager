#pragma once

#ifndef SANITIZE_INPUTS
#define SANITIZE_INPUTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100

// Checks if destined given string can be assigned to an int without issues
int sanitize_number_input(char* input);

//Checks if string can be converted to float, also checks if int was given so it can just return a .2f version of the input
float string_to_float(const char* str);

// Checks if destined given string can be assigned to an char* without issues
// Checks for special chars etc..
int sanitize_string_input(char* input);

void no_bug_inpt(char** str);

#endif