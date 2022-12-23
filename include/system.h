#pragma once
#ifndef SYSTEM_FOLL
#define SYSTEM_FOLL
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

//Go to an XY location on the console screen
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

//Outputs White Background and Black text to emulate a selection
#define selected() printf("\033[30;47m")

//Resets the Background and text colors to default
#define reset() printf("\033[0;0m")

//Sets Font to black, and background to a nice pale purple
#define purp_back() printf("\033[30;48;5;146m")

//Green kind of background
#define bind_col() printf("\033[30;48;5;82m")

// Define a `struct` type called `DEFAULT_CONSOLE` that represents a rectangle on the console screen.
typedef struct DEFAULT_CONSOLE {
	// The x-coordinate of the left edge of the rectangle.
	SHORT Left;

	// The y-coordinate of the top edge of the rectangle.
	SHORT Top;

	// The x-coordinate of the right edge of the rectangle.
	SHORT Right;

	// The y-coordinate of the bottom edge of the rectangle.
	SHORT Bottom;
} DEFAULT_CONSOLE;

/*
 * cursor: Shows or hides the console cursor.
 *
 * show_hide: A flag indicating whether to show (1) or hide (0) the cursor.
 */
void cursor(int show_hide);

bool EnableVTMode();

#endif