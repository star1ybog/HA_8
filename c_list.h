#ifndef C_LIST_H
#define C_LIST_H

#include <stddef.h> // For size_t

typedef enum {
    int_type,
    float_type,
    string_type
} list_data_type;

// c_list structure
typedef struct c_list {
    void** items;               // Dynamic array of pointers to elements
    list_data_type* types;      // Array of data types for each element
    size_t size;                // Number of elements
    size_t capacity;            // Current capacity of the list

    // Function pointers for list operations
    void (*append)(struct c_list* list, void* item, list_data_type type);
    void (*pop)(struct c_list* list);
    void (*destroy)(struct c_list* list);
    void (*print)(const struct c_list* list);
    struct c_list* (*copy)(const struct c_list* list); // Variant 1
    void (*clear)(struct c_list* list);               // Variant 1
} c_list;

// Function prototypes
c_list* create_list(size_t initial_capacity);
void append(c_list* list, void* item, list_data_type type);
void pop(c_list* list);
void destroy(c_list* list);
void print(const c_list* list);
c_list* copy(const c_list* list);
void clear(c_list* list);

#endif // C_LIST_H
