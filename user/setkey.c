#include "user.h"

int isNumber(char* str){
    

    for(int i = 0; str[i] != '\0'; i++){
        
        if(!(str[i] >= '0' && str[i] <= '9' ) && str[i] != '\n'){
            
            return 0;
        }
    }

    return 1;
}


int
main(int argc, char** argv){
    if(argc != 2){
        printf("Greska\n");
        exit();
    }
    int x;
    if(strcmp(argv[1],  "-h") == 0 || strcmp(argv[1],"--help") == 0){
        printf("Helo je ovde!\n");
        exit();
    }else if (strcmp(argv[1],  "-s") == 0 || strcmp(argv[1],"--secret") == 0){
        char buff[20];
        setecho(0);
        gets(buff,20);
        if(!isNumber(buff)){
            printf("Neispravan unos\n");
            setecho(1);
            exit();
        }
        setkey(atoi(buff));
        setecho(1);
        printf("%s\n", buff);
        
    }else{
        if(!isNumber(argv[1])){
            printf("Neispravan unos\n");
            exit();
        }
        int key = atoi(argv[1]);
        setkey(key);
        printf("%d\n",key);
        
    }
    
    


    
    exit();
}