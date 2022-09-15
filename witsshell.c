#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

int batchmode = 0;
void int_mode(){
                                                            //interactive mode
    char *buffer;                                           //simple array pointer                             
    ssize_t read;
    char b[1024];
    // char n[1024]; 
    char *gdir;
    char *dir;
    char *to; 
    int s;
    int rc;                                        

    /*while no exit or CTRL_D*/
    do{
        size_t buffersize = 32;    
        buffer = (char*)malloc(buffersize*sizeof(char));    //declare
        printf("witsshell> ");                              //prompt
        read = getline(&buffer,&buffersize,stdin);          //user input
        /*this will help to not change the user input*/
        char *buffbrother = buffer;                         //hey brother
        /*for spacing multiple reads*/
        char *found;                                        
        char **arg = malloc(buffersize*sizeof(char*));                              //data structure :/
        int pos = 0;                                        //num of arg
        found = strsep(&buffbrother," "); 
        /*getting user input from buffer 
         and separating em and storing 
          them to  array DS
        */ 
        while (found != NULL )
        {
            arg[pos] = found;
            pos++;

            if((int)pos >= (int)buffersize){
                buffersize+=buffersize;
                arg = realloc(arg,buffersize*sizeof(char*));
            }
            // printf("%s+%s\n",found,arg[pos]);
            found = strsep(&buffbrother," ");
        }
        arg[pos] = NULL;

        char *first[1];
        first[0] = arg[0];
        char * bin;
        if(!strcmp(first[0],"echo\n") || !strcmp(first[0],"echo")){
            bin = "/bin/echo";
            int s;
            int rc = fork();
            if(rc==0){
                execv("/bin/echo",arg);
            }
            else{
                wait(&s);
            }     
        }

        else if(!strcmp(first[0],"ls\n") || !strcmp(first[0],"ls")){
            bin = "/bin/ls";
            int s;
            int rc = fork();
            if(rc==0){
                execv("/bin/ls",arg);
            }
            else{
                wait(&s);
            }     
        }

        else if(!strcmp(first[0],"exit\n") || !strcmp(first[0],"exit")){
            exit(0);  
        }

        else if(!strcmp(first[0],"cd")){

            int s;
            int rc = fork();
            if(rc==0){
                /*gdir =*/ getcwd(b,sizeof(b));
                // dir = strcat(gdir,"/");
                // to = strcat(dir,arg[pos-1]);
                // printf("%s",gdir);
                to = "check";
                chdir(to);
                getcwd(b,sizeof(b));
                printf("changed to: %s\n",b);
                // exit(0);
            }
            else{
                wait(&s);
                // exit(1);
            }     
            
        }
        // printf("%s\n",bin);
        // rc = fork();
        // if(rc==0){
        //     execv(bin,arg);            
        // }
        // else{
        //     wait(&s);
        // } 
        //free(buffer);
        //free(arg);  
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

    if(batchmode == 1){
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