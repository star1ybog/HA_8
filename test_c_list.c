#include <assert.h>
#include "c_list.h"

int main() {
    c_list* list = create_list(2);
    assert(list != NULL);

    int int_val = 42;
    float float_val = 3.14;
    char* str_val = "hello";

    list->append(list, &int_val, int_type);
    list->append(list, &float_val, float_type);
    list->append(list, str_val, string_type);

    assert(list->size == 3);

    c_list* copied_list = list->copy(list);
    assert(copied_list->size == list->size);

    list->clear(list);
    assert(list->size == 0);

    list->destroy(list);
    copied_list->destroy(copied_list);

    printf("All tests passed!\n");
    return 0;
}
