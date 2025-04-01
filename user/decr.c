#include "user.h"

void print_help() {
    printf("Use this program to decrypt selected encrypted files or all files in directorium.\n");    printf("Usage: encr [OPTION]\n");
    printf("\n");
    printf("--help (-h)           Show help menu\n");
    printf("--decrypt-all (-a)    decrypt all encrypted files in directory\n");
    
}

void openAndEncrFile(char* filename){
    
    int fd = open(filename, O_RDWR);
        if(fd < 0){
            printf("There is no file [ %s ] in this directory!\n",filename);
            return;
        }
        int ret = decr(fd);
        // uslovi za sys poziv
        if(ret == -1){
            printf("Error: Encryption key not set.\n");
            
        }else if(ret == -2){
            printf("Error: File %s isn't able to be decrypted (invalid type).\n", filename);
            
        }else if(ret == -3){
            printf("Error: File '%s' isn't encrypted.\n", filename);  
            
        }else if(ret == 0){
            printf("File '%s' decrypted successfully.\n", filename);
        }else{
            printf("Error: Unknown decryption error (%d).\n", ret);
        }
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