#include "user.h"

void sysPoziv(char** args){
    if(fork() == 0) { 
        char path[100];  

        strcpy(path, "/bin/");  
        memmove(path + strlen(path), args[0], strlen(args[0]) + 1); 
        printf("\nPozivam : \n", path);
        for (int i = 0; args[i] != 0; i++) {
            printf("  %s", args[i]);  
        }
        printf("\n");
        sleep(300);
        //
        exec(path, args); 
        // 
        printf("exec failed: %s\n", path);
        exit();  
    }
    wait(); 
}

int main(int argc, char *argv[]) {   
    char *argsd[] = {"blockwriter", "-o", "milos.aca", "-b", "57", 0};  
    sysPoziv(argsd);

    char *args1[] = {"cat", "milos.aca", 0};  
    sysPoziv(args1);

    char *args2[] = {"setkey", "5", 0};  
    sysPoziv(args2);

    char *args3[] = {"encr", "milos.aca", 0};  
    sysPoziv(args3);

    char *args4[] = {"cat", "milos.aca", 0};  
    sysPoziv(args4);
    printf("\n");
    exit();
}
