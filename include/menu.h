#pragma once
#ifndef MENU_HEAD
#define MENU_HEAD

#ifndef SYSTEM_FOLL
#include "../include/system.h"
#endif
#ifndef MODULES_FOLL
#include "../include/modules.h"
#endif
#ifndef STUDENTS_STRCT
#include "../include/students.h"
#endif

#define MAX_INPUT_LENGTH 100
/*
 * clear_buffer: Clears the input buffer.
 */
void clear_buffer();

void trim(char* s);

bool can_be_casted_to_int(const char* str);

float get_avg(float arr[MAX_GRADES], int amount);

/*
 * char_repeat: Allocates memory for a character array, fills it with `n` copies of the character `c`,
 * and returns a pointer to the character array.
 *
 * n: The number of times the character `c` should be repeated.
 * c: The character to be repeated.
 *
 * Returns: A pointer to the character array on success, or NULL if the memory allocation failed.
 */
char* char_repeat(int n, char c);

float total_avg(Student* stud, List* Modules);
/*
 * Display the title and some instructions to the user
 *
 * num_columns: Pointer to the number of columns in the terminal window
 * num_rows: Pointer to the number of rows in the terminal window
 */
void display_title(int* num_columns, int* num_rows);

/*
 * fake_load: Displays the main screen
 * 
 * columns: The width of the console screen, in columns.
 * rows: The height of the console screen, in rows.
 */
void fake_load(int* columns, int* rows);

/*
 * optionBox: Draws a box with a label on the console screen.
 *
 * array_Values: An array of strings containing the labels for the boxes.
 * columns: The width of the console screen, in columns.
 * rows: The height of the console screen, in rows.
 * is_selected: A flag indicating whether the box should be highlighted (1) or not (0).
 * index: The index of the label in the `array_Values` array to display in the box.
 */
void optionBox(char** array_Values, int* columns, int* rows, int is_selected, int index);

/*
 * display_options: Displays a set of options as boxes on the console screen.
 *
 * arr_values: An array of strings containing the labels for the options.
 * selected: The index of the currently selected option in the `arr_values` array.
 * columns: The width of the console screen, in columns.
 * rows: The height of the console screen, in rows.
 * array_length: The number of elements in the `arr_values` array.
 */
void display_options(char** arr_values, int* selected, int* columns, int* rows, int* array_length);

/*
 * infoBox: Displays a box containing information on the console screen.
 *
 * key_binds: An array of strings containing the keybinds for the options.
 * informations: An array of strings containing the corresponding information for the options.
 * display_binds_bool: A flag indicating whether the keybinds should be displayed (1) or not (0).
 * columns: The width of the console screen, in columns.
 * rows: The height of the console screen, in rows.
 * index: The index of the label in the `informations` array to display in the box.
 */
void infoBox(char** key_binds, char** informations, int display_binds_bool, int* columns,
			 int* rows, int index);

/*
 * display_informations: Displays information boxes on the console screen.
 *
 * key_binds: An array of strings containing the keybinds for the options.
 * informations: An array of strings containing the corresponding information for the options.
 * display_binds_bool: A flag indicating whether the keybinds should be displayed (1) or not (0).
 * columns: The width of the console screen, in columns.
 * rows: The height of the console screen, in rows.
 * array_length: The number of elements in the `key_binds` and `informations` arrays.
 */
void display_informations(char** key_binds, char** informations, int display_binds_bool, int* columns,
						  int* rows, int array_length);

/*
 * get_com_code: Returns a com message.
 *
 * communication_code: corresponds to the following message
 */
char* get_com_code(int communication_code);

/*
 * inpt_grades: Input of students grades.
 *
 * Stud: corresponds to the student
 * amount: how many times it loops
 * mod_name: module name 
 */
void inpt_grades(Student* Stud, int amount, char* mod_name, bool edit, int index);

/*
 * sync_modules: Sync the new modules to the student to avoid bugs.
 *
 * Students_Container: Linked list containing students
 * Modules_Container: Linked list containing modules
 */
void sync_modules(List* Students_Container, List* Modules_Container);

/*
 * create_student: Function to create Students.
 *
 * Students_Container: Holds Students
 * Moldules_Container: Holds Modules
 * amount: Number of Students that needs to be created
 */
void create_students(List* Students_Container, List* Modules_Container, int amount);

/*
 * create_modules: Function to create modules.
 *
 * Modules_Container: Holds modules
 * amount: Number of modules that needs to be created
 */
void create_modules(List* Modules_Container, int amount);

/*
 * input_menu: Function to handle input related menus.
 *
 * communication_code: Holds modules
 * instructions: Number of modules that needs to be created
 * columns: Columns of the console
 * rows: Rows of the console
 * selected_index: Selected index (So can check to avoid bugs)
 * Student_Container: Linked list of Students
 * Modules_Container: Linked list of Modules
 */
void input_menu(int* communication_code, char* instructions, int* columns, int* rows, int* selected_index,
				List* Students_Container, List* Modules_Container);

/*
 * display_students: Function to display created users.
 *
 * students_linkedlist: Linked list of students
 * columns: columns of the console
 * rows: rows of the console
 */
int display_students(List* students_linkedlist, int* columns, int* rows, List* modules_linkedlist);

/*
 * display_modules: Function to display created modules.
 *
 * modules: linked list of the modules containing module_name and coef
 */
int display_modules(List* modules, int* columns, int* rows);
/*
 * is_valid_id: Function to check if user id provided is valid.
 *
 * student_linkedlist: linked list of the students
 * id: id provided
 */
bool is_valid_id(List* student_linkedlist, int id);

/*
 * get_idx_by_id: Function to get the index in linked list based on the id
 *
 * student_list: linked list of the students
 * id: id provided
 */
int get_idx_by_id(List* student_list, int id);

/*
 * del_edit_Student: Function to delete/edit any data of the student
 *
 * sutdent_linkedlist: linked list of the students
 * modules_linkedlist: linked list of the modules
 */
int del_edit_Student(List* sutdent_linkedlist, int* columns, int* rows, List* modules_linkedlist);

/*
 * display_rewrite_grades: Function that displays modules of the users, the number of grades and its avg
 *
 * stud: Struct Student to be modified
 * Modules: linked list of the modules
 */
void display_rewrite_grades(Student* stud, List* Modules);

bool is_nonvalid_modName(List* module_linkedlist, char* mod_name);

/*
 * del_edit_Module: Function to delete/edit the modules coef and names
 *
 * stud: Struct Student to be modified
 * Modules: linked list of the modules
 */
int del_edit_Module(List* modules_linkedlist, int* columns, int* rows, List* students_linkedlist);

#endif