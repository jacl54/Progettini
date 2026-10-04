typedef struct
{
    char* key;
    char* value;
}item;


typedef struct
{
    int base_size;
    int size;
    int count;
    item** items;
}table;


table* new_table_size(int size);

void insert(char* key, char* value, table* h);