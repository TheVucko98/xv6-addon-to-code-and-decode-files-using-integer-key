#include "user.h"

int isNumber(char* str){
    

    for(int i = 0; str[i] != '\0'; i++){
        
        if(!(str[i] >= '0' && str[i] <= '9' ) && str[i] != '\n'){
            
            return 0;
        }
    }

    return 1;
}

void print_help() {
    printf("Use this program to set the current active key.\n");
    printf("After setting the key, you use encr and decr with key\n");
    printf("Usage: setkey [OPTION]... [KEY]\n");
    printf('\n');
    printf("--help (-h)           Show help menu\n");
    printf("--secret (-s)    Enter the key via STDIN. Hide key when entering it.\n");
    
}


int
main(int argc, char** argv){
    if(argc != 2){
        printf("Error: Must contain 2 arguments!\n");
        exit();
    }
    int x;
    if(strcmp(argv[1],  "-h") == 0 || strcmp(argv[1],"--help") == 0){
        print_help();
        exit();
    }else if (strcmp(argv[1],  "-s") == 0 || strcmp(argv[1],"--secret") == 0){
        char buff[20];
        printf("Enter the key: ");
        setecho(0);
        gets(buff,20);
        if(!isNumber(buff)){
            printf("Error: Invalid input, must contain only numbers\n");
            setecho(1);
            exit();
        }
        setkey(atoi(buff));
        setecho(1);
        printf("%s\n", buff);
        
    }else{
        if(!isNumber(argv[1])){
            printf("Error: Invalid input, must contain only numbers\n");
            exit();
        }
        int key = atoi(argv[1]);
        setkey(key);
        printf("%d\n",key);
        
    }
    
    


    
    exit();
}