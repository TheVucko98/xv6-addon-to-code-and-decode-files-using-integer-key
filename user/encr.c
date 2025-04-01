#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

void print_help() {
    printf("Use this program to encrypt selected files or all files in directorium.\n");    printf("Usage: encr [OPTION]\n");
    printf("\n");
    printf("--help (-h)           Show help menu\n");
    printf("--encrypt-all (-a)    Encrypt all files in directory\n");
    
}

void openAndEncrFile(char* filename){
    
    int fd = open(filename, O_RDWR);
        if(fd < 0){
            printf("There is no file [ %s ] in this directory!\n",filename);
            return;
        }
        int ret = encr(fd);
        // uslovi za sys poziv
        if(ret == -1){
            printf("File :  %s   Error: Encryption key not set.\n" , filename);
            
        }else if(ret == -2){
            printf("Error: File '%s' isn't able to be encrypted.\n", filename);
            
        }else if(ret == -3){
            printf("Error: File '%s' is already encrypted.\n", filename);  
            
        }else if(ret == 0){
            printf("File '%s' encrypted successfully.\n", filename);
        }else{
            printf("Error: Unknown encryption error (%d).\n", ret);
        }

    close(fd);
}
char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
    buf[strlen(p)] = '\0';
	return buf;
}

void openCurrDirAndEncrytFiles(){
    char *path = ".";
    char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(path, 0)) < 0){
		fprintf(2, "encr: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "encr: cannot stat %s\n", path);
		close(fd);
		return;
	}

    
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
        if(de.inum == 0)
            continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("encr: cannot stat %s\n", buf);
            continue;
        }
        if(st.type == T_FILE)
        openAndEncrFile(fmtname(buf));
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
    }else if(argc == 2 && (strcmp(argv[1],  "-a") == 0 || strcmp(argv[1],"--encrypt-all") == 0)){
        openCurrDirAndEncrytFiles();

    }else if(argc > 2){
        for(int i = 1; i < argc;i++){
            openAndEncrFile(argv[i]);
        }
    }else{
        openAndEncrFile(argv[1]);
    }
    
    exit();
}
