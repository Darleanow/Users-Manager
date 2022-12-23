#include "../include/menu.h"

void clear_buffer() {
	char buffer[1024];
	fgets(buffer, 1024, stdin);
}

void trim(char* s)
{
	// Find the first non-whitespace character
	char* start = s;
	while (isspace(*start)) {
		start++;
	}

	// Find the last non-whitespace character
	char* end = s + strlen(s) - 1;
	while (end > start && isspace(*end)) {
		end--;
	}

	// Terminate the string after the last non-whitespace character
	*(end + 1) = '\0';

	// Shift the string so that it begins with the first non-whitespace character
	memmove(s, start, end - start + 2);
}

bool can_be_casted_to_int(const char* str) {
	// Check if the string is empty
	if (str[0] == '\0') {
		return false;
	}

	// Check if the first character is a negative sign
	if (str[0] == '-') {
		// If the string is only a negative sign, it cannot be casted to an int
		if (str[1] == '\0') {
			return false;
		}
		// Otherwise, we start checking from the second character
		str++;
	}

	// Iterate through the string, checking if each character is a digit
	for (int i = 0; str[i] != '\0'; i++) {
		if (!isdigit(str[i])) {
			return false;
		}
	}

	// If we reach this point, the string consists only of digits or a negative sign followed by digits, so it can be casted to an int
	return true;
}

float get_avg(float arr[MAX_GRADES], int amount)
{
	float tot = 0;
	for (int i = 0; i < amount; i++)
	{
		tot += arr[i];
	}
	return tot / amount;
}

float total_avg(Student* stud, List* Modules)
{
	float avgs = 0;
	float coef_div = 0;
	for (int i = 0; i < stud->module_count; i++)
	{
		Module* act_module = malloc(sizeof(Module));
		act_module = list_get(Modules, i);
		Modules_Storage_UserStruct* md = malloc(sizeof(Modules_Storage_UserStruct));
		md = (Modules_Storage_UserStruct*)list_get(stud->Modules, i);
		
		avgs+=get_avg((*md).grades, (*md).grades_amount) * act_module->coef;
		coef_div += act_module->coef;
	}
	return avgs / coef_div;
}

char* char_repeat(int n, char c)
{
	// Allocate memory for the character array. The size of the array is `n+1` to accommodate `n` copies of `c` and the string terminator `'\0'`.
	char* dest = (char*)malloc((size_t)n + 1);

	// If the memory allocation failed, return NULL.
	if (dest == NULL)
		return NULL;

	// Use `memset` to fill the character array with `n` copies of `c`.
	memset(dest, c, n);

	// Set the last element of the character array to the string terminator `'\0'`.
	dest[n] = '\0';

	// Return a pointer to the character array.
	return dest;
}

void display_title(int* num_columns, int* num_rows)
{
	// Print the title text in the center of the screen
	gotoxy(74 / 3, 10); // Move the cursor to the desired position
	printf("  __  __       _       _   _           _             _            _");
	gotoxy(74 / 3, 11);
	printf(" |  \\/  |     | |     | | ( )         | |           | |          | |");
	gotoxy(74 / 3, 12);
	printf(" | \\  / |_   _| | ___ | |_|/ ___   ___| |_ _   _  __| | ___ _ __ | |_ ___");
	gotoxy(74 / 3, 13);
	printf(" | |\\/| | | | | |/ _ \\| __| / __| / __| __| | | |/ _` |/ _ \\ '_ \\| __/ __|");
	gotoxy(74 / 3, 14);
	printf(" | |  | | |_| | | (_) | |_  \\__ \\ \\__ \\ |_| |_| | (_| |  __/ | | | |_\\__ \\");
	gotoxy(74 / 3, 15);
	printf(" |_|  |_|\\__,_|_|\\___/ \\__| |___/ |___/\\__|\\__,_|\\__,_|\\___|_| |_|\\__|___/");
	gotoxy(90, 16); // Move the cursor to the desired position
	printf("Release v1.0"); // Print the release version

	// Print instructions for the user
	gotoxy((*num_columns - 18) / 3, 18); // Move the cursor to the desired position
	printf("Tip: use Arrow Keys to travel and Enter to go in a menu");
	gotoxy((*num_columns - 18) / 3, 20); // Move the cursor to the desired position
	printf("--> press 'ENTER' to begin"); // Prompt the user to press Enter to begin
}

void fake_load(int* columns, int* rows)
{
	display_title(columns, rows);
	getchar();
}

void optionBox(char** array_Values, int* columns, int* rows, int is_selected, int index)
{
	// Calculate the width of each box based on the number of rows available.
	int box_width = (*rows / (sizeof(array_Values) / sizeof(array_Values[0]))) + 10;

	// Calculate the row at which to start drawing the outer box.
	// We use the index provided from the `array_Values` array and the length of the array.
	int draw_start = ((box_width * index) / 10) + 1;

	// Draw the top line of the outer box.
	gotoxy(1, draw_start);
	printf("+");
	for (int i = 0; i < *columns - 2; i++)
	{
		printf("-");
	}
	printf("+");

	// Fill the console screen with spaces and draw the left and right borders of the box.
	for (int actual_line = 1; actual_line < box_width / 10; actual_line++)
	{
		gotoxy(0, draw_start + actual_line);
		printf("|");

		if (is_selected == 1)
			purp_back();

		for (int line_fill = 0; line_fill < *columns - 2; line_fill++)
		{
			printf(" ");
		}

		if (is_selected == 1)
			reset();

		printf("|");
	}

	// Display the label at the center of the box on the x-y axis.
	gotoxy((*columns) / 2 - (int)(strlen(array_Values[index]) / 2), draw_start + 2);

	if (is_selected == 1)
		purp_back();

	printf("%s", array_Values[index]);

	reset();
	gotoxy(0, draw_start + (box_width / 10));
	printf("+");
	for (int i = 0; i < *columns - 2; i++)
	{
		printf("-");
	}
	printf("+");
}

void display_options(char** arr_values, int* selected, int* columns, int* rows, int* array_length)
{
	// Iterate through all the options in the `arr_values` array.
	for (int i = 0; i < *array_length; i++)
	{
		// If the current option is the selected option, highlight it.
		if (i == *selected)
		{
			optionBox(arr_values, columns, rows, 1, i);
		}
		else
		{
			// Otherwise, display the option normally.
			optionBox(arr_values, columns, rows, 0, i);
		}
	}
}

void infoBox(char** key_binds, char** informations, int display_binds_bool, int* columns,
			 int* rows, int index)
{
	// Calculate the width of the left panel, displayed if `display_binds_bool` is 1.
	int key_bind_width = *columns / 6;
	// Calculate the width of the rightmost box.
	int box_width = key_bind_width * 5;
	// Calculate the height of the box in lines.
	int box_height = (*rows / (sizeof(informations) / sizeof(informations[0]))) + 10;
	// Calculate the coordinates of the starting draw point.
	int draw_start = ((box_height * index) / 10) + 1;
	// Initialize strings to hold a certain number of characters.
	char* str1;
	char* str2;

	// If `display_binds_bool` is greater than 0, display the keybinds.
	if (display_binds_bool > 0)
	{
		gotoxy(1, draw_start);
		str1 = char_repeat(key_bind_width, '-');
		str2 = char_repeat(box_width - 3, '-');

		// Top outer line of each box
		printf("+%s+%s+", str1, str2);
		free(str1);
		free(str2);
		for (int i = 1; i < box_height / 10; i++)
		{
			gotoxy(1, draw_start + i);
			str1 = char_repeat(key_bind_width, ' ');
			str2 = char_repeat(box_width - 3, ' ');
			printf("|\033[30;48;5;82m%s\033[0;0m|%s|", str1, str2);
			free(str1);
			free(str2);
			if ((box_height / 10) / 2 == i)
			{
				gotoxy(key_bind_width / 5, draw_start + i);
				printf("\033[30;48;5;82m%s\033[0;0m", key_binds[index]);
				gotoxy(key_bind_width + (box_width / 10), draw_start + i);
				printf("%s", informations[index]);
			}
		}
		gotoxy(1, (box_height / 10) + draw_start);
		str1 = char_repeat(key_bind_width, '-');
		str2 = char_repeat(box_width - 3, '-');
		// Top outer line of each box
		printf("+%s+%s+", str1, str2);
		free(str1);
		free(str2);
	}
}

void display_informations(char** key_binds, char** informations, int display_binds_bool, int* columns,
						  int* rows, int array_length)
{
	// Iterate over the elements in the `key_binds` and `informations` arrays.
	for (int i = 0; i < array_length; i++)
	{
		// Display an information box for each element in the arrays.
		infoBox(key_binds, informations, display_binds_bool, columns, rows, i);
	}
}

char* get_com_code(int communication_code)
{
	return	communication_code == 0 ? "\033[30m\033[48;5;146mINPUT\033[0m---" :
			communication_code == 1 ? "\033[44m\033[1m\033[37mINFO\033[0m---" :
			communication_code == 2 ? "\033[43m\033[1m\033[37mWARNING\033[0m" :
			communication_code == 3 ? "\033[41m\033[1m\033[37mERROR\033[0m--" :
									  "\033[30;48;5;113mSUCCESS\033[0;0m----";
}

void inpt_grades(Student* Stud, int amount, char* mod_name, bool edit, int index)
{
	//String to store inputs
	char* inpt_str;

	//Getting the Modules list
	auto student_modules = Stud->Modules;
	//Allocating memory for the modules (1 unit)
	Modules_Storage_UserStruct* mds = malloc(sizeof(Modules_Storage_UserStruct));

	//Set mod_name and number of grades
	(*mds).module_name = mod_name;
	(*mds).grades_amount = amount;

	for (int grade_it = 0; grade_it < (amount >= 40 ? 39 : amount); grade_it++)
	{
		//For beauty
		selected();
		printf("Grade %d:", grade_it + 1);
		reset();
		printf(" ");
		printf("Enter grade: ");
		scanf("%s", &inpt_str);
		while (string_to_float(&inpt_str) / 100.00 < 0 || string_to_float(&inpt_str) / 100.00 > 20 
			   || strlen(&inpt_str) < 1)
		{
			printf("\nEnter a number (float or not) superior to 0\nChoice: ");
			scanf("%s", &inpt_str);

		}
		clear_buffer();
		//Assigning grade to an array
		(*mds).grades[grade_it] = string_to_float(&inpt_str) / 100.00;
		if (edit)
		{
			Modules_Storage_UserStruct* prev_mod = list_get(Stud->Modules, index);
			prev_mod->grades[grade_it] = (*mds).grades[grade_it];
			prev_mod->grades_amount = amount;
		}
		printf("\n");
	}
	if (!edit)
	{
		//Setting the mds to student modules list
		list_append((*Stud).Modules, mds);
	}
}

void sync_modules(List* Students_Container, List* Modules_Container)
{
	//String to hold format chars
	char* format_str;

	//Get rows and columns so no too much arg
	//Init of struct
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	int rows;

	//to get width and height of the console
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	//If students are created, try to see if modules need a sync
	if (Students_Container->length > 0)
	{
		//Allocating First student which is the oldest created
		Student* stud_get = malloc(sizeof(Student));
		stud_get = (Student*)list_get(Students_Container, 0);
		//Input string to hold users input
		char* inpt_string;

		//If number of users modules is less than total modules created 
		if ((*stud_get).module_count < Modules_Container->length)
		{
			//Get com code error and printing it out
			char* code = get_com_code(3);
			format_str = char_repeat(columns - strlen(code) - 2, '-');
			printf("+%s%s+\n", code, format_str);
			format_str = char_repeat(columns - 2 - 52, ' ');
			printf("| Some students are missing grades for some modules !%s|\n", format_str);
			format_str = char_repeat(columns - 2, '-');
			printf("+%s+\n", format_str);

			//Looping over each Student and see if they need an update
			for (int actual = 0; actual < Students_Container->length; actual++)
			{
				Student* stud_get = malloc(sizeof(Student));
				//Getting the student
				stud_get = (Student*)list_get(Students_Container, actual);
				//Checking if users module count is below the total modules count
				if ((*stud_get).module_count < Modules_Container->length)
				{
					printf("\n");

					selected();
					//Beauty print giving informations of the user
					printf("Student %d named %s needs updates for %d modules:\n", stud_get->ID, stud_get->FirstName,
						   Modules_Container->length - stud_get->module_count);
					reset();

					//Getting modules names
					//Updating each module
					for (int curr_mod = 0; curr_mod < (Modules_Container->length - stud_get->module_count); curr_mod++)
					{
						//Allocating Module
						Module* mods = malloc(sizeof(Module));
						mods = (Module*)list_get(Modules_Container, stud_get->module_count + curr_mod);
						printf("Enter number of grades for module %s: ", (*mods).module_name);
						scanf("%s", &inpt_string);
						clear_buffer();
						//Sanitizing input
						while (atoi(&inpt_string) < 0 && atoi(&inpt_string) > 20 && strlen(&inpt_string))
						{
							printf("\nEnter a number\nChoice: ");
							scanf("%s", &inpt_string);
							clear_buffer();
						}
						//Input grades giving the module name missing
						inpt_grades(stud_get, atoi(&inpt_string), (*mods).module_name, false,-1);
						(*stud_get).module_count++;
					}
				}
			}
		}
	}
}

void create_students(List* Students_Container, List* Modules_Container, int amount)
{
	//Try syncing modules before continuing
	sync_modules(Students_Container, Modules_Container);
	system("cls");

	//Get rows and columns so no too much arg
	//Init of struct
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	int rows;

	//to get width and height of the console
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	int line_follow = 1;
	gotoxy(0, line_follow);

	char* string_code = get_com_code(1);
	char* str_repeat = char_repeat((columns - 2 - (strlen(string_code)) + 18), '-');
	printf("+%s%s+", string_code, str_repeat);

	line_follow++; gotoxy(0, line_follow);
	str_repeat = char_repeat((columns - 25), ' ');
	printf("|Now creating the students%s|", str_repeat);

	line_follow++; gotoxy(0, line_follow);
	str_repeat = char_repeat(columns - 2, '-');
	printf("+%s+", str_repeat);
	//Input string
	char* user_input;
	//Loop for each user that needs to be created
	for (int actual_item = 0; actual_item < amount; actual_item++)
	{
		//Allocating Student
		Student* stud = malloc(sizeof(Student));
		//Allocating size for the Linked list of Stud modules
		(*stud).Modules = list_create();
		printf("\n\n");
		selected();
		printf("Student %d:\033[0;0m\n", actual_item + 1);
		reset();

		printf("Enter Student's ID: ");
		scanf("%s", &user_input);
		clear_buffer();
		while (sanitize_number_input(&user_input) <= 0 || strlen(&user_input) == 0 || atoi(&user_input) >= INT_MAX ||
			   is_valid_id(Students_Container, atoi(&user_input)))
		{
			printf("\nEnter a unique number superior to 0 and inferior to %d\nChoice: ",INT_MAX);
			scanf("%s", &user_input);
			clear_buffer();

		}
		(*stud).ID = atoi(&user_input);

		printf("Enter Student's firstname: ");
		no_bug_inpt(&user_input);
		while (strlen(user_input) < 3 || strlen(user_input) > 15)
		{
			printf("Enter a 3-15 chars firstname: ");
			no_bug_inpt(&user_input);
		}
		(*stud).FirstName = user_input;
		printf("Enter Student's name: ");
		no_bug_inpt(&user_input);
		while (strlen(user_input) < 3 || strlen(user_input) > 15)
		{
			printf("Enter a 3-15 chars name: ");
			no_bug_inpt(&user_input);
		}
		(*stud).Name = user_input;
		printf("Enter Student's age: ");
		scanf("%s", &user_input);
		clear_buffer();
		while (sanitize_number_input(&user_input) <= 0 || strlen(&user_input) == 0 || atoi(&user_input) > 150)
		{
			printf("\nEnter a number superior to 0 and inferior to 150\nChoice: ");
			scanf("%s", &user_input);
			clear_buffer();

		}
		(*stud).Age = atoi(&user_input);
		printf("Enter Student's nationality: ");
		no_bug_inpt(&user_input);
		while (strlen(user_input) < 2 || strlen(user_input) > 15)
		{
			printf("Enter a 2-15 chars nationality: ");
			no_bug_inpt(&user_input);
		}
		(*stud).Nationality = user_input;

		char* inpt_str;

		//Looping over the Modules_Container elem
		for (int curr_md = 0; curr_md < Modules_Container->length; curr_md++)
		{
			//Allocating sizeof module for each module
			Module* md = malloc(sizeof(Module));
			//Getting module
			md = (Module*)list_get(Modules_Container, curr_md);
			printf("How many grades for module %s: ", (*md).module_name);
			no_bug_inpt(&inpt_str);
			while (strlen(inpt_str) < 1 || atoi(inpt_str) < 1 || atoi(inpt_str) > 40)
			{
				printf("Enter a number between 1-39: ", (*md).module_name);
				no_bug_inpt(&inpt_str);
			}
			//input grades
			inpt_grades(stud, atoi(inpt_str), (*md).module_name, false,-1);
			
		}
		//Manually update module_count so we can keep track on how many modules user has
		(*stud).module_count = Modules_Container->length;
		//Adding the user to the student_container list
		list_append(Students_Container, stud);
		//Getting it for debug purpose and beauty
		Student* stud_get = list_get(Students_Container, Students_Container->length - 1);
		//Print Success message
		printf("+%s%s+\n", get_com_code(4), char_repeat(columns - 13, '-'));
		printf("|Successfully created Student named %s %s !%s|\n", stud_get->FirstName, stud_get->Name,
			   char_repeat(columns-2-36-2-strlen(stud_get->FirstName) - strlen(stud_get->Name),' '));
		printf("+%s+\n", char_repeat(columns - 2, '-'));
	}
	//Free string
	free(user_input);
	printf("Press enter to continue. . .");
	getchar();
}

void create_modules(List* Modules_Container, int amount)
{
	//Get rows and columns so no too much arg
	//Init of struct
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	int rows;

	//to get width and height of the console
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	//User input string
	char* user_input;
	
	for (int actual_item = 0; actual_item < amount; actual_item++)
	{
		//Looping for each module and allocating Memory
		Module* mod = malloc(sizeof(Module));
		//Beauty print
		printf("\n\n");
		selected();
		printf("Module %d:\033[0;0m", actual_item + 1);
		reset();
		printf("\nEnter module's name: ");
		no_bug_inpt(&user_input);
		trim(user_input);
		while (strlen(user_input) < 3 || strlen(user_input) > 15 || is_nonvalid_modName(Modules_Container, user_input))
		{
			printf("Enter a unique 3-15 chars name: ");
			no_bug_inpt(&user_input);
			trim(user_input);
		}
		
		(*mod).module_name = user_input;

		printf("Enter module's coefficient (float or not): ");
		scanf("%s", &user_input);
		while (string_to_float(&user_input) <= 0 || atof(&user_input) <= 0)
		{
			printf("\nEnter a number (float or not) superior to 0\nChoice: ");
			scanf("%s", &user_input);

		}
		clear_buffer();
		(*mod).coef = string_to_float(&user_input) / 100.00;
		//Adding Module to the module_container list
		list_append(Modules_Container, mod);
		//Printing it out for beauty
		Module* mod_get = list_get(Modules_Container, Modules_Container->length - 1);
		printf("\n");
		printf("+%s%s+\n", get_com_code(4), char_repeat(columns - 13, '-'));
		printf("|Successfully created Module %s with coef of %.2f !%s|\n", mod_get->module_name, mod_get->coef,
			   char_repeat(columns - 2 - 29 - 16 - strlen(mod_get->module_name) - 
			   ((short)log10((int)mod_get->coef) > 1 ? 3 : 3), ' '));
		printf("+%s+\n", char_repeat(columns - 2, '-'));
	}

	printf("Press enter to continue. . .");
	getchar();
	system("cls");
}

void input_menu(int* communication_code, char* instructions, int* columns, int* rows, int* selected_index,
				List* Students_Container, List* Modules_Container)
{
	//turning on cursor, getting string code, and setting input type based on the selcted index
	cursor(1);
	char* string_code = get_com_code(communication_code);
	char* input_type = *selected_index == 0 ? "student" : "module";

	//Setting base line to 1 
	int line_follow = 1;

	//Check if needed to create modules
	bool need_module = *selected_index == 0 ? false : true;

	//Format and input strings
	char* str_repeat;
	char* user_input;
	char* user_input_2;

	//Goto topright
	gotoxy(0, line_follow);
	str_repeat = char_repeat((*columns - 2 - (strlen(string_code)) + 20), '-');
	printf("+%s%s+", string_code, str_repeat);

	line_follow++; gotoxy(0, line_follow);
	str_repeat = char_repeat((*columns - 38 - strlen(input_type)), ' ');
	printf("|How many %s(s) do you want to create ?%s|", input_type, str_repeat);

	line_follow++; gotoxy(0, line_follow);
	str_repeat = char_repeat(*columns - 2, '-');
	printf("+%s+", str_repeat);

	line_follow++; gotoxy(0, line_follow);
	printf("Choice: ");
	scanf("%s", &user_input);

	while (!(sanitize_number_input(&user_input)) || atoi(&user_input) <= 0 || strlen(&user_input) == 0)
	{
		line_follow++;
		gotoxy(0, line_follow);
		printf("Enter a valid number (1 to %d)", INT_MAX);
		line_follow++;
		gotoxy(0, line_follow);
		printf("Choice: ");
		scanf("%s", &user_input); line_follow++;
	}

	//Checking if User tries to create a student before creating modules
	if (Modules_Container->length == 0 && *selected_index == 0)
	{
		need_module = true;
		line_follow += 2; gotoxy(0, line_follow);

		string_code = get_com_code(3);
		str_repeat = char_repeat(*columns - 2 - (strlen(string_code)) + 18, '-');
		printf("+%s%s+", string_code, str_repeat);

		line_follow++; gotoxy(0, line_follow);
		str_repeat = char_repeat(*columns - 52, ' ');
		printf("|You need at least one module to create a Student !%s|", str_repeat);

		line_follow++; gotoxy(0, line_follow);
		str_repeat = char_repeat(*columns - 44, ' ');
		printf("|Getting redirected to the modules creation%s|", str_repeat);

		line_follow++; gotoxy(0, line_follow);
		str_repeat = char_repeat(*columns - 2, '-');
		printf("+%s+", str_repeat);

		line_follow += 2; gotoxy(0, line_follow);
		string_code = get_com_code(0);
		str_repeat = char_repeat(*columns - (strlen(string_code)) + 18, '-');
		printf("+%s%s+", string_code, str_repeat);

		line_follow++; gotoxy(0, line_follow);
		str_repeat = char_repeat((*columns - 37 - strlen(input_type)), ' ');
		printf("|How many module(s) do you want to create ?%s|", str_repeat);

		line_follow++; gotoxy(0, line_follow);
		str_repeat = char_repeat(*columns - 2, '-');
		printf("+%s+", str_repeat);

		line_follow++; gotoxy(0, line_follow);
		printf("Choice: ");
		scanf("%s", &user_input_2);
		while (!(sanitize_number_input(&user_input_2)) || atoi(&user_input_2) <= 0 || strlen(&user_input_2) == 0)
		{
			line_follow++;
			gotoxy(0, line_follow);
			printf("Enter a valid number (1 to %d)",INT_MAX);
			line_follow++;
			gotoxy(0, line_follow);
			printf("Choice: ");
			scanf("%s", &user_input_2); line_follow++;
		}
	}
	clear_buffer();

	//Handle Modules creating and directing the users creating
	if (need_module == true && *selected_index == 0)
	{
		create_modules(Modules_Container, atoi(&user_input_2));

		line_follow = 1;
		gotoxy(0, line_follow);

		string_code = get_com_code(1);
		str_repeat = char_repeat((*columns - 2 - (strlen(string_code)) + 18), '-');
		printf("+%s%s+", string_code, str_repeat);

		line_follow++; gotoxy(0, line_follow);
		str_repeat = char_repeat((*columns - 25), ' ');
		printf("|Now creating the students%s|", str_repeat);

		line_follow++; gotoxy(0, line_follow);
		str_repeat = char_repeat(*columns - 2, '-');
		printf("+%s+\n", str_repeat);

		create_students(Students_Container, Modules_Container, atoi(&user_input));

	}
	//If modules was entered at first
	else if (need_module == true)
	{
		create_modules(Modules_Container, atoi(&user_input));
	}
	//Otherwise everything is ok, create the students
	else
	{
		create_students(Students_Container, Modules_Container, atoi(&user_input));
	}
}

int display_students(List* students_linkedlist, int* columns, int* rows, List* modules_linkedlist)
{
	if (students_linkedlist->length == 0)
	{
		char* string_code = get_com_code(3);
		char* str_repeat = char_repeat(*columns - 2 - (strlen(string_code)) + 18, '-');
		printf("+%s%s+\n", string_code, str_repeat);

		str_repeat = char_repeat(*columns - 51, ' ');
		printf("|You need at least one module to display modules !%s|\n", str_repeat);
		str_repeat = char_repeat(*columns - 2, '-');
		printf("+%s+\n", str_repeat);
		printf("\nPress enter to continue. . .");
		getchar();
		return 0;
	}
	//Syncing here too so no bugs
	sync_modules(students_linkedlist, modules_linkedlist);
	system("cls");
	//Allocating memory to hold a student
	Student* stud_get = malloc(sizeof(Student));
	//for formatting
	char* str_form;
	for (int i = 0; i < students_linkedlist->length; i++)
	{
		//getting student
		stud_get = (Student*)list_get(students_linkedlist, i);
		str_form = char_repeat(50, '-');
		printf("+-\033[45m\033[1m\033[37mSTUDENT\033[0;0m%s+\n", str_form);
		str_form = char_repeat(58 - 15 - (int)log10(stud_get->ID), ' ');
		printf("| Students ID: %d%s|\n", stud_get->ID, str_form);

		str_form = char_repeat(58 - 21 - strlen(stud_get->FirstName), ' ');
		printf("| Students Firstname: %s%s|\n", stud_get->FirstName, str_form);

		str_form = char_repeat(58 - 16 - strlen(stud_get->Name), ' ');
		printf("| Students Name: %s%s|\n", stud_get->Name, str_form);

		str_form = char_repeat(58 - 16 - (short)log10(stud_get->Age), ' ');
		printf("| Students Age: %d%s|\n", stud_get->Age, str_form);

		str_form = char_repeat(58 - 23 - strlen(stud_get->Nationality), ' ');
		printf("| Students Nationality: %s%s|\n", stud_get->Nationality, str_form);

		//log10 of a number gives out its length :)
		//Printing every module
		str_form = char_repeat(58 - 24 - (short)log10(stud_get->module_count), ' ');
		printf("| Total modules number: %d%s|\n", stud_get->module_count, str_form);
		
		for (int act_module = 0; act_module < stud_get->module_count; act_module++)
		{
			Modules_Storage_UserStruct* md = malloc(sizeof(Modules_Storage_UserStruct));
			md = (Modules_Storage_UserStruct*)list_get(stud_get->Modules, act_module);
			char* format = (*md).grades_amount > 1 ? "grades" : "grade";
			str_form = char_repeat(53 - 8 - strlen(format) - strlen((*md).module_name) - (short)log10((*md).grades_amount), ' ');
			printf("| Module %s: %d %s %s|\n", (*md).module_name, (*md).grades_amount, format, str_form);
		}
		str_form = char_repeat(58, '-');
		printf("+%s+\n", str_form);
		for (int act_module = 0; act_module < stud_get->module_count; act_module++)
		{
			Modules_Storage_UserStruct* md = malloc(sizeof(Modules_Storage_UserStruct));
			md = (Modules_Storage_UserStruct*)list_get(stud_get->Modules, act_module);
			
			float avg = get_avg((*md).grades, (*md).grades_amount);
			int spaces_from_avg = avg < 10 ? 3 : 4;
			str_form = char_repeat(58 - 21 - 4 - spaces_from_avg - strlen((*md).module_name), ' ');
			printf("| Average on module %s: %.2f/20%s|\n", (*md).module_name, avg, str_form);
		}
		str_form = char_repeat(58, '-');
		printf("+%s+\n", str_form);
		str_form = char_repeat(58 - 27 - 8, ' ');
		printf("| Total average on modules: %.2f/20%s|\n", total_avg(stud_get, modules_linkedlist), str_form);
		str_form = char_repeat(58, '-');
		printf("+%s+\n", str_form);
	}
}

int display_modules(List* modules, int* columns, int* rows)
{
	if (modules->length == 0)
	{
		char* string_code = get_com_code(3);
		char* str_repeat = char_repeat(*columns - 2 - (strlen(string_code)) + 18, '-');
		printf("+%s%s+\n", string_code, str_repeat);

		str_repeat = char_repeat(*columns - 51, ' ');
		printf("|You need at least one module to display modules !%s|\n", str_repeat);
		str_repeat = char_repeat(*columns - 2, '-');
		printf("+%s+\n", str_repeat);
		printf("\nPress enter to continue. . .");
		getchar();
		return 0;
	}
	Module* md = malloc(sizeof(Module));

	for (int i = 0; i < modules->length; i++)
	{
		md = (Module*) list_get(modules, i);
		printf("+-\033[45m\033[1m\033[37mMODULE 0%d\033[0;0m%s+\n", i+1,char_repeat(49, '-'));
		printf("| Module Name: %s %s|\n", md->module_name, char_repeat(58 - 14 - strlen(md->module_name), ' '));
		printf("| Module Coef: %.2f%s|\n", md->coef, char_repeat(58 - 17, ' '));
		printf("+%s+\n", char_repeat(59, '-'));
	}
}

bool is_valid_id(List* student_linkedlist, int id)
{
	for (int i = 0; i < student_linkedlist->length; i++)
	{
		Student* stud = (Student*)list_get(student_linkedlist, i);
		if (id == stud->ID)
		{
			return true;
		}
	}
	return false;
}

bool is_nonvalid_modName(List* module_linkedlist, char* mod_name)
{
	for (int i = 0; i < module_linkedlist->length; i++)
	{
		Module* mod = (Module*)list_get(module_linkedlist, i);
		if (strcmp(&mod_name,mod->module_name) == 0)
		{
			return true;
		}
	}
	return false;
}

int get_idx_by_id(List* student_list, int id)
{
	for (int i = 0; i < student_list->length; i++)
	{
		Student* stud = (Student*)list_get(student_list, i);
		if (stud->ID == id)
		{
			return i;
		}
	}
	return -1;
}

int get_idx_by_name(List* module_list, char* name)
{
	for (int i = 0; i < module_list->length; i++)
	{
		Module* mod = (Module*)list_get(module_list, i);
		if (strcmp(mod->module_name,name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void display_rewrite_grades(Student* stud,List* Modules)
{
	char usr_inpt[100];
	for (int i = 0; i < stud->module_count; i++)
	{
		Modules_Storage_UserStruct* md = malloc(sizeof(Modules_Storage_UserStruct));
		md = (Modules_Storage_UserStruct*)list_get(stud->Modules, i);
		printf("+-\033[45m\033[1m\033[37mMODULES\033[0;0m%s+\n", char_repeat(50, '-'));
		printf("| Module ID: %d%s|\n", i+1,char_repeat(58- 13 - (short)log10(i),' '));
		float avg = get_avg(md->grades, md->grades_amount);
		printf("| %s : %.2f/20 avg%s|\n", md->module_name, avg, char_repeat(58 - strlen(md->module_name)
			   - 16,' '));
		printf("+%s+\n", char_repeat(58, '-'));

	}
	printf("Enter the module id you want to rewrite\n");
	printf("NOTE: All grades from this module will be erased.\nChoice: ");
	scanf("%s", usr_inpt);
	clear_buffer();
	while (atoi(&usr_inpt) <= 0 || atoi(&usr_inpt) > stud->module_count || strlen(&usr_inpt) == 0)
	{
		printf("\nEnter a valid id\nChoice: ");
		scanf("%s", usr_inpt);
		clear_buffer();
	}
	char amount[100];
	printf("Enter now how many grades you want to enter\nChoice: ");
	scanf("%s", amount);
	clear_buffer();
	while (atoi(&amount) <= 0 || atoi(&amount) >= 40)
	{
		printf("\nEnter a valid amount (1-39)\nChoice: ");
		scanf("%s", amount);
		clear_buffer();
	}

	Modules_Storage_UserStruct* md = malloc(sizeof(Modules_Storage_UserStruct));
	md = (Modules_Storage_UserStruct*)list_get(stud->Modules, atoi(&usr_inpt)-1);
	inpt_grades(stud, atoi(&amount), md->module_name,true, atoi(&usr_inpt) - 1);

	system("cls");
}

int del_edit_Student(List* students_linkedlist, int* columns, int* rows, List* modules_linkedlist)
{
	if (students_linkedlist->length == 0)
	{
		char* string_code = get_com_code(3);
		char* str_repeat = char_repeat(*columns - 2 - (strlen(string_code)) + 18, '-');
		printf("+%s%s+\n", string_code, str_repeat);

		str_repeat = char_repeat(*columns - 53, ' ');
		printf("|You need at least one student to display Students !%s|", str_repeat);
		str_repeat = char_repeat(*columns - 2 , '-');
		printf("+%s+\n",str_repeat);
		printf("\nPress enter to continue. . .");
		getchar();
		return 0;
	}
	cursor(1);
	char* user_inpt;
	char scd_usr_inpt[100];

	bool is_valid_choice = false;

	display_students(students_linkedlist, columns, rows, modules_linkedlist);

	printf("\nEnter the id of the student you want to take actions to or 'cancel' to cancel: ");
	scanf("%s", &user_inpt);
	clear_buffer();
	if (strcmp(&user_inpt, "cancel") != 0)
	{
		while (!(is_valid_id(students_linkedlist, atoi(&user_inpt))))
		{
			printf("\nEnter a valid id.\nChoice: ");
			scanf("%s", &user_inpt);
			clear_buffer();
		}
	}
	else
	{
		return 0;
	}

	printf("Enter 'cancel' to cancel, 'yes' to delete the student with the ID of %d, or 'mod' to change its values:\nChoice: ", atoi(&user_inpt));

	scanf("%s", scd_usr_inpt);
	clear_buffer();
	while (strcmp(scd_usr_inpt, "cancel") != 0 && strcmp(scd_usr_inpt, "yes") != 0 && strcmp(scd_usr_inpt, "mod"))
	{
		printf("Invalid choice, try again.\nChoice: ");
		scanf("%s", scd_usr_inpt);
		clear_buffer();
	}

	if (strcmp(scd_usr_inpt, "yes") == 0)
	{
		int idx = 0;
		idx = get_idx_by_id(students_linkedlist, atoi(&user_inpt));
		list_remove(students_linkedlist, idx);

		char* string_code = get_com_code(2);
		char* str_repeat = char_repeat(*columns - 2 - (strlen(string_code)) + 18, '-');
		printf("\n+%s%s+\n", string_code, str_repeat);

		str_repeat = char_repeat(*columns - 52, ' ');
		printf("|Success deleting student %d!%s|\n", atoi(&user_inpt), str_repeat);
		str_repeat = char_repeat(*columns - 2, '-');
		printf("+%s+\n", str_repeat);
		printf("Press 'enter' to continue. . .");
		getchar();
		system("cls");
	}
	else if (strcmp(scd_usr_inpt, "mod") == 0)
	{
		system("cls");
		int idx = 0;
		idx = get_idx_by_id(students_linkedlist, atoi(&user_inpt));
		char* str_form;
		Student* stud_get = malloc(sizeof(Student));

		stud_get = (Student*)list_get(students_linkedlist, idx);
		str_form = char_repeat(50, '-');
		printf("+-\033[45m\033[1m\033[37mSTUDENT\033[0;0m%s+\n", str_form);
		str_form = char_repeat(55 - 15 - (int)log10(stud_get->ID), ' ');
		printf("| 01 Students ID: %d%s|\n", stud_get->ID, str_form);

		str_form = char_repeat(55 - 21 - strlen(stud_get->FirstName), ' ');
		printf("| 02 Students Firstname: %s%s|\n", stud_get->FirstName, str_form);

		str_form = char_repeat(55 - 16 - strlen(stud_get->Name), ' ');
		printf("| 03 Students Name: %s%s|\n", stud_get->Name, str_form);

		str_form = char_repeat(55 - 16 - (short)log10(stud_get->Age), ' ');
		printf("| 04 Students Age: %d%s|\n", stud_get->Age, str_form);

		str_form = char_repeat(55 - 23 - strlen(stud_get->Nationality), ' ');
		printf("| 05 Students Nationality: %s%s|\n", stud_get->Nationality, str_form);


		str_form = char_repeat(58 - 15 - (short)log10(stud_get->module_count), ' ');
		printf("| 06 Modules (%d)%s|\n", stud_get->module_count, str_form);
		str_form = char_repeat(58, '-');
		printf("+%s+\n", str_form);

		char* thrd_str_inpt;
		printf("Enter the number next to the field name to change it: ");
		scanf("%s", &thrd_str_inpt);
		while (atoi(&thrd_str_inpt) < 1 || atoi(&thrd_str_inpt) > 6)
		{
			printf("\nEnter a correct number: ");
			scanf("%s", &thrd_str_inpt);
		}
		char* lst_str;
		switch (atoi(&thrd_str_inpt))
		{
			case 1:
				printf("Enter Student's ID: ");
				scanf("%s", &lst_str);
				clear_buffer();
				while (sanitize_number_input(&lst_str) <= 0 || strlen(&lst_str) == 0 || atoi(&lst_str) >= INT_MAX ||
					   is_valid_id(students_linkedlist, atoi(&lst_str)))
				{
					printf("\nEnter a unique number superior to 0 and inferior to %d\nChoice: ", INT_MAX);
					scanf("%s", &lst_str);
					clear_buffer();

				}
				(*stud_get).ID = atoi(&lst_str);
				break;
				
			case 2:
				printf("Enter Student's firstname: ");
				no_bug_inpt(&lst_str);
				while (strlen(lst_str) < 3 || strlen(lst_str) > 15)
				{
					printf("Enter a 3-15 chars firstname: ");
					no_bug_inpt(&lst_str);
				}
				(*stud_get).FirstName = lst_str;
				break;
			case 3:
				printf("Enter Student's name: ");
				no_bug_inpt(&lst_str);
				while (strlen(lst_str) < 3 || strlen(lst_str) > 15)
				{
					printf("Enter a 3-15 chars name: ");
					no_bug_inpt(&lst_str);
				}
				(*stud_get).Name = lst_str;
				break;
			case 4:
				printf("Enter Student's age: ");
				scanf("%s", &lst_str);
				clear_buffer();
				while (sanitize_number_input(&lst_str) <= 0 || strlen(&lst_str) == 0 || atoi(&lst_str) > 150)
				{
					printf("\nEnter a number superior to 0 and inferior to 150\nChoice: ");
					scanf("%s", &lst_str);
					clear_buffer();

				}
				(*stud_get).Age = atoi(&lst_str);
				break;
			case 5:
				printf("Enter Student's nationality: ");
				no_bug_inpt(&lst_str);
				while (strlen(lst_str) < 2 || strlen(lst_str) > 15)
				{
					printf("Enter a 2-15 chars nationality: ");
					no_bug_inpt(&lst_str);
				}
				(*stud_get).Nationality = lst_str;
				break;
			case 6:
				display_rewrite_grades(stud_get, modules_linkedlist);
			default:
				break;
		}
	}
	else
	{
		system("cls");
	}
	del_edit_Student(students_linkedlist, columns, rows, modules_linkedlist);
	return 0;
}

int del_edit_Module(List* modules_linkedlist,int* columns, int* rows, List* students_linkedlist)
{
	
	if (modules_linkedlist->length == 0)
	{
		char* string_code = get_com_code(3);
		char* str_repeat = char_repeat(*columns - 2 - (strlen(string_code)) + 18, '-');
		printf("+%s%s+\n", string_code, str_repeat);

		str_repeat = char_repeat(*columns - 51, ' ');
		printf("|You need at least one module to display modules !%s|\n", str_repeat);
		str_repeat = char_repeat(*columns - 2, '-');
		printf("+%s+\n", str_repeat);
		printf("\nPress enter to continue. . .");
		getchar();
		return 0;
	}
	char *user_inpt;
	display_modules(modules_linkedlist, columns, rows);
	cursor(1);
	
	printf("Enter module nr to modify/delete it\nChoice: ");
	scanf("%s", &user_inpt);
	clear_buffer();
	while (!can_be_casted_to_int(&user_inpt))
	{
		printf("Enter module nr to modify/delete it\nChoice: ");
		scanf("%s", &user_inpt);
		clear_buffer();
	}

	system("cls");
	Module* md_get = malloc(sizeof(Module));
	md_get = (Module*)list_get(modules_linkedlist, atoi(&user_inpt) - 1);
	printf("+-\033[45m\033[1m\033[37mMODULE\033[0;0m%s+\n", char_repeat(58-7, '-'));
	printf("| 01 Module name: %s%s|\n", md_get->module_name, char_repeat(60 - 17 - 2 - strlen(md_get->module_name), ' '));
	printf("| 02 Module coef: %.2f%s|\n", md_get->coef, char_repeat(60 - 21 - 2, ' '));
	printf("+%s+\n", char_repeat(60 - 2, '-'));
	printf("\nEnter a number next to a value to change it, 'cancel' to cancel, 'del' to delete the module\nChoice: ");
	char* scd_inpt_str;
	scanf("%s", &scd_inpt_str);
	clear_buffer();
	while (strcmp(&scd_inpt_str, "del") != 0 && strcmp(&scd_inpt_str, "cancel") != 0 && atoi(&scd_inpt_str) != 1
		   && atoi(&scd_inpt_str) != 2)
	{
		printf("\nEnter a number next to a value to change it, 'cancel' to cancel, 'del' to delete the module\nChoice: ");
		scanf("%s", &scd_inpt_str);
		clear_buffer();
	}
	if (strcmp(&scd_inpt_str, "cancel") == 0)
	{
		return 0;
	}
	else if (strcmp(&scd_inpt_str, "del") == 0)
	{
		char* md_name = md_get->module_name;
		if (students_linkedlist->length > 0)
		{
			for (int i = 0; i < students_linkedlist->length; i++)
			{
				Student* stud = (Student*) list_get(students_linkedlist, i);
				for (int j = 0; j < stud->Modules->length; j++)
				{
					Modules_Storage_UserStruct* std_md = (Modules_Storage_UserStruct*)list_get(stud->Modules,j);
					if (strcmp(std_md->module_name, md_name) == 0)
					{
						list_remove(stud->Modules, j);
						(*stud).module_count -= 1;
					}
				}
			}
		}
		list_remove(modules_linkedlist, atoi(&user_inpt) - 1);
		printf("+%s%s+\n", get_com_code(4), char_repeat(*columns - 13, '-'));
		printf("|Successfully deleted Module%s|\n",char_repeat(*columns - 2 - 27, ' '));
		printf("+%s+\n", char_repeat(*columns - 2, '-'));
		printf("Press enter to continue. . .");
		getchar();
	}
	else if (atoi(&scd_inpt_str) == 1)
	{
		char* thrd_inpt;
		char* md_name = md_get->module_name;
		printf("Enter new module name: ");
		no_bug_inpt(&thrd_inpt);
		trim(thrd_inpt);
		while (strlen(thrd_inpt) < 3 || strlen(thrd_inpt) > 15 || is_nonvalid_modName(modules_linkedlist, thrd_inpt))
		{
			printf("Enter a unique 3-15 chars name: ");
			no_bug_inpt(&thrd_inpt);
			trim(thrd_inpt);
		}
		(*md_get).module_name = thrd_inpt;

		if (students_linkedlist->length > 0)
		{
			for (int i = 0; i < students_linkedlist->length; i++)
			{
				Student* stud = (Student*)list_get(students_linkedlist, i);
				for (int j = 0; j < stud->Modules->length; j++)
				{
					Modules_Storage_UserStruct* std_md = (Modules_Storage_UserStruct*)list_get(stud->Modules, j);
					if (strcmp(std_md->module_name, md_name) == 0)
					{
						(*std_md).module_name = thrd_inpt;
					}
				}
			}
		}
		printf("+%s%s+\n", get_com_code(4), char_repeat(*columns - 13, '-'));
		printf("|Successfully updated Module%s|\n", char_repeat(*columns - 2 - 27, ' '));
		printf("+%s+\n", char_repeat(*columns - 2, '-'));
		printf("Press enter to continue. . .");
		getchar();
	}
	else if (atoi(&scd_inpt_str) == 2)
	{
		char* thrd_inpt;
		printf("Enter module's coefficient (float or not): ");
		scanf("%s", &thrd_inpt);
		while (string_to_float(&thrd_inpt) <= 0 || atof(&thrd_inpt) <= 0)
		{
			printf("\nEnter a number (float or not) superior to 0\nChoice: ");
			scanf("%s", &thrd_inpt);

		}
		clear_buffer();
		(*md_get).coef = string_to_float(&thrd_inpt) / 100.00;
		printf("+%s%s+\n", get_com_code(4), char_repeat(*columns - 13, '-'));
		printf("|Successfully deleted Module%s|\n", char_repeat(*columns - 2 - 27, ' '));
		printf("+%s+\n", char_repeat(*columns - 2, '-'));
		printf("Press enter to continue. . .");
		getchar();
	}

}