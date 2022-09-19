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

int main(){
    for(int i=0;i<10;i++){
        if(i==1 || i==5){
            continue;
        }
        printf("%d",i);
        
    }
}