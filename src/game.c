/**
 * @file		game.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <time.h>

#include "utils.h"
#include "input.h"
#include "textbox.h"
#include "piece.h"
#include "element.h"
#include "splash.h"
#include "main_menu.h"
#include "board.h"
#include "winner_view.h"
#include "game.h"

static struct Game game; ///< A játék tulajdonságait tartalmazó változó

void game_init()
{
	if (!validate_dimensions()) return;
	set_signal_handler();
	game.current_view = VIEW_SPLASH;
	set_terminal_mode();
	splash_init();
}

void int_handler(int sig)
{
	exit_game(0);
}

void set_terminal_mode()
{
	termios_changemode(1);
	printf("\e[?25l\e[?47h");
	clear_screen();
}

void restore_terminal_mode()
{
	termios_changemode(0);
	printf("\e[?47l\e[?25h");
}

void set_signal_handler()
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, int_handler);
	signal(SIGTERM, int_handler);
}

bool validate_dimensions()
{

	//Ebbben az esetben a textbox a jobb oldalra kerül, így elég kisebb magasság is
	if (screen_width() < MIN_COLUMNS + (TEXTBOX_OFFSET + TEXTBOX_WIDTH ) * 2 + 3 && screen_height() < MIN_ROWS + TEXTBOX_OFFSET + TEXTBOX_HEIGHT + 6) {
		fprintf(stderr, "Az ablaknak minimum %d magasnak vagy %d szelesnek kell lenni!\n",
				MIN_ROWS + TEXTBOX_OFFSET + TEXTBOX_HEIGHT + 6,
				(MIN_COLUMNS + (TEXTBOX_OFFSET + TEXTBOX_WIDTH ) * 2 + 3)
			   );
		return false;
	} else if (screen_width() < MIN_COLUMNS) {
		fprintf(stderr, "Az ablaknak minimum %d szelesnek kell lenni!\n", MIN_COLUMNS);
		return false;
	} else if (screen_height() < MIN_ROWS) {
		fprintf(stderr, "Az ablaknak minimum %d magasnak kell lenni!\n", MIN_ROWS);
		return false;
	}

	return true;
}

void game_next_view()
{
	switch (game.current_view) {
	case VIEW_SPLASH:
		game.current_view = VIEW_MAIN_MENU;
		main_menu_init();
		break;
	case VIEW_MAIN_MENU:
		game.current_view = VIEW_BOARD;
		board_init();
		break;
	case VIEW_BOARD:
		game.current_view = VIEW_WINNER;
		winner_view_init();
		break;
	default:
		exit_game(0);
		break;
	}
}

void game_prev_view()
{
	switch (game.current_view) {
	case VIEW_MAIN_MENU:
		game.current_view = VIEW_SPLASH;
		splash_init();
		break;
	case VIEW_BOARD:
		game.current_view = VIEW_MAIN_MENU;
		main_menu_init();
		break;
	//Újrakezdi az egészer
	case VIEW_WINNER:
		game.current_view = VIEW_SPLASH;
		splash_init();
		break;
	default:
		exit_game(0);
		break;
	}
}

void set_game_mode(enum GameMode mode)
{
	game.mode = mode;
}

void game_loop(void (*update)(input_t input, bool *running), void (*render)())
{
	bool running = true;
	clock_t frame = current_frame();
	input_t input;
	clear_screen();
	int orig_scr_w = screen_width(), orig_scr_h = screen_height();
	while (running) {
		//Túlcsordulás ellen egy kis apróság
		if (current_frame() > frame || frame - current_frame() > 1000000) {
			input = input_process();
			update(input, &running);
			if (orig_scr_w != screen_width() || orig_scr_h != screen_height()) {
				clear_screen();
				orig_scr_w = screen_width();
				orig_scr_h = screen_height();
				assert(!(screen_width() < MIN_COLUMNS + (TEXTBOX_OFFSET + TEXTBOX_WIDTH ) * 2 + 3 && screen_height() < MIN_ROWS + TEXTBOX_OFFSET + TEXTBOX_HEIGHT + 6));
				assert(!(screen_width() < MIN_COLUMNS));
				assert(!(screen_height() < MIN_ROWS));
			}
			render();
			frame = current_frame();
		}
	}
	game_next_view();
}

void exit_game(int ret)
{
	restore_terminal_mode();
	exit(ret);
	assert(false);
}