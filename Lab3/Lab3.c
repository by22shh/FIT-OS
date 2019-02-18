#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char **argv){

    printf("Real UID\t= %d\n", getuid());
    printf("Effective UID\t= %d\n", geteuid());

    if (argc != 2) {
        printf("No file name\n");
        exit(1);
    }

    FILE * FILE;
    FILE = fopen(argv[1], "r");
    if (FILE == NULL){
        perror("File not open");
    }

    fclose(FILE);

    setuid(getuid());

    printf("after using setuid \n");

    printf("Real UID\t= %d\n", getuid());
    printf("Effective UID\t= %d\n", geteuid());

    FILE = fopen(argv[1], "r");
    if (FILE == NULL){
        perror("File not open");
    }

    fclose(FILE);

    return 0;
}