
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd;
	char ch;
	struct termios terminal;
	struct termios save_set; 

	//Получаем дескриптор файла, соответствующий терминальному устройству
	//Открытие его эквивалентно открытию управляющего терминала текущей сессии
	fd = open("/dev/tty", O_RDWR);
	//tcgetattr() получает текущие установки терминального устройства
	tcgetattr(fd, &terminal);
	save_set = terminal;
	//Поле c_lflag используется для управления обработкой строк
	//Запрос чтения не будет удовлетворен, пока не будет прочитано MIN символов
	//Значение MIN хранится в соответсвующей позиции массива c_cc[]
	terminal.c_lflag &= ~ICANON;
	//Массив c_cc определяет специальные управляющие символы
	//VMIN - Минимальное количество символов для неканонического ввода.
	terminal.c_cc[VMIN] = 1;
	//tcsetattr() изменяет установки терминального устройства
	//TCSANOW - установить атрибуты немедленно
	tcsetattr(fd, TCSANOW, &terminal);

	write(fd, "Enter some symbol: ", 19);	

	read(fd, &ch, 1);
	
	write(fd, "\nYou entered: ", 14);
	write(fd, &ch, 1);
	write(fd, "\n", 1);
	
	tcsetattr(fd, TCSAFLUSH, &save_set);
	
	return 0;
}