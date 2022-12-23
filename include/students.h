#pragma once
#ifndef STUDENTS_STRCT
#define STUDENTS_STRCT
#ifndef LINKED_LIST
#define LINKED_LIST
#include "../include/linked_list.h"
#endif

struct Student
{
	int Age;
	int ID;
	int module_count;

	char* Name;
	char* FirstName;
	char* Nationality;

	//Will contain addresses to Modules structures 
	List* Modules;
};
typedef struct Student Student;
#endif
