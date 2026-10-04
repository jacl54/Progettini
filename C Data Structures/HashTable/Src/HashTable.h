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
