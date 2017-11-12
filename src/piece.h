/**
 * @file		piece.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 10. 16.
 */

#ifndef PIECE_H
#define PIECE_H

#define PIECE_COUNT 24 ///< Bábuk száma a táblán

/**
 * Bábuk státusza
 */
enum PieceStatus {
	P_EMPTY, /**< A ponton nincsen bábu. */
	P_P1, /**< A ponton az 1. játékos bábuja áll. */
	P_P2 /**< A ponton az 2. játékos bábuja áll. */
};


typedef struct Piece piece_t;
typedef struct Element element_t;

/**
 * @brief      A bábuk struktúrája
 */
struct Piece {
	enum PieceStatus status; ///< A pont státusza
	piece_t *left_piece; ///< A ponttól balra levő pontjának pointere
	piece_t *top_piece; ///< A ponttól fentebb levő pontjának pointere.
	piece_t *right_piece; ///< A ponttól jobbre levő pontjának pointere.
	piece_t *bottom_piece; ///< A ponttól lentebb levő pontjának pointere.
	element_t *element; ///< A bábuhoz kapcsolódó elem
};

/**
 * @brief      Továbbítja a megadott pozíció alapján a bábu pointerét
 *
 * @param[in]  pos   A pozíció
 *
 * @return     Az adott pozíción lévő bábu pointere
 */
piece_t *piece(int pos);

/**
 * @brief      Inicializálja a bábukat (pl. set_pieces_relations())
 */
void piece_init();

/**
 * @brief      Beállítja a logikai kapcsolatot a bábuk között.
 */
void set_pieces_relations();

#endif