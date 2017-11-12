/**
 * @file		textbox.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 * 
 * @image 		html textbox.png "Szövegdoboz" width=200px
 * @image 		html textbox_error.png "Szövegdoboz hibánál" width=200px
 * 
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "textbox.h"

static char *textbox_msg;  ///< A textbox üzenete
static bool error; ///< Az aktuális üzenetet hibaként jelenítse-e meg?

void set_textbox_msg(char *msg)
{
	if (strlen(msg) >= 128) return;
	error = false;
	free(textbox_msg);
	textbox_msg = malloc(128 * sizeof(char));
	strcpy(textbox_msg, msg);
}

void set_textbox_error(char *msg)
{
	if (strlen(msg) >= 128) return;
	error = true;
	free(textbox_msg);
	textbox_msg = malloc(128 * sizeof(char));
	strcpy(textbox_msg, msg);
}

void draw_textbox(char *str, int row)
{
	/*
	██████████████████████████████
	██       M  A  L  O  M      ██
	██████████████████████████████

	██████████████████████████████
	██                          ██
	██ Következő: első játékos  ██
	██                          ██
	█████Berki Tamas - PDRE31█████
	*/

	char *output = malloc(TEXTBOX_WIDTH * TEXTBOX_WIDTH);
	output[0] = '\0';

	char *design[TEXTBOX_HEIGHT + 1] = {
		"\e[47m                              \e[0m",
		"\e[47m        \e[1mM  A  L  O  M\e[0m\e[47m         \e[0m",
		"\e[47m                              \e[0m",
		"                              ",
		"\e[47m                              \e[0m",
		"\e[47m  \x05                          \e[47m  \e[0m",
		"\e[47m  \x05 ",
		" \e[47m  \e[0m",
		"\e[47m  \x05                          \e[47m  \e[0m",
		"\e[47m     Berki Tamas - PDRE31     \e[0m"
	};

	int i, k;

	if (row > TEXTBOX_DYNAMIC_MSG) {
		row++;
		strcat(output, design[row]);
	} else if (row == TEXTBOX_DYNAMIC_MSG) {

		strcat(output, design[row]);

		if (strlen(textbox_msg) > TEXTBOX_WIDTH - 6) {
			char *msg_ellipsis = malloc((TEXTBOX_WIDTH - 5) * sizeof(char));
			memcpy(msg_ellipsis, textbox_msg, TEXTBOX_WIDTH - 9);
			msg_ellipsis[TEXTBOX_WIDTH - 9] = '\0';
			strcat(msg_ellipsis, "...");
			strcat(output, msg_ellipsis);
			free(msg_ellipsis);
		} else if (strlen(textbox_msg) < TEXTBOX_WIDTH - 6) {
			strcat(output, textbox_msg);
			int i;
			for (i = 0; i < TEXTBOX_WIDTH - 6 - strlen(textbox_msg); ++i) {
				strcat(output, " ");
			}
		} else {
			strcat(output, textbox_msg);
		}
		strcat(output, design[row + 1]);

	} else {
		strcat(output, design[row]);
	}

	for (i = 0; i < strlen(output); ++i) {
		if (output[i] == '\x05') {
			if (error) {
				for (k = strlen(output); k > i; --k)
					output[k + 13] = output[k];

				output[i++] = '\e';
				output[i++] = '[';
				output[i++] = '4';
				output[i++] = '1';
				output[i++] = ';';
				output[i++] = '1';
				output[i++] = 'm';
				output[i++] = '\e';
				output[i++] = '[';
				output[i++] = '3';
				output[i++] = '7';
				output[i++] = ';';
				output[i++] = '1';
				output[i++] = 'm';
			} else {
				for (k = strlen(output); k > i; --k)
					output[k + 3] = output[k];

				output[i++] = '\e';
				output[i++] = '[';
				output[i++] = '0';
				output[i++] = 'm';
			}
		}
	}

	strcat(str, output);
	free(output);
}