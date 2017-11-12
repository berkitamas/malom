/**
 * @file		board.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 * 
 * @image 		html board.png "Tábla" width=100%
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "utils.h"
#include "input.h"
#include "piece.h"
#include "element.h"
#include "textbox.h"
#include "board.h"
#include "pause_menu.h"
#include "game.h"

static struct Board board; ///< A tábla tulajdonságait tartalmazó változó

void board_init()
{
	piece_init();
	//Ha valaki kilép a főmenübe, majd vissza, akkor nullázni kell mindent
	board.win = false;
	board.winner = 0;
	board.stage = STAGE_PLACE;
	board.remove_mode = false;
	board.move_mode = false;
	board.paused = false;
	board.moving_element = NULL;
	board.removable_pieces = 0;
	board.placed_pieces = 0;
	board.current_player = PLAYER_1;
	set_textbox_msg("Lerak: 1. jatekos");
	element_init();
	set_piece_element_relation();
	//board_debug();
	board.selected_element = piece(0)->element;
	board.selected_element->blink_frame = current_frame();
	game_loop(board_update, board_render);
}

void board_update(input_t input, bool *running)
{
	//Szüneteltetés esetében
	if (board.paused) {
		//Enter esetében kilép
		if (input == INPUT_ENTER) {
			*running = false;
			game_prev_view();
		//Cancel esetében visszatér a játékhoz
		} else if (input == INPUT_CANCEL) {
			board.paused = false;
		}
	} else { //Ha nem szünetel
		//Elem villogása
		if (check_interval(board.selected_element->blink_frame, BLINK_TIME)) {
			board.selected_element->blink_status = !board.selected_element->blink_status;
			board.selected_element->blink_frame = current_frame();
		}
		//Szünet gomb essetében szüneteltetés
		if (input == INPUT_PAUSE) {
			board.paused = true;
		}
		//Táblán való navigáció
		if (input == INPUT_UP) board_move_cursor(D_UP);
		else if (input == INPUT_DOWN) board_move_cursor(D_DOWN);
		else if (input == INPUT_LEFT) board_move_cursor(D_LEFT);
		else if (input == INPUT_RIGHT) board_move_cursor(D_RIGHT);

		//Ha malom lett kirakva
		if (board.remove_mode) {
			if (input == INPUT_ENTER) {
				enum PieceStatus status = board.selected_element->piece->status;
						//Csak a másik bábuját lehet levenni
				if ((	(board.current_player == PLAYER_1 && status == P_P2) ||
						(board.current_player == PLAYER_2 && status == P_P1)
					) &&
						//Bábu nincs malomban, vagy a játékos összes bábuja malomban van
					(	!board_check_mill(board.selected_element->piece) ||
						((board.current_player == PLAYER_1 && board_check_all_mill_player(PLAYER_2)) ||
						(board.current_player == PLAYER_2 && board_check_all_mill_player(PLAYER_1))))
					) {
					board.selected_element->piece->status = P_EMPTY;
					board.selected_element->status = E_EMPTY;
					board.removable_pieces--;
				} else {
					set_textbox_error("Babut nem lehet levenni");
				}
			}
			//Ha cancelt nyom, akkor nem vesz le egy bábut sem
			if (input == INPUT_CANCEL) {
				board.removable_pieces--;
			}
			//Ha nincs több levehető bábu, akkor kilép a malomból
			if (!board.removable_pieces) {
				if (board.placed_pieces >= 18) {
					board.stage = STAGE_MOVE;
					board_check_win(running);
				}
				if (board.current_player == PLAYER_1) {
					board.current_player = PLAYER_2;
					if (board.stage == STAGE_PLACE) set_textbox_msg("Lerak: 2. jatekos");
					if (board.stage == STAGE_MOVE) set_textbox_msg("Mozgat: 2. jatekos");
				} else if (board.current_player == PLAYER_2) {
					board.current_player = PLAYER_1;
					if (board.stage == STAGE_PLACE) set_textbox_msg("Lerak: 1. jatekos");
					if (board.stage == STAGE_MOVE) set_textbox_msg("Mozgat: 1. jatekos");
				}
				board.selected_element = piece(0)->element;
				board.selected_element->blink_frame = current_frame();
				board.selected_element->blink_status = false;
				board.remove_mode = false;
			}
		} else {
			if (board.stage == STAGE_PLACE) { //Lerakás
				if (input == INPUT_ENTER) {
					if (board.selected_element->piece->status == P_EMPTY) {
						board_place_piece();
						board.removable_pieces = board_check_mill(board.selected_element->piece);
						//Kettő malom kialakulhat egyszerre
						if (board.removable_pieces) {
							if (board.removable_pieces == 1) set_textbox_msg("Vegyel le egy babut");
							//Kettőnél több malom nem alakulhat ki egyszerre
							else  set_textbox_msg("Vegyel le ket babut");
							board.remove_mode = true;
						} else {
							if (board.placed_pieces >= 18) {
								board_check_win(running);
								board.stage = STAGE_MOVE;
								board.current_player = PLAYER_1;
								set_textbox_msg("Mozgat: 1. jatekos");
							} else {
								if (board.current_player == PLAYER_1) {
									board.current_player = PLAYER_2;
									set_textbox_msg("Lerak: 2. jatekos");
								} else if (board.current_player == PLAYER_2) {
									board.current_player = PLAYER_1;
									set_textbox_msg("Lerak: 1. jatekos");
								}
							}
						}
						board.selected_element = piece(0)->element;
						board.selected_element->blink_frame = current_frame();
						board.selected_element->blink_status = false;
					} else {
						set_textbox_error("A hely mar foglalt");
					}
				}
			} else if (board.stage == STAGE_MOVE) { //Mozgatás
				//Ebbe a blokkba akkor lép ba, ha már kiválasztotta a mozgatni kívánt bábut
				if (board.move_mode) {
					if (input == INPUT_ENTER) {
						if (piece_can_move_here(	board.moving_element->piece,
													board.selected_element->piece)) {
							board.selected_element->status = board.moving_element->status;
							board.selected_element->piece->status = board.moving_element->piece->status;
							board.moving_element->status = E_EMPTY;
							board.moving_element->piece->status = P_EMPTY;
							if (board_check_mill(board.selected_element->piece)) {
								set_textbox_msg("Vegyel le egy babut");
								//Masodik reszben csak egy malom alakulhat ki egyszerre
								board.removable_pieces = 1;
								board.remove_mode = true;
							} else {
								//Lehet olyan eset, hogy az egyik játékos nem tud mozogni, akkor az veszített
								board_check_win(running);
								if (board.current_player == PLAYER_1) {
									board.current_player = PLAYER_2;
									set_textbox_msg("Mozgat: 2. jatekos");
								} else if (board.current_player == PLAYER_2) {
									board.current_player = PLAYER_1;
									set_textbox_msg("Mozgat: 1. jatekos");
								}
							}
							board.selected_element = piece(0)->element;
							board.selected_element->blink_frame = current_frame();
							board.selected_element->blink_status = false;
							board.move_mode = false;
						} else {
							set_textbox_error("Nem mozgathatod ide a babut");
						}
					//Mégssem ezt akarta a felhasználó, újra kiválasztja az elemet
					} else if (input == INPUT_CANCEL) {
						board.move_mode = false;
						board.moving_element = NULL;
					}
				} else {
					if (input == INPUT_ENTER) {
						if ((board.current_player == PLAYER_1 && board.selected_element->piece->status == P_P1) ||
								(board.current_player == PLAYER_2 && board.selected_element->piece->status == P_P2)) {
							if (piece_can_move(board.selected_element->piece)) {
								board.moving_element = board.selected_element;
								board.move_mode = true;
							} else {
								set_textbox_error("Babu nem mozgathato");
							}
						} else {
							set_textbox_error("Sajat babut valassz");
						}
					}
				}
			}
		}
	}
}

enum Player board_winner()
{
	return board.winner;
}

void board_debug() {
	piece(1)->status = P_P2;
	piece(1)->element->status = E_P2;
	piece(2)->status = P_P1;
	piece(2)->element->status = E_P1;
	piece(3)->status = P_P1;
	piece(3)->element->status = E_P1;
	piece(4)->status = P_P2;
	piece(4)->element->status = E_P2;
	piece(5)->status = P_P1;
	piece(5)->element->status = E_P1;
	piece(6)->status = P_P2;
	piece(6)->element->status = E_P2;
	piece(7)->status = P_P2;
	piece(7)->element->status = E_P2;
	piece(8)->status = P_P1;
	piece(8)->element->status = E_P1;
	piece(10)->status = P_P2;
	piece(10)->element->status = E_P2;
	piece(12)->status = P_P2;
	piece(12)->element->status = E_P2;
	piece(13)->status = P_P2;
	piece(13)->element->status = E_P2;
	piece(15)->status = P_P1;
	piece(15)->element->status = E_P1;
	piece(18)->status = P_P2;
	piece(18)->element->status = E_P2;
	piece(14)->status = P_P2;
	piece(14)->element->status = E_P2;
	board.placed_pieces = 18;
	board.current_player = PLAYER_2;
	board.stage = STAGE_MOVE;
}

void board_check_win(bool *running)
{
	//Tud-e valaki mozogni
	int move_p1 = 0, move_p2 = 0, i;
	for (i = 0; i < PIECE_COUNT; i++) {
		if (piece_can_move(piece(i))) {
			if (piece(i)->status == P_P1) move_p1++;
			if (piece(i)->status == P_P2) move_p2++;
		}
	}

	if (board.current_player == PLAYER_1) {
		if (count_pieces_with_status(P_P2) < 3) {
			board.win = true;
			board.winner = PLAYER_1;
			*running = false;
			return;
		}
		//P2 nem tud mozogni
		if (!move_p2) {
			board.win = true;
			board.winner = PLAYER_1;
			*running = false;
			return;
		}
	} else if (board.current_player == PLAYER_2) {
		//2 vagy kevesebb bábu
		if (count_pieces_with_status(P_P1) < 3) {
			board.win = true;
			board.winner = PLAYER_2;
			*running = false;
			return;
		}
		//P1 nem tud mozogni
		if (!move_p1) {
			board.win = true;
			board.winner = PLAYER_2;
			*running = false;
			return;
		}
	}
}

int count_pieces_with_status(enum PieceStatus p)
{
	int counter = 0, i;
	for (i = 0; i < PIECE_COUNT; ++i) {
		if (piece(i)->status == p) counter++;
	}
	return counter;
}

bool piece_can_move_here(struct Piece *from, struct Piece *to)
{
	if (to->status == P_EMPTY) {
		//3-nál bárhova léphet
		if (count_pieces_with_status(from->status) <= 3) return true;

		//Ha több, mint 3 van neki, akkor csak a szomszédos területre
		if (from->left_piece == to) return true;
		else if (from->right_piece == to) return true;
		else if (from->top_piece == to) return true;
		else if (from->bottom_piece == to) return true;
		else return false;
	} else return false; //Ha foglalt a hely, ahova lépni szeretne
}

bool piece_can_move(struct Piece *p)
{
	if (p->status != P_P1 && p->status != P_P2) return false; //Hibás bemenő adat
	if (count_pieces_with_status(p->status) <=  3) return true;
	//Ha több, mint 3 van neki, akkor csak a szomszédos területre
	if (p->left_piece && p->left_piece->status == P_EMPTY) return true;
	else if (p->right_piece && p->right_piece->status == P_EMPTY) return true;
	else if (p->top_piece && p->top_piece->status == P_EMPTY) return true;
	else if (p->bottom_piece && p->bottom_piece->status == P_EMPTY) return true;
	return false;
}

bool board_check_all_mill_player(enum Player player)
{
	enum PieceStatus p;
	if (player == PLAYER_1) p = P_P1;
	else if (player == PLAYER_2) p = P_P2;
	else p = P_EMPTY;
	int i;
	for (i = 0; i < PIECE_COUNT; ++i)
		if (piece(i)->status == p && board_check_mill(piece(i)) == 0)
			return false;

	return true;
}

int board_check_mill(struct Piece *p)
{
	enum PieceStatus status = p->status;

	if (status == P_EMPTY) return 0;

	int rem = 0;

	if (p->left_piece && p->left_piece->status == status)
		if (	(p->left_piece->left_piece && p->left_piece->left_piece->status == status) ||
				(p->right_piece && p->right_piece->status == status))
			rem++;
	if (p->right_piece && p->right_piece->status == status)
		if (	(p->right_piece->right_piece && p->right_piece->right_piece->status == status))
			rem++;
	if (p->top_piece && p->top_piece->status == status)
		if (	(p->top_piece->top_piece && p->top_piece->top_piece->status == status) ||
				(p->bottom_piece && p->bottom_piece->status == status))
			rem++;
	if (p->bottom_piece && p->bottom_piece->status == status)
		if (	(p->bottom_piece->bottom_piece && p->bottom_piece->bottom_piece->status == status))
			rem++;
	return rem;
}

void board_place_piece()
{
	if (board.current_player == PLAYER_1) {
		board.selected_element->piece->status = P_P1;
		board.selected_element->status = E_P1;
	} else {
		board.selected_element->piece->status = P_P2;
		board.selected_element->status = E_P2;
	}
	board.placed_pieces++;
}

void board_move_cursor(enum Direction d)
{
	if (d == D_UP && board.selected_element->piece->top_piece)
		board.selected_element = board.selected_element->piece->top_piece->element;
	else if (d == D_DOWN && board.selected_element->piece->bottom_piece)
		board.selected_element = board.selected_element->piece->bottom_piece->element;
	else if (d == D_LEFT && board.selected_element->piece->left_piece)
		board.selected_element = board.selected_element->piece->left_piece->element;
	else if (d == D_RIGHT && board.selected_element->piece->right_piece)
		board.selected_element = board.selected_element->piece->right_piece->element;
	board.selected_element->blink_frame = current_frame();
	board.selected_element->blink_status = false;
}

void board_render()
{
	if (board.paused) {
		pause_menu();
	} else {
		char *output = malloc(screen_width() * screen_height() * 5 * sizeof(char));
		int i;

		output[0] = '\0';

		if (screen_width() < MIN_COLUMNS + (TEXTBOX_OFFSET + TEXTBOX_WIDTH ) * 2 + 3) {
			strcat(output, "\e[0m\n");
			for (i = 0; i < TEXTBOX_HEIGHT; i++) {
				char *textbox_row = malloc(TEXTBOX_WIDTH * 5);
				textbox_row[0] = 0;
				draw_textbox(textbox_row, i);
				center_align(&textbox_row);
				strcat(output, textbox_row);
				strcat(output, "\e[0m\n");
				free(textbox_row);
			}
			strcat(output, "\e[0m\n");
		}



		for (i = 0; i < ELEMENT_ROW; ++i) {
			draw_row(output, i);
			if (i < TEXTBOX_HEIGHT && screen_width() >= MIN_COLUMNS + (TEXTBOX_OFFSET + TEXTBOX_WIDTH ) * 2 + 3) {
				strcat(output, "   ");
				draw_textbox(output, i);
			}
			if(i != ELEMENT_ROW - 1) strcat(output, "\e[0m\n");
			else strcat(output, "\e[0m");
		}

		printf("\e[H%s", output);

		free(output);
	}

}

void set_piece_element_relation()
{
	piece(0)->element = element(1, 0);
	piece(1)->element = element(1, 6);
	piece(2)->element = element(1, 12);
	piece(3)->element = element(7, 2);
	piece(4)->element = element(7, 6);
	piece(5)->element = element(7, 10);
	piece(6)->element = element(13, 4);
	piece(7)->element = element(13, 6);
	piece(8)->element = element(13, 8);
	piece(9)->element = element(19, 0);
	piece(10)->element = element(19, 2);
	piece(11)->element = element(19, 4);
	piece(12)->element = element(19, 8);
	piece(13)->element = element(19, 10);
	piece(14)->element = element(19, 12);
	piece(15)->element = element(25, 4);
	piece(16)->element = element(25, 6);
	piece(17)->element = element(25, 8);
	piece(18)->element = element(31, 2);
	piece(19)->element = element(31, 6);
	piece(20)->element = element(31, 10);
	piece(21)->element = element(37, 0);
	piece(22)->element = element(37, 6);
	piece(23)->element = element(37, 12);

	element(1, 0)->piece = piece(0);
	element(1, 6)->piece = piece(1);
	element(1, 12)->piece = piece(2);
	element(7, 2)->piece = piece(3);
	element(7, 6)->piece = piece(4);
	element(7, 10)->piece = piece(5);
	element(13, 4)->piece = piece(6);
	element(13, 6)->piece = piece(7);
	element(13, 8)->piece = piece(8);
	element(19, 0)->piece = piece(9);
	element(19, 2)->piece = piece(10);
	element(19, 4)->piece = piece(11);
	element(19, 8)->piece = piece(12);
	element(19, 10)->piece = piece(13);
	element(19, 12)->piece = piece(14);
	element(25, 4)->piece = piece(15);
	element(25, 6)->piece = piece(16);
	element(25, 8)->piece = piece(17);
	element(31, 2)->piece = piece(18);
	element(31, 6)->piece = piece(19);
	element(31, 10)->piece = piece(20);
	element(37, 0)->piece = piece(21);
	element(37, 6)->piece = piece(22);
	element(37, 12)->piece = piece(23);
}

void draw_element(char *output, int row, int col)
{
	element_t *element_p = element(row, col);
	if (element_p->status == E_STATIC) {
		switch (element_p->type) {
		case 'a':
			strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_BLOCK_FG BOARD_BLOCK_FG BOARD_BG);
			break;
		case 'b':
			strcat(output, BOARD_BG BOARD_BLOCK_BG BOARD_BLOCK_BG BOARD_BLOCK_BG);
			break;
		case 'c':
			strcat(output, BOARD_BG BOARD_BLOCK_BG BOARD_FG BOARD_BLOCK_FG BOARD_BG BOARD_BLOCK_BG);
			break;
		}
	} else {
		if (element_p->status == E_P1) {
			if (element_p == board.selected_element) {
				if (element_p->blink_status) {
					strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_SELECT BOARD_BLOCK_SELECT BOARD_FG BOARD_BLOCK_FG);
				} else {
					strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_P1 BOARD_BLOCK_SELECT BOARD_FG BOARD_BLOCK_FG);
				}
			} else if (element_p == board.moving_element) {
				strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_P1 BOARD_BLOCK_MOVING BOARD_FG BOARD_BLOCK_FG);
			} else {
				strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_P1 BOARD_BLOCK_BG BOARD_FG BOARD_BLOCK_FG);
			}
		} else if (element_p->status == E_P2) {
			if (element_p == board.selected_element) {
				if (element_p->blink_status) {
					strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_SELECT BOARD_BLOCK_SELECT BOARD_FG BOARD_BLOCK_FG);
				} else {
					strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_P2 BOARD_BLOCK_SELECT BOARD_FG BOARD_BLOCK_FG);
				}
			} else if (element_p == board.moving_element) {
				strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_P2 BOARD_BLOCK_MOVING BOARD_FG BOARD_BLOCK_FG);
			} else {
				strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_P2 BOARD_BLOCK_BG BOARD_FG BOARD_BLOCK_FG);
			}
		} else {
			if (element_p == board.selected_element) {
				if (element_p->blink_status) {
					strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_BG BOARD_BLOCK_BG BOARD_FG BOARD_BLOCK_FG);
				} else {
					strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_SELECT BOARD_BLOCK_SELECT BOARD_FG BOARD_BLOCK_FG);
				}
			} else {
				strcat(output, BOARD_FG BOARD_BLOCK_FG BOARD_EMPTY BOARD_BLOCK_BG BOARD_FG BOARD_BLOCK_FG);
			}
		}
	}
}

void draw_row(char *output, int row)
{
	int i = 0;
	char *elements = malloc(ELEMENT_ROW * 3 * 5 * sizeof(char));

	elements[0] = 0;

	for (i = 0; i < ELEMENT_COLUMN; ++i) {
		draw_element(elements, row, i);
	}

	center_align(&elements);

	strcat(output, elements);
	strcat(output, BOARD_BG);

	free(elements);
}