#include <stdlib.h>
#include <stdio.h>

#include <getopt.h>

#include <sys/types.h>
#include <unistd.h>

#include <ulimit.h>

#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[], char * envp[]) {
    if (argc == 1) {
        printf("No options\n");
        exit(0);
    }

    const char valid_options[] = "ispuU:cC:dvV:";

    int result = 0;

    struct rlimit rlim;

    char buffer[1024];

    int i;

    long value;

    while ((result = getopt(argc, argv, valid_options)) != -1) {
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
                printf("PGID\t= %d\n", getpgid(0));
                break;
            case 'u':
                printf("Ulimit size\t %ld\n", ulimit(UL_GETFSIZE));
                break;
            case 'U':
                value = atol(optarg);
                if (value == 0) printf("Wrong value\n");
                else ulimit(UL_SETFSIZE, atol(optarg));
                break;
            case 'c':
                getrlimit(RLIMIT_CORE, &rlim);
                printf("rlim_cur\t= %d\n", rlim.rlim_cur);
                printf("rlim_max\t= %d\n", rlim.rlim_max);
                break;
            case 'C':
                value = atol(optarg);
                if (value == 0) printf("Wrong value\n");
                else {
                    rlim.rlim_cur = atol(optarg);
                    rlim.rlim_max = atol(optarg);
                    setrlimit(RLIMIT_CORE, &rlim);
                }
                break;
            case 'd':
                getcwd(buffer, 1024);
                printf("Current working directory\t=  %s\n", buffer);
                break;
            case 'v':
                for (i = 0; envp[i] != NULL; i++)
                    printf("\n%s", envp[i]);
                break;
            case 'V':
                env_optarg = optarg;

                env_name = strtok(env_optarg, "=");
                env_value = strtok(NULL, "=");

                setenv(env_name, env_value, 1);
        }
    }
    return 0;
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

/*
 * RLIMIT_CORE
Максимальный размер дампа памяти (в байтах), разрешенный для процесса. Значение 0 (ноль) предотвращает создание файла. Создание файла дампа остановится на этом пределе.
 */
