#pragma once
#ifndef MODULES_FOLL
#define MODULES_FOLL
#ifndef LINKED_LIST
#include "../include/linked_list.h"
#endif
#define MAX_GRADES 40

struct Modules_Storage_UserStruct
{
	char* module_name;

	int grades_amount;
	float grades[MAX_GRADES];
};
typedef struct Modules_Storage_UserStruct Modules_Storage_UserStruct;

typedef struct Module
{
	char* module_name;
	float coef;
}Module;

#endif