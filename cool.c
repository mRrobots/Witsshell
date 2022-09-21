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


int path = 0;
char arr[100][100];

void addHey(/*char arr[100][100]*/){
    strcpy(arr[path],"NoNoNO");
    printf("path = %d\n",path);
    path=0;
}
int main () {
    for(int i=0;i<4;i++){
        strcpy(arr[path],"hello");
        path++;
    }
    addHey(/*&(arr)*/);
    for(int i=0;i<=path;i++){
        printf("i %d__%s\n",i,arr[i]);
    }
    printf("path = %d\n",path);
    path++;
    addHey(/*&(arr)*/);

   return(0);
}