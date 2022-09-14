#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int batchmode = 0;
void int_mode(){
    char *buffer;
    size_t buffersize = 32;
    ssize_t read;
    int c;

    do{
        
        buffer = (char*)malloc(buffersize*sizeof(char));
        printf("witsshell> ");
        read = getline(&buffer,&buffersize,stdin);
        char *buffbrother = buffer;
        // printf("print this\n");
        // char **token = (char*)malloc(buffersize*sizeof(char));
        char *found;
        char *arg[buffersize];
        int pos=0;
        found = strsep(&buffbrother," ");
        while (found != NULL )
        {
            arg[pos] = found;
            
            if(pos>=buffersize){
                buffersize+=buffersize;
                arg[buffersize];
            }
            printf("%s+%s\n",found,arg[pos]);
            found = strsep(&buffbrother," ");
            pos++;
        } 
        free(found);
        free(buffbrother);
    }
    while(strcmp(buffer,"exit\n") &&!feof(stdin));
}
int main(int argc,char* argv[]){

    char *file = "/no/such/file";
    if(argc>2){
        char error[32] = "error";
        exit(1); 
    }
    else if(argc==2){
        batchmode = 1;
        file =  argv[1];
        printf("reading file\n");
    }

    FILE *new;
    FILE *fp;

    if(batchmode==1){
        printf("read\n");
        fp = fopen(file,"r");
        int c = getc(fp);
        while (c!=EOF)
        {
            putchar(c);
            c = getc(fp);
        }
        exit(0);
    }
    else{
        int_mode();
    }
    
    return 0;
}