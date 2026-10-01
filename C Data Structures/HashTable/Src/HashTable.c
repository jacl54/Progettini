#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "HashTable.h"

//necessario quando si elimina un elemento perchè altrimenti la search si ferma a metà della catena :C
static item DELETED_ITEM = {NULL, NULL};

static item* new_item(char* k, char* v){
    item* i = malloc(sizeof(item));
    i->key = k;
    i->value = v;
    return i;
}

static void del_item(item* i){
    free(i->key);
    free(i->value);
    free(i);
}

table* new_table(){
    table* h = malloc(sizeof(table));
    h->count = 0;
    h->size = 53;
    h->items = calloc((size_t)h->size, sizeof(item*));
    //printf("creata nuova tabella con lunghezza %d\n", h->size);
    return h;
}

void del_table(table* h){
    for (int i = 0; i < h->size; i++ ){
        item* j = h->items[i];
        if(j!=NULL){
            del_item(j);
        }
    }
    free(h->items);
    free(h);
    //ovviamente free si usa solo con puntatori
}

int hf(char* s, int mult, int buckets){
    long hash = 0;
    int length = strlen(s);
    for (int i = 0; i < length; i++){
        hash+=(long)(pow(mult, length - (i+1))*(int)s[i]);
        hash%=buckets;
    }
    return (int)hash;
}

//Double hashing : quando si trova una collisione si aggiunge un altro hash per trovare la posizione corretta (con un minimo di 1)

int HashFunctionCollision(char* s, int buckets, int attempt){
    //151 e 163 sono primi maggiori del numero di caratteri codificabili (per ascii normale sono 128)
    int hash1 = hf(s, 151, buckets);
    int hash2 = hf(s, 163, buckets);
    return (hash1 + attempt * (hash2 + 1)) % buckets;
}

int FindHash(char* key, table* h){
    int i=1;
    int hash = HashFunctionCollision(key, h->size, 0);
    while(h->items[hash]!=NULL){
        if(h->items[hash]!=&DELETED_ITEM){ 
            if (strcmp(h->items[hash]->key, key)==0){
                return hash;
            }
        }
        hash = HashFunctionCollision(key, h->size, i);
        //if(i==53){return -1;}
        i++;
    }
    return -1;
}
void resize(table* h, int length){
    table* h1
}

void insert(char* key, char* value, table* h){
    int k = FindHash(key, h);
    if(k!=-1){
        del_item(h->items[k]);
        h->items[k] = new_item(key, value);
        return;
    }else{
        int i=0;
        int hash;
        do{
            hash = HashFunctionCollision(key, h->size, i);
            i++;
        }while(h->items[hash]!=NULL && h->items[hash]!=&DELETED_ITEM);

        h->items[hash]=new_item(key, value);
        h->count++;
        
    }
    
}

char* search(char* key, table* h){
    int pos = FindHash(key, h);
    if(pos == -1){return NULL;}
    return h->items[pos]->value;
}


void delete(char* key, table* h){
    int pos = FindHash(key, h);
    if(pos == -1){
        printf("Elemento inesistente\n");
    }else{
        del_item(h->items[pos]);
        h->items[pos] = &DELETED_ITEM;
        h->count--;
    }
}

void printTable(table* h){
    item** array = h->items;
    for(int i = 0; i < h->size; i++){
        if(array[i]!=NULL){
            printf("Key: %s; Value: %s\n",array[i]->key, array[i]->value);
        }
    }
}