#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>

int batchmode = 0;
void int_mode(){
                                                            //interactive mode
    char *buffer;                                           //simple array pointer                             //size of string
    ssize_t read;                                           //idk why this but cool

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
        // printf("%s\n",first[0]);
        if(!strcmp(first[0],"echo\n") || !strcmp(first[0],"echo")){
            
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
            
            int s;
            int rc = fork();
            if(rc==0){
                execv("/bin/ls",arg);
            }
            else{
                wait(&s);
            }     
        }
        //now we execute the arg
        // int rc = fork();
        // if(rc < 0){
        //     //some problems
        //     fprintf(stderr,"fork failed\n");
        //     exit(1);
        // } 
        // else if(rc == 0){
        //     //child
        //     // printf("%d+%s ",pos,arg[0]);
        //     if(!strcmp(arg[0],"echo")){
        //         execv("/bin/echo",arg);
        //     }
        //     else if(!strcmp(arg[0],"ls")){ 
        //         // char* arr[] = {"ls",NULL};
        //         printf("%s ",arg[0]);
        //         // execv("/bin/ls",arg);
        //         exit(0);
        //     }
        //     else{
        //         printf("%s+",arg[0]);
        //     }
        // }
        // else{
        //     //parent
        //     int wc = wait(NULL);
        // }
        
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