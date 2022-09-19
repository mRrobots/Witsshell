// void int_mode()
// {
//     // interactive mode
//     char *buffer; // simple array pointer
//     ssize_t read;
//     char b[1024];
//     char *to;
//     int s;
//     char *paths[1024]; // for storing path
//     int pathsize = 1;

//     /*while no exit or CTRL_D*/
//     do
//     {
//         paths[0] = "/bin/"; // start up bin
//         size_t buffersize = 32;
//         buffer = (char *)malloc(buffersize * sizeof(char)); // declare
//         printf("witsshell> ");                              // prompt
//         read = getline(&buffer, &buffersize, stdin);        // user input
//         /*this will help to not change the user input*/
//         char *buffbrother = buffer; // hey brother
//         /*for spacing multiple reads*/
//         char *found;
//         char **arg = malloc(buffersize * sizeof(char *));
//         // data structure :/
//         int pos = 0; // num of arg
//         found = strsep(&buffbrother, " ");
//         strtok(found, "\n");
//         /*getting user input from buffer
//          and separating em and storing
//           them to  array DS
//         */
//         int redirection = 0; // This is for Redirection
//         int parallelism = 0; // Parallelism
//         int n_com = 1;       // number of coms
//         while (found != NULL)
//         {
//             arg[pos] = found;
//             char *first[1];
//             first[0] = arg[pos];
//             pos++;

//             // if the buffer is already full, put some more(lets say 2x)
//             if ((int)pos >= (int)buffersize)
//             {
//                 buffersize += buffersize;
//                 arg = realloc(arg, buffersize * sizeof(char *));
//             }
//             if (strcmp(first[0], ">") == 0)
//             {                    // check if i have to rerout to the output file
//                 redirection = 1; // yep we have to, but becareful
//             }
//             if (strcmp(first[0], "&") == 0)
//             {                    // parallel commands sign
//                 parallelism = 1; // yep we got one,maybe more
//                 n_com++;
//             }
//             found = strsep(&buffbrother, " ");
//             strtok(found, "\n");
//         }

//         arg[pos] = NULL; // make last value,for terminating

//         char *first[1]; // Helper :/
//         first[0] = arg[0];
//         // printf("number of coms: %d\n pos: %d\n element : %s\n" ,n_com,pos,arg[0]);
//         for (int i = 0; i < n_com; i++)
//         {
//             /*// char **parg = malloc(buffersize*sizeof(char*));
//             for (int j = 0; j < pos; j++)
//             {
//                 printf("from here: %s:(%d;%d)\n", arg[j], i, j);
//             }*/
//             // if(fork() == 0){
//                 //Exit command
//                 if(!strcmp(first[0],"exit")){
//                     if(pos>1){
//                         char error_message[30] = "An error has occurred\n";
//                         write(STDERR_FILENO, error_message, strlen(error_message));
//                     }
//                     exit(0);
//                 }
//                 //CD command
//                 else if(!strcmp(first[0],"cd")){
//                     int rc = fork();
//                     if(rc==0){
//                         getcwd(b,sizeof(b));
//                         char *str1 = arg[pos-1];
//                         strtok(str1,"\n");
//                         to = str1;
//                         int chd = chdir(to);
//                         if(chd == -1){
//                             //error occured
//                             char error_message[30] = "An error has occurred\n";
//                             write(STDERR_FILENO, error_message, strlen(error_message));
//                         }
//                         // getcwd(b,sizeof(b));
//                         // printf("changed to: %s\n",b);
//                     }
//                     else{
//                         wait(NULL);
//                         exit(1);
//                     }
//                 }
//                 //Path eg./bin/mosis/usr
//                 else if(!strcmp(first[0],"path")){
//                     pathsize = 1;
//                     //inserting paths
//                     for(int i=1;i<pos;i++){
//                         paths[i] = arg[i];
//                         pathsize++;
//                     }
//                 }

//                 //Non-Built in Commands
//                 else{
//                     for(int i = 0;i<pathsize;i++){
//                         char dest[128];
//                         char dest2[128];
//                         char *path = paths[i];
//                         char *a = first[0];
//                         strtok(a,"\n");
//                         strcpy(dest,path);
//                         strcpy(dest2,a);
//                         strcat(dest,dest2); 
//                         int fd = access(dest,X_OK);
//                         if( fd == 0){
//                             if(redirection){
//                                 //write to a file
//                                 mode_t mode= S_IRWXU; //mode to read and write and execute
//                                 int fdr = open("mosis.txt",O_WRONLY|O_CREAT|O_TRUNC,mode);
//                                 int rc = fork();
//                                 if(rc==0){
//                                     dup2(fdr,1); //send std to file mosis
//                                     dup2(fdr,2); //send std to file mosis
//                                     close(fdr);
//                                     execv(dest,arg); //this will exit
//                                 }
//                                 else{
//                                     wait(NULL);
//                                 }
//                                 close(fdr);
//                             }
//                             else{
//                                 int rc = fork();
//                                 if(rc==0){
//                                     execv(dest,arg);
//                                 }
//                                 else{
//                                     wait(&s);
//                                 }
//                             }
//                             break;
//                         }
//                         else{
//                             //no path found for ruunning a command
//                             //its an error
//                         }
//                     }
//                 }
//             // }
//         }

//         // int corpse;
//         // int status;
//         // while ((corpse = wait(&status)) > 0)
//         // {
//         //     exit(0);
//         // }

//     } while (strcmp(buffer, "exit\n") && !feof(stdin));
// }