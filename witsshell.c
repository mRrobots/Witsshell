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
size_t buffersize = 32;  
void command(char* buffer){
    char *filename[1];
    char b[1024];
    char *to; 
    int s;
    char *paths[1024];                                      //for storing path
    paths[0] = "/bin/";                                 //start up bin
    int pathsize = 1;
    /*this will help to not change the user input*/
    char *buffbrother = buffer;                         //hey brother
    /*for spacing multiple reads*/
    char *found;                                        
    char **arg = malloc(buffersize*sizeof(char*));      //data structure :/
    int pos = 0;                                        //num of arg
    found = strsep(&buffbrother," "); 
    strtok(found,"\n");

    int redirection = 0;                                //This is for Redirection
    int parallelism = 0;                                //Parallelism
    int n_com = 1;                                      //number of coms

    while ( found != NULL )
    {
        arg[pos] = found;
        pos++;

        //if the buffer is already full, put some more(lets say 2x)
        if((int)pos >= (int)buffersize){
            buffersize+=buffersize;
            arg = realloc(arg,buffersize*sizeof(char*));
        }
        if(strcmp(arg[pos-1],">") == 0){  //check if i have to rerout to the output file
            redirection = 1; //yep we have to, but becareful
            pos--;//cannot put  > in  out command
        }
        if(strcmp(arg[pos-1],"&") == 0){  //check if i have to rerout to the output file
            parallelism = 1; //yep we have to, but becareful
            n_com++;
            pos--;//cannot put & in  out comman
        }
        found = strsep(&buffbrother," ");
        strtok(found,"\n");
        if(redirection){
            //get the file name
            filename[0] = arg[pos-1];
        }
    }
    // printf("%s",filename[0]);
    char *first[1]; //Helper array:/
    first[0] = arg[0];
    //Exit command
    if(!strcmp(first[0],"exit")){
        exit(0);  
    }

        //CD command
    else if(!strcmp(first[0],"cd")){
    // int s; //NULL
        int rc = fork();
        if(rc==0){
            getcwd(b,sizeof(b));
            char *str1 = arg[pos-1];
            strtok(str1,"\n");
            to = str1;
            int c = chdir(to);
            if(c==-1){
                //error
            }
        }
        else{
            wait(NULL);
            exit(1);
        }     
    }
    //Path eg./bin/mosis/usr
    else if(!strcmp(first[0],"path")){
        pathsize = 1;
        //inserting paths
        for(int i=1;i<pos;i++){
            paths[i] = arg[i];
            pathsize++;
        }
    }

    //Non-Built in Commands
    else{
        for(int i = 0;i<pathsize;i++){
            char dest[128];
            char dest2[128];
            char *path = paths[i];
            char *a = first[0];
            //remove the newline,just incase we have it
            strtok(a,"\n");
            //concatination of the path and current command
            strcpy(dest,path);
            strcpy(dest2,a);
            strcat(dest,dest2);
            //check if the file exists and executable
            int fd = access(dest,X_OK);
            if( fd ==0){
                //phakaty inside
                if(redirection){
                    //write to a file
                    mode_t mode= S_IRWXU; //mode to read and write and execute
                    int fdr = open(filename[0],O_WRONLY|O_CREAT|O_TRUNC,mode);
                    int rc = fork();
                    //child
                    if(rc==0){
                        //child process, will let evrything write on file
                        dup2(fdr,1);
                        // no idea for this
                        dup2(fdr,2);
                        close(fdr);
                        //execute the command
                        execv(dest,arg);
                    }
                    //parent 
                    else{
                        wait(NULL);
                    }
                    close(fdr);
                }
                else{
                    //nomarl execution
                    int rc = fork();
                    //child
                      if(rc==0){
                        execv(dest,arg);
                    }//parent
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
void int_mode(){
                                                            //interactive mode
    char *buffer;                                           //simple array pointer                             
    ssize_t read;

    /*while no exit or CTRL_D*/
    do{
          
        buffer = (char*)malloc(buffersize*sizeof(char));    //declare
        printf("witsshell> ");                              //prompt
        read = getline(&buffer,&buffersize,stdin);          //user input
       
        /*getting user input from buffer 
         and separating em and storing 
          them to  array DS
        */
          command(buffer);
    }
    while(!feof(stdin));
}
int main(int argc,char* argv[]){

    //error message for error
    char *file = "/no/such/file";

    //erro to many arguments
    if(argc>2){
        char error[32] = "error";
        exit(1); 
    }
    // arguments for reading on file(batch mode)
    else if(argc==2){
        //set a batch mode
        batchmode = 1;
        file =  argv[1];
        // printf("reading file\n");
    }

    //batch or witsshell, lets found out

    FILE *fp;

    if(batchmode == 1){
        //we are in batch mode
        fp = fopen(file,"r");
        char line[256];
        char ch;
        

        do{
          
        while (fgets(line ,sizeof(line),fp)/* && (ch = getchar()) != EOF*/ ){
            command(line);//read line
        }
        fclose(fp);
       
        /*getting user input from buffer 
         and separating em and storing 
          them to  array DS
        */
        }
        while(!feof(stdin));       
    }
    else{
        //witsshell
        int_mode();
    }
    return 0;
}