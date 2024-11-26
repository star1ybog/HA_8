#include "c_list.h"
#include <stdio.h>

int main() {
    c_list* list = create_list(2); // Initialize a list
    int int_val = 42;
    float float_val = 3.14;
    char* str_val = "hello";

    list->append(list, &int_val, int_type);
    list->append(list, &float_val, float_type);
    list->append(list, str_val, string_type);

    printf("List before pop:\n");
    list->print(list);

    list->pop(list);

    printf("List after pop:\n");
    list->print(list);

    list->destroy(list); // Free memory
    return 0;
}
