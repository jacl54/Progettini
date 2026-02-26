#include <stdlib.h>
#include <stdio.h>


#include "md5.c"

int HashCheck(uint8_t *a ,uint8_t *b);
void initialize_string(char *p, int length);
void print_string(char *p);
int StringEquals(char *a, char *b);

int main(int argc, char **argv){
    int i=1;
    char* current=NULL;
    uint8_t Finding[16];
    md5String(argv[1], Finding);
    uint8_t Testing[16];
    uint8_t example[16];
    //md5String(argv[1], Finding);
    //printf("%d", HashCheck(Finding, Testing));
    //sets string to '0'
    while(!HashCheck(Finding, Testing)){    
        //md5String(argv[1], example);
        //print_hash(example);
        int j = i-1;
        current=realloc(current, sizeof(char)*(i+1));
        initialize_string(current, i);
        current[i]=0;
        md5String(current, Testing);
        while(current[0]!=127){

            /*//questa parte è testing, secondo questo IF due stringhe uguali hanno hash diverso
            if(StringEquals(current, argv[1])){
                //per qualche motivo cambia la generazione dell'hash dopo l'inizio
                print_string(argv[1]);
                print_hash(Finding);
                print_string(current);
                //md5String(argv[1], Testing);
                print_hash(Testing);
                printf("-------------");
                md5String(argv[1], example);
                print_hash(example);
                return 1;
                //conclusioni :: Hash deve essere unico per locazione in memoria della stringa calcolata
                //conclusione sbagliata, ho un problema con realloc
            }*/

            //questo serve per vedere quale stringa sta venendo controllata ora ma funge da bottleneck se usiamo thread
            print_string(current);
            //controllo che la stringa adesso abbia hashset uguale
            if(HashCheck(Testing, Finding)){
                print_hash(Finding);
                print_string(current);
                break;
            }
            while(j > -1 && current[j]==126){
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
            md5String(current, Testing);
        }
        i++;
    }
}

//controlla che gli hash digest in md5 siano uguali
int HashCheck(uint8_t *a ,uint8_t *b){
    for(int i = 0; i<16; i++){
        if(a[i]!=b[i]){
            return 0;
        }
    }
    return 1;
}

//setta una stringa tutta a "000000...."
void initialize_string(char *p, int length){
    for(int i = 0; i<length; i++){
        p[i]='0';
    }
}

//stampa una stringa
void print_string(char *p){
    int i = 0;
    while(p[i]!=0){
        printf("%c", p[i]);
        i++;
    }
    printf("\n");
}

//controlla che due stringhe siano uguali
int StringEquals(char *a, char *b){
    int i = 0;
    while(a[i]!=0 && b[i]!=0){
        if(a[i]!=b[i]){
            return 0;
        }
        i++;
    }
    if(a[i]==0 && b[i]!=0 || a[i]!=0 && b[i]==0){
        return 0;
    }
    return 1;
}