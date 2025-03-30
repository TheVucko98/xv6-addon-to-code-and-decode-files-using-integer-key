#include "user.h"

#define MAX_BLOCK 128*128+11+128

int isNumber(char* str){
    

    for(int i = 0; str[i] != '\0'; i++){
        
        if(!(str[i] >= '0' && str[i] <= '9' ) && str[i] != '\n'){
            
            return 0;
        }
    }

    return 1;
}

void print_help() {
    printf("Usage: blockwriter [OPTIONS]\n");
    printf(" With not parameters default block = 150, default name = long.txt \n");
    printf("--help (-h)           Show help menu\n");
    printf("--output-file (-o)    Set output filename (default: long.txt)\n");
    printf("--blocks (-b)         Set number of blocks (default: 150)\n");
}

int main(int argc, char *argv[]) {
    char *output_file = "long.txt";  
    int blocks = 150;               

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_help();
        exit();
    }
    if(argc == 2){
        printf("Error: Missing argument for %s\n", argv[1]);
        exit(); 
    }
    int flagO = 0, flagB = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--output-file") == 0 || strcmp(argv[i], "-o") == 0) {
            if(flagO){
                printf("Error: Repated argument %s, one is max\n", argv[i]);
                exit();
            }
            if (i + 1 < argc) {
                flagO++;
                output_file = argv[++i];  
            } else {
                printf("Error: Missing argument for %s\n", argv[i]);
                exit();           
            }
        }
        else if (strcmp(argv[i], "--blocks") == 0 || strcmp(argv[i], "-b") == 0) {
            if (i + 1 < argc) {
                if(flagB){
                    printf("Error: Repated argument %s, one is max\n", argv[i]);
                    exit();
                }

                

                if(!isNumber(argv[i+1])){
                    printf("Error: Invalid input, must contain only numbers\n");
                    exit();
                }
                if(MAX_BLOCK < atoi(argv[i+1])){
                    printf("Error: Input is bigger that max blocks %d\n",MAX_BLOCK);
                    exit();
                }

                flagB++;
                blocks = atoi(argv[++i]);  
            } else {
                printf("Error: Missing argument for %s\n", argv[i]);
                exit();
            }
        }
    }

    printf("Creating file: %s with %d blocks\n", output_file, blocks);

 
    int fd = open(output_file, O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf("Error: Failed to create file\n");
        exit();
    }

   
    char buffer[BLOCK_SIZE] = {'a'};
    memset(buffer, 'a', BLOCK_SIZE);

     

    for (int i = 0; i < blocks; i++) {
  
            if (i >= 100 && i < 1000) {
                int x = i;
    
           
                buffer[0] = (x / 100) + '0';  
                buffer[1] = ((x / 10) % 10) + '0'; 
                buffer[2] = (x % 10) + '0';  
                buffer[3] = '.';  
            } 
    
        
          
    
            if (write(fd, buffer, BLOCK_SIZE) != BLOCK_SIZE) {
                printf("Error: Write failed at block %d\n", i);
                close(fd);
                exit();
            }
      
        
       
        printf("\n");
        printf("Creating block %d/%d\n", i + 1, blocks);
       
        
    }
    close(fd);
    exit();
}
