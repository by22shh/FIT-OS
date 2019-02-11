#include <stdlib.h>
#include <stdio.h>

#include <getopt.h>

#include <sys/types.h>
#include <unistd.h>

#include <ulimit.h>

#include <sys/time.h>
#include <sys/resource.h>

main(int argc, char *argv[], char * envp[]) {
    if (argc == 1) {
        printf("No options\n");
        exit(0);
    }
        /* valid short options */
    const char short_options[] = "ispucdv";

    /* valid long options */
    const struct option long_options[] = {
        {"Unew_ulimit", required_argument, NULL, 0},
        {"Csize", required_argument, NULL, 0},
        {"VTERM", required_argument, NULL, 0},
        {"VSHELL", required_argument, NULL, 0},
        {"VSSH_CLIENT", required_argument, NULL, 0},
        {"VLC_NUMERIC", required_argument, NULL, 0},
        {"VSSH_TTY", required_argument, NULL, 0},
        {"VUSER", required_argument, NULL, 0},
        {"VMAIL", required_argument, NULL, 0},
        {"VPATH", required_argument, NULL, 0},
        {"VLC_MESSAGES", required_argument, NULL, 0},
        {"VLC_COLLATE", required_argument, NULL, 0},
        {"VPWD", required_argument, NULL, 0},
        {"VLANG", required_argument, NULL, 0},
        {"VTZ", required_argument, NULL, 0},
        {"VSHLVL", required_argument, NULL, 0},
        {"VHOME", required_argument, NULL, 0},
        {"VLOGNAME", required_argument, NULL, 0},
        {"VSSH_CONNECTION", required_argument, NULL, 0},
        {"VLC_CTYPE", required_argument, NULL, 0},
        {"VLC_TIME", required_argument, NULL, 0},
        {NULL,0,NULL,0}
    };
             
    int result;
    int option_index;
        
    struct rlimit rlim;
    
    char buffer[1024];
    
    int i;
    
    char *env_name, *env_value;

    long value;
    while ((result = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (result) {
                case 'i':
                        printf("Real UID\t= %d\n", getuid());
                        printf("Effective UID\t= %d\n", geteuid());
                        printf("Real GID\t= %d\n", getgid());
                        printf("Effective GID\t= %d\n", getegid());
                        break;
                case 's':
                        setpgid(0, 0);
                        break;
                case 'p':
                        printf("PID\t= %d\n", getpid());
                        printf("PPID\t= %d\n", getppid());
                        break;
                case 'u':
                        printf("Ulimit size\t %ld\n", ulimit(UL_GETFSIZE));
                        break;
                case 'c':
                        getrlimit(RLIMIT_CORE, &rlim);
                        printf("rlim_cur\t= %d\n", rlim.rlim_cur);
                        printf("rlim_max\t= %d\n", rlim.rlim_max);
                        break;
                case 'd':
                        getcwd(buffer, 1024);
                        printf("Current working directory\t=  %s\n", buffer);
                        break;
                case 'v':
                        for (i = 0; envp[i] != NULL; i++)
                                printf("\n%s", envp[i]);
                        break;
                case 0:
                        if(strcmp("Unew_ulimit", long_options[option_index].name ) == 0) {
                                value = atol(optarg);
                                if (value == 0) printf("Wrong value\n");
                                else ulimit(UL_SETFSIZE, atol(optarg));
                        } else if (strcmp("Csize", long_options[option_index].name) == 0) {
                                value = atol(optarg);
                                if (value == 0) printf("Wrong value\n");
                                else {
                                        rlim.rlim_cur = atol(optarg);
                                        rlim.rlim_max = atol(optarg);
                                        setrlimit(RLIMIT_CORE, &rlim);
                                }
                        } if(strcmp("VTERM", long_options[option_index].name ) == 0) {
                                setenv("TERM", optarg, 1);
                        } else if (strcmp("VSHELL", long_options[option_index].name) == 0) {
                                setenv("SHELL", optarg, 1);
                        } else if (strcmp("VSSH_CLIENT", long_options[option_index].name) == 0) {
                                setenv("SSH_CLIENT", optarg, 1);
                        } else if (strcmp("VLC_NUMERIC", long_options[option_index].name) == 0) {
                                setenv("LC_NUMERIC", optarg, 1);
                        } else if (strcmp("VSSH_TTY", long_options[option_index].name) == 0) {
                        		setenv("SSH_TTY", optarg, 1);
                        } else if (strcmp("VUSER", long_options[option_index].name) == 0) {
                                setenv("USER", optarg, 1);
                        } else if (strcmp("VMAIL", long_options[option_index].name) == 0) {
                                setenv("MAIL", optarg, 1);
                        } else if (strcmp("VPATH", long_options[option_index].name) == 0) {
                                setenv("PATH", optarg, 1);
                        } else if (strcmp("VLC_MESSAGES", long_options[option_index].name) == 0) {
                                setenv("LC_MESSAGES", optarg, 1);
                        } else if (strcmp("VLC_COLLATE", long_options[option_index].name) == 0) {
                                setenv("LC_COLLATE", optarg, 1);
                        } else if (strcmp("VPWD", long_options[option_index].name) == 0) {
                                setenv("PWD", optarg, 1);
                        } else if (strcmp("VLANG", long_options[option_index].name) == 0) {
                                setenv("LANG", optarg, 1);
                        } else if (strcmp("VTZ", long_options[option_index].name) == 0) {
                                setenv("TZ", optarg, 1);
                        } else if (strcmp("VSHLVL", long_options[option_index].name) == 0) {
                                setenv("SHLVL", optarg, 1);
                        } else if (strcmp("VHOME", long_options[option_index].name) == 0) {
                                setenv("HOME", optarg, 1);
                        } else if (strcmp("VLOGNAME", long_options[option_index].name) == 0) {
                                setenv("LOGNAME", optarg, 1);
                        } else if (strcmp("VSSH_CONNECTION", long_options[option_index].name) == 0) {
                                setenv("SSH_CONNECTION", optarg, 1);
                        } else if (strcmp("VLC_CTYPE", long_options[option_index].name) == 0) {
                                setenv("LC_CTYPE", optarg, 1);
                        } else if (strcmp("VLC_TIME", long_options[option_index].name) == 0) {
                                setenv("LC_TIME", optarg, 1);
                        }
                        break;

        }
    }
}


/*
argc - счетчик количества параметров командой строки argc.
argv - значения парамеров командной строки argv[].
optstring - список коротких названий параметров
longopts - специальный массив с названиями длинных параметров.
longindex - указатель на переменную, в которую будет помещен индекс текущего параметра из массива longopts. 
*/

/*
struct option {
	const char *name;
	int has_arg;
	int *flag;
	int val;
};
*/

/*
Поле flag задает указатель на флаг, в который помещается значение val, если найден данный параметр (сама функция при этом возвращает 0). Если указатель равен NULL, то функция возвращает значение val в качестве результата работы.
Поле var содержит значение, которое помещается в flag или возвращается в качестве результата работы функции.
*/

/*
В качестве результата работы функция getopt_long возвращает:
	- если короткий параметр, то его название (т.е. символ)
	- если длинный параметр, то значение val при flag=NULL, иначе 0 и флагу flag присваивается значение val.
*/

/*
Говоря в общем, реальный идентификатор пользователя (или группы) сообщает, кто создал процесс, а эффективный идентификатор пользователя (или группы) сообщает от чьего лица выполняется процесс, если эта информация изменяется.
*/

/*
Группа процессов - это совокупность процессов с одним и тем же идентификатором группы процессов.
*/

/*
Если pid равен 0, будет использован идентификатор вызывающего
процесса. Если pgid равен нулю, процесс с идентификатором pid станет
лидером группы процессов.
*/

/*
Идентификатор процесса Process ID (PID)
Каждый процесс имеет уникальный идентификатор PID, позволяющий ядру системы различать процессы. Когда создается новый процесс, ядро присваивает ему следующий свободный (т. е. не ассоциированный ни с каким процессом) идентификатор. Присвоение идентификаторов происходит по возрастающий, т.е. идентификатор нового процесса больше, чем идентификатор процесса, созданного перед ним. Если идентификатор достиг максимального значения, следующий процесс получит минимальный свободный PID и цикл повторяется. Когда процесс завершает свою работу, ядро освобождает занятый им идентификатор.
*/

/*
Процесс, который запустил процесс называется родительским 
*/

/*
Переменные окружения — именованные переменные, содержащие текстовую информацию, которую могут использовать запускаемые программы. 
*/
