/**
 * @file		winner_view.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 05.
 *
 * @image 		html winner_view.png "Győztes képernyő" width=100%
 *
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "input.h"
#include "element.h"
#include "piece.h"
#include "board.h"
#include "winner_view.h"
#include "game.h"

void winner_view_init()
{
	game_loop(winner_view_update, winner_view_render);
}

void winner_view_update(input_t input, bool *running)
{
	if (input == INPUT_ENTER) {
		*running = false;
		game_prev_view();
	}
	if (input == INPUT_CANCEL) {
		*running = false;
		game_next_view();
	}
}

void winner_view_render()
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
	printf("\n\n");
	const char *design2[] = {
		"                                                        __     ",
		"                                 ,-_                  (`  ).   ",
		"                                 |-_'-,              (     ).  " ,
		"                                 |-_'-'           _(        '`.",
		"                        _        |-_'/        .=(`(      .     )",
		"                       /;-,_     |-_'        (     (.__.:-`-_.' ",
		"                      /-.-;,-,___|'          `(       ) )       ",
		"                     /;-;-;-;_;_/|\\_ _ _ _ _   ` __.:'   )      ",
		"                        x_( __`|_P_|`-;-;-;,|        `--'       ",
		"                        |\\ \\    _||   `-;-;-'                   ",
		"                        | \\`   -_|.      '-'                    ",
		"                        | /   /-_| `                            ",
		"                        |/   ,'-_|  \\                           ",
		"                        /____|'-_|___\\                          ",
		"                 _..,____]__|_\\-_'|_[___,.._                    ",
		"                '                          ``'--,..,.      mic  "
	};

	for (i = 0; i < 16; i++) {
		gfx = malloc((strlen(design2[i]) + 1) * sizeof(char));
		strcpy(gfx, design2[i]);
		center_align(&gfx);
		printf("%s\n", gfx);
		free(gfx);
	}
	gfx = malloc(screen_width() * sizeof(char));
	if (board_winner() == PLAYER_1) strcpy(gfx, "1. jatekos nyert");
	if (board_winner() == PLAYER_2) strcpy(gfx, "2. jatekos nyert");
	center_align(&gfx);
	printf("\n%s", gfx);
	free(gfx);
	gfx = malloc(screen_width() * sizeof(char));
	strcpy(gfx, "Keszitette: Berki Tamas - PDRE31                                     ");
	center_align(&gfx);
	printf("\n\n\n\n%s", gfx);
	free(gfx);
}