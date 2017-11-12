/**
 * @file		board.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */


#ifndef BOARD_H
#define BOARD_H

#define BOARD_BG "\e[0m" ///< A táblában használt háttérszín (fehér)
#define BOARD_FG "\e[0m\e[7m" ///< A táblában használt előtérszín (fekete)
#define BOARD_EMPTY "\e[38;5;252m" ///< Az üres elem előtérszíne (szürke)
#define BOARD_P1 "\e[38;5;160m" ///< Az első játékos előtérszíne (piros)
#define BOARD_P2 "\e[38;5;38m" ///< A második játékos előtérszíne (kék)
#define BOARD_SELECT "\e[38;5;241m" ///< A kijelölt elem előtérszíne (sötétszürke)
#define BOARD_BLOCK_BG "  " ///< A blokk megjelenítésére használt karakter (háttér)
#define BOARD_BLOCK_FG "  " ///< A blokk megjelenítésére használt karakter (előtér)
#define BOARD_BLOCK_SELECT "[]"  ///< A kijelölt blokk megjelenítésére használt karakter
#define BOARD_BLOCK_MOVING "@@"  ///< A mozgatandó blokk megjelenítésére használt karakter

#define BLINK_TIME 500 ///< A táblában lévő animáció intervalluma miliszekundumban

/**
 * @brief      Irányt leíró enum
 *
 * Mozgásnál használjuk, pl board_move_cursor()
 *
 */
typedef enum Direction {
	D_UP, ///< Fel
	D_RIGHT,///< Jobbra
	D_DOWN,///< Le
	D_LEFT///< Balra
} dir_t;

/**
 * @brief      A játékosok enumja
 */
enum Player {
	PLAYER_1, ///< Első játékos
	PLAYER_2 ///< Második játékos
};

/**
 * @brief      A játszma részei
 */
enum BoardStage {
	STAGE_PLACE, ///< Bábuk lerakása
	STAGE_MOVE ///< Bábuk mozgatása
};

/**
 * @brief      A tábla tulajdonságai
 */
struct Board {
	bool win; ///<  Nyert-e valaki?
	enum Player winner; ///< Ki nyert?
	enum BoardStage stage; ///< A malom játéknak 2 része van, itt tároljuk, hogy melyik az aktuális
	bool remove_mode; ///< Akkor true, ha valaki malmot rakott ki, és az ellenfél bábuját akarja levenni
	bool move_mode; ///< A második részben az az állapot, amikor a játékos kijelölte a mozgatni kívánt bábut
	bool paused; ///< Le van-e állítva a játék?
	element_t *selected_element; ///< A kiválaszott elem
	element_t *moving_element; ///< A mozgatni kívánt elem
	/**
	 * Az játék első felében létrejöhet az az eset, hogy egyszerre két malmot rak ki a játékos
	 * Ebben az esetben annyi bábut vehet le, ahány malmot kirakott
	 * Ez a speciális eset csak az első részben lehetséges, és kettőnél több malom nem rakható ki egyszerre
	 */
	int removable_pieces; ///< A malom kirakása során levehető bábuk száma
	/**
	 * Ezt azért kell külön eltárolni, mert már az első részben fennállhat az az eset, hogy
	 * valaki malmot rak ki, és levesz az ellenfél bábui közül egyet, szóval kevesebb bábu
	 * lesz a táblán, mint 9+9, de attól még 9+9 bábut tettek le a játékosok.
	 */
	int placed_pieces; ///< Az első részben lerakott bábuk száma
	enum Player current_player; ///< A jelenlegi játékos
};

/**
 * @brief      A tábla inicializálása
 */
void board_init();

/**
 * @brief      A tábla frissítése
 *
 * @param[in]  input    Input
 * @param      running  Cikluskilépéshez átadjuk a pointert
 */
void board_update(input_t input, bool *running);

void board_debug();

/**
 * @brief      Rendereli a táblát
 */
void board_render();

/**
 * @brief      Továbbítja a győztest
 *
 * @return     Győztes játékos
 */
enum Player board_winner();

/**
 * @brief      Leellenőrzi, hogy van-e nyertes
 *
 * Ez az eljárás el is végzi a szükséges teendőket, ha valamelyik játékos nyert
 *
 * @param      running  Cikluskilépéshez átadjuk a pointert
 */
void board_check_win(bool *running);

/**
 * @brief      Megnézi az összes ugyanolyan státuszú bábuk számát
 *
 * @param[in]  p     Az ellenőrizendő bábu státusza
 *
 * @return     Az ugyanolyan státuszú bábuk száma
 */
int count_pieces_with_status(enum PieceStatus p);

/**
 * @brief      Leellenőrzi, hogy megadott bábu tud-e mozogni a megadott pontra
 *
 * @param      from  A mozgatandó bábu
 * @param      to    A cél
 *
 * @return     Mozgatható-e oda?
 */
bool piece_can_move_here(struct Piece *from, struct Piece *to);

/**
 * @brief      Leellenőrzi, hogy a megadott bábu tud-e mozogni
 *
 * @param      p     Az ellenőrizendő bábu
 *
 * @return     Tud-e mozogni?
 */
bool piece_can_move(struct Piece *p);

/**
 * @brief      Megnézi, hogy a megadott játékos összes bábuja malomban van-e
 *
 * @param[in]  player  Az ellenőrizendő játékos
 *
 * @return     Malomban van-e az összes bábu?
 */
bool board_check_all_mill_player(enum Player player);

/**
 * @brief      Megnézi, hogy az adott bábu malomban van-e
 *
 * Muszáj visszaadni, hogy hány malom alakult ki. (ld. Board::removable_pieces)
 *
 * @param      p     A bábu
 *
 * @return     Malomban van-e?
 */
int board_check_mill(struct Piece *p);

/**
 * @brief      A kijelölt bábu lehelyezése a táblára
 */
void board_place_piece();

/**
 * @brief      A kurzor mozgatása a táblán
 *
 * @param[in]  d     A mozgatás iránya
 */
void board_move_cursor(enum Direction d);

/**
 * @brief      Megteremti a logikai kapcsolatot az elemek és a bábuk között
 */
void set_piece_element_relation();

/**
 * @brief      Egy elemet rajzol ki, a makrókban meghatározottak alapján
 *
 * @param      output  A kimenő string pointere
 * @param[in]  row     Az elem sora
 * @param[in]  col     Az elem oszlopa
 */
void draw_element(char *output, int row, int col);

/**
 * @brief      Egy sort rajzol ki, a draw_element() függvény alapján
 *
 * @param      output  A kimenő string pointere
 * @param[in]  row     A kirajzolandó sor
 */
void draw_row(char *output, int row);

#endif