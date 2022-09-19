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
    char arry[10] = "Vusi";
    char *n = arry+1;
    printf("%c\n",n[0]);
    printf("%s",arry);
}