#include "user.h"

void print_help() {
    printf("Use this program to encr selected files or all files in directorium.\n");    printf("Usage: encr [OPTION]\n");
    printf("\n");
    printf("--help (-h)           Show help menu\n");
    printf("--encrypt-all (-a)    encrypt all files in directory\n");
    
}

void openAndEncrFile(char* filename){
    
    int fd = open(filename, O_RDWR);
        if(fd < 0){
            printf("There is no file [ %s ] in this directory!\n",filename);
            return;
        }
        int ret = encr(fd);
        // uslovi za sys poziv
        close(fd);
}

int
main(int argc, char **argv){
    if(argc == 1){
        print_help();
        exit();
    }
    if(argc == 2 && (strcmp(argv[1],  "-h") == 0 || strcmp(argv[1],"--help") == 0)){
        print_help();
        exit();
    }else if(argc == 2 && (strcmp(argv[1],  "-a") == 0 || strcmp(argv[1],"--encrypt-all") == 0)){
        
        printf("%s", argv[1]);

    }else if(argc > 2){
        for(int i = 1; i < argc;i++){
            openAndEncrFile(argv[i]);
        }
    }else{
        openAndEncrFile(argv[1]);
    }
    
    exit();
}