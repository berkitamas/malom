/**
 * @file		piece.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */
#include <stdlib.h>

#include "piece.h"

static piece_t pieces[PIECE_COUNT];  ///< A bábuk tulajdonságait tartalmazó változó

piece_t *piece(int pos)
{
	if (pos < 0 || pos > PIECE_COUNT - 1) {
		return NULL;
	}
	return &pieces[pos];
}

void piece_init()
{
	set_pieces_relations();
}

void set_pieces_relations()
{
	int i;
	for (i = 0; i < PIECE_COUNT; ++i) {
		pieces[i].status = P_EMPTY;
	}
	pieces[0].top_piece = NULL;
	pieces[1].top_piece = NULL;
	pieces[2].top_piece = NULL;
	pieces[3].top_piece = NULL;
	pieces[5].top_piece = NULL;
	pieces[6].top_piece = NULL;
	pieces[8].top_piece = NULL;

	pieces[0].left_piece = NULL;
	pieces[9].left_piece = NULL;
	pieces[21].left_piece = NULL;
	pieces[3].left_piece = NULL;
	pieces[18].left_piece = NULL;
	pieces[6].left_piece = NULL;
	pieces[15].left_piece = NULL;

	pieces[15].bottom_piece = NULL;
	pieces[17].bottom_piece = NULL;
	pieces[18].bottom_piece = NULL;
	pieces[20].bottom_piece = NULL;
	pieces[21].bottom_piece = NULL;
	pieces[22].bottom_piece = NULL;
	pieces[23].bottom_piece = NULL;

	pieces[8].right_piece = NULL;
	pieces[17].right_piece = NULL;
	pieces[5].right_piece = NULL;
	pieces[20].right_piece = NULL;
	pieces[2].right_piece = NULL;
	pieces[14].right_piece = NULL;
	pieces[23].right_piece = NULL;

	pieces[9].top_piece = pieces[1].left_piece = &pieces[0];
	pieces[4].top_piece = pieces[2].left_piece = pieces[0].right_piece = &pieces[1];
	pieces[14].top_piece = pieces[1].right_piece = &pieces[2];

	pieces[10].top_piece = pieces[4].left_piece = &pieces[3];
	pieces[7].top_piece = pieces[5].left_piece = pieces[1].bottom_piece = pieces[3].right_piece = &pieces[4];
	pieces[13].top_piece = pieces[4].right_piece = &pieces[5];

	pieces[11].top_piece = pieces[7].left_piece = &pieces[6];
	pieces[8].left_piece = pieces[4].bottom_piece = pieces[6].right_piece = &pieces[7];
	pieces[12].top_piece = pieces[7].right_piece = &pieces[8];

	pieces[21].top_piece = pieces[10].left_piece = pieces[0].bottom_piece = &pieces[9];
	pieces[18].top_piece = pieces[11].left_piece = pieces[3].bottom_piece = pieces[9].right_piece = &pieces[10];
	pieces[15].top_piece = pieces[6].bottom_piece = pieces[10].right_piece = &pieces[11];

	pieces[17].top_piece = pieces[13].left_piece = pieces[8].bottom_piece = &pieces[12];
	pieces[20].top_piece = pieces[14].left_piece = pieces[5].bottom_piece = pieces[12].right_piece = &pieces[13];
	pieces[23].top_piece = pieces[2].bottom_piece = pieces[13].right_piece = &pieces[14];

	pieces[16].left_piece = pieces[11].bottom_piece = &pieces[15];
	pieces[19].top_piece = pieces[17].left_piece = pieces[15].right_piece = &pieces[16];
	pieces[12].bottom_piece = pieces[16].right_piece = &pieces[17];

	pieces[19].left_piece = pieces[10].bottom_piece = &pieces[18];
	pieces[22].top_piece = pieces[20].left_piece = pieces[16].bottom_piece = pieces[18].right_piece = &pieces[19];
	pieces[13].bottom_piece = pieces[19].right_piece = &pieces[20];

	pieces[22].left_piece = pieces[9].bottom_piece = &pieces[21];
	pieces[23].left_piece = pieces[19].bottom_piece = pieces[21].right_piece = &pieces[22];
	pieces[14].bottom_piece = pieces[22].right_piece = &pieces[23];
}