#pragma once

#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct ListNode {
	void* data;
	struct ListNode* next;
} ListNode;

typedef struct List {
	ListNode* head;
	ListNode* tail;
	size_t length;
} List;

// Creates a new list and returns a pointer to it.
List* list_create();

// Frees the memory used by a list and all its nodes.
void list_destroy(List* list);

// Inserts a new element at the end of the list.
bool list_append(List* list, void* data);

// Inserts a new element at the beginning of the list.
bool list_prepend(List* list, void* data);

// Removes the element at the specified index from the list.
bool list_remove(List* list, size_t index);

// Returns the element at the specified index in the list.
void* list_get(List* list, size_t index);

// Return the length of the list
int* list_size(List* list);

#endif // !LINKED_LIST
