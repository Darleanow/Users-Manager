#include "../include/linked_list.h"

// Creates a new list and returns a pointer to it.
List* list_create() {
    //Empty struct allocation
    List* list = malloc(sizeof(List));
    
    //If any runtime problems, list returns NULL
    if (list == NULL) {
        return NULL;
    }
    // Assignation to NULL
    list->head = NULL;
    list->tail = NULL;
    //Sets default length
    list->length = 0;
    return list;
}

// Frees the memory used by a list and all its nodes.
void list_destroy(List* list) {
    //Creating a new node and assigning it to the head
    ListNode* node = list->head;
    //While list isn't empty, we free each note
    while (node != NULL) {
        ListNode* next = node->next;
        free(node);
        node = next;
    }
    //Then we free the list
    free(list);
}

// Inserts a new element at the end of the list.
bool list_append(List* list, void* data) {
    //Default allocation
    ListNode* node = malloc(sizeof(ListNode));
    // if any runtime problems
    if (node == NULL) {
        return false;
    }
    //Assigning data to the node
    node->data = data;
    node->next = NULL;

    //If len of the list is 0, node to head
    if (list->tail == NULL) {
        list->head = node;
    }
    else {
        list->tail->next = node;
    }
    list->tail = node;
    list->length++;
    return true;
}

// This function adds a new node to the beginning of a linked list.
// The new node contains the data specified in the "data" parameter.
bool list_prepend(List* list, void* data) {

    // Allocate memory for the new node.
    ListNode* node = malloc(sizeof(ListNode));

    // If malloc fails, return false.
    if (node == NULL) {
        return false;
    }

    // Initialize the new node with the specified data.
    node->data = data;

    // Set the next pointer of the new node to the current head of the list.
    node->next = list->head;

    // Set the head of the list to the new node.
    list->head = node;

    // If the list was previously empty, set the tail of the list to the new node.
    if (list->tail == NULL) {
        list->tail = node;
    }

    // Increment the length of the list.
    list->length++;

    // Return true to indicate success.
    return true;
}

// This function removes the node at the specified index from a linked list.
bool list_remove(List* list, size_t index) {

    // If the index is out of bounds, return false.
    if (index >= list->length) {
        return false;
    }

    // Initialize pointers to the previous and current nodes.
    ListNode* prev = NULL;
    ListNode* node = list->head;

    // Iterate through the list until we reach the specified index.
    for (size_t i = 0; i < index; i++) {
        prev = node;
        node = node->next;
    }

    // If the node to be removed is the head of the list, update the head pointer.
    if (prev == NULL) {
        list->head = node->next;
    }
    // Otherwise, update the next pointer of the previous node.
    else {
        prev->next = node->next;
    }

    // If the node to be removed is the tail of the list, update the tail pointer.
    if (node->next == NULL) {
        list->tail = prev;
    }

    // Free the memory for the node and decrement the length of the list.
    free(node);
    list->length--;

    // Return true to indicate success.
    return true;
}

// This function retrieves the data stored in the node at the specified index in a linked list.
void* list_get(List* list, size_t index) {

    // If the index is out of bounds, return NULL.
    if (index >= list->length) {
        return NULL;
    }

    // Initialize a pointer to the current node.
    ListNode* node = list->head;

    // Iterate through the list until we reach the specified index.
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }

    // Return the data stored in the node.
    return node->data;
}

// This function returns the length of the linked list
int* list_size(List* list)
{
    return list->length;
}
