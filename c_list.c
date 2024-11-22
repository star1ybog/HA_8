#include "c_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

c_list* create_list(size_t initial_capacity) {
    c_list* list = (c_list*)malloc(sizeof(c_list));
    if (!list) return NULL;

    list->items = (void**)malloc(initial_capacity * sizeof(void*));
    list->types = (list_data_type*)malloc(initial_capacity * sizeof(list_data_type));
    if (!list->items || !list->types) {
        free(list->items);
        free(list->types);
        free(list);
        return NULL;
    }

    list->size = 0;
    list->capacity = initial_capacity;

    // Assign function pointers
    list->append = append;
    list->pop = pop;
    list->destroy = destroy;
    list->print = print;
    list->copy = copy;
    list->clear = clear;

    return list;
}

static void reallocate_if_needed(c_list* list) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->items = realloc(list->items, list->capacity * sizeof(void*));
        list->types = realloc(list->types, list->capacity * sizeof(list_data_type));

        if (!list->items || !list->types) {
            fprintf(stderr, "Memory reallocation failed!\n");
            exit(EXIT_FAILURE);
        }
    }
}

void append(c_list* list, void* item, list_data_type type) {
    reallocate_if_needed(list);

    if (type == int_type) {
        list->items[list->size] = malloc(sizeof(int));
        memcpy(list->items[list->size], item, sizeof(int));
    } else if (type == float_type) {
        list->items[list->size] = malloc(sizeof(float));
        memcpy(list->items[list->size], item, sizeof(float));
    } else if (type == string_type) {
        size_t len = strlen((char*)item) + 1; // Include null-terminator
        list->items[list->size] = malloc(len);
        memcpy(list->items[list->size], item, len);
    }

    list->types[list->size] = type;
    list->size++;
}

void pop(c_list* list) {
    if (list->size == 0) return;

    list->size--;
    if (list->types[list->size] == string_type) {
        free(list->items[list->size]); // Free string memory
    }
    list->items[list->size] = NULL; // Avoid dangling pointer
}

void destroy(c_list* list) {
    for (size_t i = 0; i < list->size; i++) {
        if (list->types[i] == string_type) {
            free(list->items[i]);
        }
    }
    free(list->items);
    free(list->types);
    free(list);
}

c_list* copy(const c_list* list) {
    c_list* new_list = create_list(list->capacity);
    if (!new_list) return NULL;

    for (size_t i = 0; i < list->size; i++) {
        if (list->types[i] == string_type) {
            new_list->append(new_list, list->items[i], string_type);
        } else {
            new_list->append(new_list, list->items[i], list->types[i]);
        }
    }
    return new_list;
}

void clear(c_list* list) {
    for (size_t i = 0; i < list->size; i++) {
        if (list->types[i] == string_type) {
            free(list->items[i]);
        }
    }
    list->size = 0;
}

void print(const c_list* list) {
    for (size_t i = 0; i < list->size; i++) {
        if (list->types[i] == int_type) {
            printf("%d ", *(int*)(list->items[i]));
        } else if (list->types[i] == float_type) {
            printf("%f ", *(float*)(list->items[i]));
        } else if (list->types[i] == string_type) {
            printf("%s ", (char*)(list->items[i]));
        }
    }
    printf("\n");
}
