#include "../include/system.h"



void cursor(int show_hide)
{
	// Get a handle to the console output.
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Initialize a CONSOLE_CURSOR_INFO struct with the size of the cursor set to 100.
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;

	// Set the visibility of the cursor based on the `show_hide` flag.
	if (show_hide == 1)
	{
		info.bVisible = TRUE;
	}
	else
	{
		info.bVisible = FALSE;
	}

	// Use the `SetConsoleCursorInfo` function to set the cursor properties.
	SetConsoleCursorInfo(console_handle, &info);
}

bool EnableVTMode()
{
	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	// Get console mode, if unable
	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	//Bitwise OR
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	//If unable to set console to VT, return false
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}