#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>


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
    char *paths[1024];
    // char *path[1024];
    int pathsize = 1;
    
                                           

    /*while no exit or CTRL_D*/
    do{
        paths[0] = "/bin/";
        size_t buffersize = 32;    
        buffer = (char*)malloc(buffersize*sizeof(char));    //declare
        printf("witsshell> ");                              //prompt
        read = getline(&buffer,&buffersize,stdin);         //user input
        /*this will help to not change the user input*/
        char *buffbrother = buffer;                         //hey brother
        /*for spacing multiple reads*/
        char *found;                                        
        char **arg = malloc(buffersize*sizeof(char*)); 
                                     //data structure :/
        int pos = 0;                                        //num of arg
        found = strsep(&buffbrother," "); 
        /*getting user input from buffer 
         and separating em and storing 
          them to  array DS
        */
       int redirection = 0; 
        while ( found != NULL )
        {
            arg[pos] = found;
            char *first[1];
            first[0] = arg[pos];
            pos++;

            if((int)pos >= (int)buffersize){
                buffersize+=buffersize;
                arg = realloc(arg,buffersize*sizeof(char*));
            }
            if(strcmp(first[0],">") == 0){  //check if i have to rerout to the output file
                redirection = 1; //yep we have to, but becareful
            }
            // printf("%s+%s\n",found,arg[pos]);
            found = strsep(&buffbrother," ");
        }

        arg[pos] = NULL;
        

        char *first[1];
        first[0] = arg[0];
        char * bin;

        if(!strcmp(first[0],"exit\n") || !strcmp(first[0],"exit")){
            exit(0);  
        }

        else if(!strcmp(first[0],"cd")){

            int s;
            int rc = fork();
            if(rc==0){
                getcwd(b,sizeof(b));
                char *str1 = arg[pos-1];
                strtok(str1,"\n");
                to = str1;
                chdir(to);
                getcwd(b,sizeof(b));
                printf("changed to: %s\n",b);
                // exit(0);
            }
            else{
                wait(&s);
                exit(1);
            }     
        }
        else if(!strcmp(first[0],"path")){
            pathsize = 1;
            for(int i=1;i<pos;i++){
                paths[i] = arg[i];
                pathsize++;
            }
        }

        else{
            for(int i = 0;i<pathsize;i++){
                char dest[128];
                char dest2[128];
                char *path = paths[i];
                char *a = first[0];
                strtok(a,"\n");
                /*printf("%s\n",path);
                printf("%s\n",a);*/
                strcpy(dest,path);
                strcpy(dest2,a);
                /*printf("%s\n",dest);
                printf("%s\n",a);*/
                strcat(dest,dest2);
                // printf("%s\n",dest);
                // strcat(path,a);
                int fd = access(dest,X_OK);
                if( fd ==0){
                    if(redirection){
                        //write to a file
                        mode_t mode= S_IRWXU; //mode to read and write and execute
                        int fdr = open("mosis.txt",O_WRONLY|O_CREAT|O_TRUNC,mode);
                        int rc = fork();
                        
                        if(rc==0){
                            dup2(fdr,1);
                            dup2(fdr,2);
                            close(fdr);
                            execv(dest,arg);
                        }
                        else{
                            wait(&s);
                        }
                        close(fdr);
                    }
                    else{
                        int rc = fork();
                        if(rc==0){
                            execv(dest,arg);
                        }
                        else{
                            wait(&s);
                        }     
                    }
                }
                else{
                    //its an error
                }
            }
        }     
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