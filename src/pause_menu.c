/**
 * @file		pause_menu.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 04.
 *
 * @image 		html pause_menu.png "Szünet menü" width=100%
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "utils.h"
#include "pause_menu.h"

void pause_menu()
{
	/*
	███████████████████ Jatek szuneteltetve ███████████████████
	██                                                       ██
	██           Biztos ki akarsz lepni a fomenube?          ██
	██                                                       ██
	██                                                       ██
	██     ENTER - Igen                       ESC - Nem      ██
	██                                                       ██
	███████████████████████████████████████████████████████████
	*/
	const char * design[8] = {
		"\e[47m                   \e[0m Jatek szuneteltetve \e[47m                   \e[0m",
		"\e[47m  \e[0m                                                       \e[47m  \e[0m",
		"\e[47m  \e[0m           Biztos ki akarsz lepni a fomenube?          \e[47m  \e[0m",
		"\e[47m  \e[0m                                                       \e[47m  \e[0m",
		"\e[47m  \e[0m                                                       \e[47m  \e[0m",
		"\e[47m  \e[0m     ENTER - Igen                       ESC - Nem      \e[47m  \e[0m",
		"\e[47m  \e[0m                                                       \e[47m  \e[0m",
		"\e[47m                                                           \e[0m"
	};
	//Megpróbáljuk középre igazítani
	int posx = screen_width() / 2 - PAUSE_MENU_WIDTH / 2;
	int posy = screen_height() / 2 - PAUSE_MENU_HEIGHT / 2;
	int i;

	//Soronként lerendereljük a pozícióját figyelembe véve
	for (i = 0; i < PAUSE_MENU_HEIGHT; ++i) {
		printf("\e[%d;%dH%s", posy + i, posx, design[i]);
	}
}