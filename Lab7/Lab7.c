#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>

int file;
char *pa;
int length;

void myAlarm(int var) {
        printf("Time is over!\n");

        write(1, pa, length);

        close(file);
        exit(0);
}


int main(int argc, char **argv){
        int i;
        int lines[101]={0};
        int pos = 0;
        int num = 1;
        char str[10];
        char string[256];

        if (argc != 2) {
                printf("no file name\n");
                exit(1);
        }

        file = open(argv[1], O_RDONLY);
        length = lseek(file, 0, SEEK_END);      
        pa = mmap(0, length, PROT_READ, MAP_SHARED, file, 0);

        for (i = 0; i < length; i++) {
                if(*(pa + i) == '\n') {
                        ++pos;
                        lines[num] = pos;
                        ++num;
                } else {
                        ++pos;
                }
        }
        pos = num;

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
                else if(num >= pos) printf("Out of range!\n");
                else if( num >= 1){
                        write(1, pa + lines[num - 1], lines[num] - lines[num - 1]);
                }
        }

        close(file);

        return 0;
}

