#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[]){
        pid_t proc;

        if((proc = fork()) == 0){
                execl("/bin/cat", "cat", "Lab9.c", NULL);
        }
        else if(proc == -1){
                return 1;
        }
        printf("Parent waits ...\n");

        wait(0);

        printf("Parent's turn.\n");

        return 0;
}