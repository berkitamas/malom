/**
 * @file		main_menu.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 *
 * @image 		html main_menu.png "Főmenü" width=100%
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "input.h"
#include "main_menu.h"
#include "game.h"

static mainmenu_t selected_item = MENU_2_PLAYER;  ///< A főmenü tulajdonságait tartalmazó változó

void main_menu_init()
{
	game_loop(main_menu_update, main_menu_render);
}

void main_menu_update(input_t input, bool *running)
{
	if (input == INPUT_UP) {
		//nem a legfölső elem
		if (selected_item != MENU_2_PLAYER) {
			selected_item--; //mivel enum
		}
	}
	if (input == INPUT_DOWN) {
		//nem a legalsó elem
		if (selected_item != MENU_QUIT_GAME) {
			selected_item++;
		}
	}
	if (input == INPUT_CANCEL) {
		*running = false;
		game_prev_view();
	}
	if (input == INPUT_ENTER) {
		switch (selected_item) {
		case MENU_2_PLAYER:
			set_game_mode(GAME_2_PLAYER);
			*running = false;
			break;
		case MENU_QUIT_GAME:
			exit_game(0);
			break;
		}
	}
}

void main_menu_render()
{
	/*
	██       ███      ████      ██          ██████████████  ███      ███
	██ █    █ ██    ██    ██    ██          ██    ██    ██  ██ █    █ ██
	██  █  █  ██  ██        ██  ██          ██  ██████  ██  ██  █  █  ██
	██   ██   ██  ██        ██  ██          ██████  ██████  ██   ██   ██
	██        ██  ████████████  ██          ██  ██████  ██  ██        ██
	██        ██  ██        ██  ██          ██    ██    ██  ██        ██
	██        ██  ██        ██  ██████████  ██████████████  ██        ██
	*/
	const char *design[] = {
		"\e[0m\e[7m   \e[0m      \e[0m\e[7m   \e[0m      \e[0m\e[7m    \e[0m      \
\e[0m\e[7m  \e[0m          \e[0m\e[7m              \e[0m  \e[0m\e[7m   \e[0m      \e[0m\e[7m   \e[0m",
		"\e[0m\e[7m  \e[0m \e[0m\e[7m \e[0m    \e[0m\e[7m \e[0m \e[0m\e[7m  \e[0m    \e[0m\e[7m  \e[0m    \
\e[0m\e[7m  \e[0m    \e[0m\e[7m  \e[0m          \e[0m\e[7m  \e[0m    \e[0m\e[7m  \e[0m    \e[0m\
\e[7m  \e[0m  \e[0m\e[7m  \e[0m \e[0m\e[7m \e[0m    \e[0m\e[7m \e[0m \e[0m\e[7m  \e[0m",
		"\e[0m\e[7m  \e[0m  \e[0m\e[7m \e[0m  \e[0m\e[7m \e[0m  \e[0m\e[7m  \e[0m  \e[0m\e[7m  \e[0m        \
\e[0m\e[7m  \e[0m  \e[0m\e[7m  \e[0m          \e[0m\e[7m  \e[0m  \e[0m\e[7m      \e[0m  \e[0m\e[7m  \
\e[0m  \e[0m\e[7m  \e[0m  \e[0m\e[7m \e[0m  \e[0m\e[7m \e[0m  \e[0m\e[7m  \e[0m",
		"\e[0m\e[7m  \e[0m   \e[0m\e[7m  \e[0m   \e[0m\e[7m  \e[0m  \e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m  \
\e[0m\e[7m  \e[0m          \e[0m\e[7m      \e[0m  \e[0m\e[7m      \e[0m  \e[0m\e[7m  \e[0m   \e[0m\
\e[7m  \e[0m   \e[0m\e[7m  \e[0m",
		"\e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m  \e[0m\e[7m            \e[0m  \e[0m\e[7m  \e[0m          \
\e[0m\e[7m  \e[0m  \e[0m\e[7m      \e[0m  \e[0m\e[7m  \e[0m  \e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m",
		"\e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m  \e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m  \e[0m\e[7m  \
\e[0m          \e[0m\e[7m  \e[0m    \e[0m\e[7m  \e[0m    \e[0m\e[7m  \e[0m  \e[0m\e[7m  \e[0m        \
\e[0m\e[7m  \e[0m",
		"\e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m  \e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m  \e[0m\
\e[7m          \e[0m  \e[0m\e[7m              \e[0m  \e[0m\e[7m  \e[0m        \e[0m\e[7m  \e[0m",
	};
	/*

	|  2 játékos                  |
	|  Kilépés a játékból         |

	*/
	const char *menu_items[] = {
		"2 jatekos",
		"Kilepes a jatekbol",
	};
	char *gfx;
	int i;
	printf("\e[H\n\n");
	//Soronként beolvassa a malom grafikát, majd középre igazítja azt
	for (i = 0; i < 7; i++) {
		gfx = malloc(strlen(design[i]) * sizeof(char) * screen_width());
		strcpy(gfx, design[i]);
		center_align(&gfx);
		printf("%s\n", gfx);
		free(gfx);
	}
	printf("\n\n\n\n\n\n");

	//Soronként beolvassa a menüpontokat, egy fix szélességre egészíti ki, színt ad hozzá, majd középre igazítja
	//és kiíratja
	for (i = 0; i < 2 ; i++) {
		gfx = malloc(MAIN_MENU_WIDTH * sizeof(char) * screen_width());
		gfx[0] = 0;
		if (selected_item == i) strcat(gfx, "\e[0m\e[7m");
		strcat(gfx, "  ");
		strcat(gfx, menu_items[i]);

		//A két escape character nem jelenik meg a terminálban, viszont az strlennél igen
		int len = (selected_item == i) ? strlen(gfx) - 8 : strlen(gfx);
		while (len < MAIN_MENU_WIDTH) {
			strcat(gfx, " ");
			len++;
		}
		if (selected_item == i) strcat(gfx, "\e[0m");
		center_align(&gfx);
		printf("%s\n", gfx);
		free(gfx);
	}
	gfx = malloc(screen_width() * sizeof(char));
	strcpy(gfx, "Berki Tamas - PDRE31");
	center_align(&gfx);
	printf("\n\n\n\n%s", gfx);
	free(gfx);
}