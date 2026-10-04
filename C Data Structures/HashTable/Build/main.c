#include <stdlib.h>
#include <stdio.h>

#include "../Src/HashTable.c"

int main(){
    table* h = new_table();
    insert("1", "mannaggia1231", h);
    printf("%d\n",h->size);
    insert("2", "mannaggia1231", h);
    insert("3", "mannaggia1231", h);
    insert("4", "mannaggia1231", h);
    insert("5", "mannaggia1231", h);
    printf("%d\n",h->size);
    insert("6", "mannaggia1231", h);
    insert("7", "mannaggia1231", h);
    insert("8", "mannaggia1231", h);
    insert("9", "mannaggia1231", h);
    insert("10", "mannaggia1231", h);
    insert("11", "mannaggia1231", h);
    insert("12", "mannaggia1231", h);
    insert("13", "mannaggia1231", h);
    printf("%d\n",h->size);
    return 0;
}