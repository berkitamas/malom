/**
 * @file		utils.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 10. 16.
 */

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"
#include "input.h"
#include "game.h"

int screen_width()
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	return w.ws_col;
}

int screen_height()
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	return w.ws_row;
}

/**
*
* Ennek a szükségessége az strlennél jön elő, hisz az a bájtszámot fogja megszámolni
* (ezért nem érdemes ékezetet használni, hisz azokat több bájton tároljuk el). Magának a függvénynek a középre igazításnál
* van fontos szerepe.
*
*/
int str_visible_len(char * str)
{
	int len = strlen(str);
	int i, k;
	for (i = 0; str[i + 2] != '\0'; i++) {
		if (str[i] == '\e') {
			for (k = i + 1; str[k] != '\0'; k++) {
				len--;
				if (str[k] == '\e') {
					break;
				}
				if (str[k] == 'm') {
					len--;
					break;
				}
			}
		}
	}
	return len;
}

void center_align(char ** str)
{
	if (!strlen(*str)) return;

	char *tmp_str = malloc(strlen(*str) * screen_width()); // egy sor hosszabb
	int len = str_visible_len(*str);

	if (len >= screen_width() - 1) {
		free(tmp_str);
		return;
	}


	int offset = screen_width() / 2 - len / 2, i;

	tmp_str[0] = 0;

	for (i = 0; i < offset; i++) {
		strcat(tmp_str, " ");
	}
	strcat(tmp_str, *str);
	free(*str);
	*str = tmp_str;
}

clock_t current_frame()
{
	return (clock_t) (clock() * FPS / CLOCKS_PER_SEC);
}

bool check_interval(int frame, int ms)
{
	return (frame + ms * FPS / 1000) < current_frame();
}

void clear_screen()
{
	int i;
	char line[2048];

	printf("\e[H");

	for (i = 0; i <= screen_width(); i++) {
		line[i] = ' ';
	}
	line[i] = '\0';

	for (i = 1; i <= screen_height(); i++) {
		printf("\e[0m%s\n", line);
	}

}

void termios_changemode(int dir)
{
	static struct termios oldt, newt;

	if ( dir == 1 ) {
		tcgetattr( STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~( ICANON | ECHO );
		tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	} else {
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	}
}

bool kbhit (void)
{
	struct timeval tv;
	fd_set rdfs;

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO(&rdfs);
	FD_SET (STDIN_FILENO, &rdfs);

	select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
}