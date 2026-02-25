#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "md5.c"
//#include "main.c"

int HashCheck(uint8_t *a,uint8_t *b);
void initialize_string(char *p, int length);
void print_string(char *p, int length);

void *calcHash(void *arg);
pthread_mutex_t mutex;
int end=0;
int counter=0;
uint8_t Testing[16];
int i = 0;

int main(){
    pthread_mutex_init(&mutex, NULL);
    //uint8_t accetta il == come controllo
    //nel caso di evitare caratteri speciali
    //char chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int count=0;
    //MD5String(stringa, puntatore uint8_t) è la funzione
    md5String("Jacopo66", Testing);
    //md5String("Jacopo66", Finding);
    //print_hash(Testing);
    //printf("%d", HashCheck(Testing, Finding));
    pthread_t threads[8];
    int j=0;
    while (end!=1){
        while(end!=1 && counter<8){
            if(pthread_create(&threads[j], NULL, calcHash, NULL)!=0){
                printf("Errore");
                return 1;
            }
            counter++;
            j++;
        }
        if(j==8){
            j=0;
        }
        pthread_join(threads[j], NULL);
    }
    return 0;
}

int HashCheck(uint8_t *a ,uint8_t *b){
    for(int i = 0; i<16; i++){
        if(a[i]!=b[i]){
            return 0;
        }
    }
    return 1;
}
void initialize_string(char *p, int length){
    for(int i = 0; i<length; i++){
        p[i]='0';
    }
}
void print_string(char *p, int length){
    for(int i = 0; i<length; i++){
        printf("%c", p[i]);
    }
    printf("\n");
}

void *calcHash(void *arg){
    i++;
    char* current=malloc(sizeof(char)*i);
    uint8_t Finding[16];
    //sets string to '0'
    initialize_string(current, i);
    md5String(current, Finding);
    int j = i-1;
    while(end!=1 && current[0]!=127){
        //print_string(current, i);
        if(HashCheck(Testing, Finding)){
            pthread_mutex_lock(&mutex);
            if(end==1){
                break;
            }
            print_hash(Finding);
            print_string(current, i);
            end=1;
            pthread_mutex_unlock(&mutex);
            break;
        }
        while(j > -1 &&current[j]==126){
            j--;
        }
        if(j==-1){
            break;
        }
        current[j]++;
        while(j!=i-1){
            j++;
            current[j]='0';
        }
        md5String(current, Finding);
    }
    counter--;
}