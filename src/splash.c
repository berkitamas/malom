/**
 * @file		splash.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 * 
 * @image 		html splash.png "Kezdőképernyő" width=100%
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "input.h"
#include "utils.h"
#include "splash.h"
#include "game.h"

void splash_init()
{
	game_loop(splash_update, splash_render);
}

void splash_update(input_t input, bool *running)
{
	if (input == INPUT_ENTER) *running = false;
	if (input == INPUT_CANCEL) exit_game(0);
}

void splash_render()
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
	char * gfx;
	int i;
	printf("\e[H\n\n");

	//Soronként beolvassa a malom grafikát, majd középre igazítja azt
	for (i = 0; i < 7; i++) {
		gfx = malloc((strlen(design[i]) + 1) * sizeof(char));
		strcpy(gfx, design[i]);
		center_align(&gfx);
		printf("%s\n", gfx);
		free(gfx);
	}
	gfx = malloc(screen_width() * sizeof(char));
	strcpy(gfx, "A folytatashoz nyomd meg az ENTER gombot!");
	center_align(&gfx);
	printf("\n\n\n\n\n\n%s", gfx);
	strcpy(gfx, "Berki Tamas - PDRE31");
	center_align(&gfx);
	printf("\n\n\n\n\n\n%s", gfx);
	free(gfx);
}