/**
 * @file		input.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "utils.h"
#include "input.h"
#include "game.h"

input_t input_process()
{
	if (kbhit()) {
		int key = getchar();
		//Interrupt keyek
		if (key == 3 || key == 4 || key == 113) {
			exit_game(0);
		}
		//iránygombok
		//Az iránygombok karaktersorozatok, aminek az utolsó (3.) eleme adja az irányt
		if (key == 27 && getchar() == 91) {
			key = getchar();
			switch (key) {
			case 65: return INPUT_UP;
			case 66: return INPUT_DOWN;
			case 67: return INPUT_RIGHT;
			case 68: return INPUT_LEFT;
			}
		}
		//enter
		if (key == 10) {
			return INPUT_ENTER;
		}

		//pause
		if (key == 32) {
			return INPUT_PAUSE;
		}

		//escape
		if (key == 27) {
			return INPUT_CANCEL;
		}

	}
	return NO_INPUT;
}