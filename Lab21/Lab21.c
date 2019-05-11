#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int count;
int fd;
struct termios save_set; 

void interruption(int sig){
        if (sig == SIGQUIT){
                printf("   %d interruptions.\n", count);
                tcsetattr(fd, TCSAFLUSH, &save_set);
                exit(0);
        }
        ++count;
        printf("\a   %d\n", count);
        signal(sig, interruption);
}

int main(){
        signal(SIGINT, interruption);
        signal(SIGQUIT, interruption);
                
        struct termios terminal;
        
        fd = open("/dev/tty", O_RDWR);
        
        tcgetattr(fd, &terminal);
        save_set = terminal;

        terminal.c_lflag &= ~(ECHO|ICANON);
        terminal.c_cc[VINTR] = 27;

        tcsetattr(fd, TCSANOW, &terminal);      

        for (;;) {
                pause();
        }

        return 0;
}