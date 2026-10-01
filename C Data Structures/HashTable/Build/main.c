#include <stdlib.h>
#include <stdio.h>

#include "../Src/HashTable.c"

int main(){
    table* h = new_table();
    insert("1", "mannaggia1231", h);
    printf("%s",search("1", h));
    return 0;
}