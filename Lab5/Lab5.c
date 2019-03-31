#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv){
        char c; 
        int file;
        int lines[101]={0};
        int num = 1;
        char str[10];
        char string[256];

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
        while(1){
                printf("Write N of string: ");
                scanf("%s", str);
                num = atoi(str);
                if(num == 0) {
                        close(file);
                        return 0;
                }
                if(num < 0) printf("N should be > 0!\n");
                else if(num >= c) printf("Out of range!\n");
                else if( num >= 1){
                        lseek(file, lines[num - 1], SEEK_SET);
                        read(file, string, lines[num ] - lines[num - 1]);
                        write(1, string, lines[num ] - lines[num - 1]);
                }
        }

        close(file);

        return 0;
}

