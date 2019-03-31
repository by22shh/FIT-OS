#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int file;

void myAlarm(int var) {
    printf("Time is over!\n");

    char c;

    lseek(file, 0, SEEK_SET);
    while(read(file, &c, 1)) {
        write(1, &c, 1);
    }
    close(file);
    exit(0);
}

int main(int argc, char **argv) {
        char c; 
        int lines[101] = {0};
        int num = 1;
        char string[256];
        char str[10];

        if (argc != 2) {
                printf("no file name\n");
                exit(1);
        }

        file = open(argv[1], O_RDONLY);

        while(read(file, &c, 1)){
                if(c == '\n'){
                        lines[num] = lseek(file, 0, SEEK_CUR);
                        ++num;                                  
                }
        }
        c = num;

        signal(SIGALRM, myAlarm);
        alarm(5);
        while(1) {
                printf("Write N of string: ");
                scanf("%s", str);
                alarm(0);
                num = atoi(str);
                if(num == 0) {
                        close(file);
                        return 0;
                }
                if(num < 0) printf("N should be > 0!\n");
                else if(num >= c) printf("Out of range!\n");
                else if( num >= 1){
                        lseek(file, lines[num - 1], SEEK_SET);
                        read(file, string, lines[num ] - lines[num - 1] - 1);
                        string[lines[num ] - lines[num - 1] - 1] = '\n';
                        write(1, string, lines[num ] - lines[num - 1]);
                }
        }

        close(file);

        return 0;
}

