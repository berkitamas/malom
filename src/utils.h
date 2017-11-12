/**
 * @file		utils.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 10. 16.
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * Legkisebb szélesség, amivel még rendesen jelzi ki a táblát
 */
#define MIN_COLUMNS 78 //error

/**
 * Legkisebb magasság, amivel még rendesen jelzi ki a táblát
 */
#define MIN_ROWS 39 //error

/**
 * @brief      Lekérdezi a képernyő oszlopainak számát.
 *
 * @return     A képernyő oszlopainak száma.
 */
int screen_width();

/**
 * @brief      Lekérdezi a képernyő sorainak számát.
 *
 * @return     A képernyő sorarinak száma.
 */
int screen_height();

/**
 * @brief      Visszaadja a megadott stringben levő látható (nem escape) karakterek számát
 *
 * @param      str   A sztring
 *
 * @return     A látható karakterek száma
 */
int str_visible_len(char *str);

/**
 * @brief      A megadott sztring középre igazítása a terminal ablakon belül
 *
 * Tulajdonképpen kiegészíti megfelelő számú szóközzel a függvény a sztringet.
 *
 * @param      str   A sztring pointerének pointere
 */
void center_align(char **str);

/**
 * @brief      Lekérdezi az aktuális képkockát
 *
 * @return     Az aktuális képkocka
 */
clock_t current_frame();

/**
 * @brief      Megállapítja, hogy az aktuális képkocka kívül esik-e a megadott intervallumon.
 *
 * @param[in]  frame  Az intervallum kezdőpontja (képkocka)
 * @param[in]  ms     Az intervallum ideje milliszekundumb an
 *
 * @return     Kívül esik-e?
 */
bool check_interval(int frame, int ms);

/**
 * @brief      Letörli a képernyőt
 *
 * Át állítja a kurzort a kezdőpontra, majd felülírja a karaktereket whitespace-el.
 *
 */
void clear_screen();

/**
 * @brief      Módosítja a termios módját ('nyers' és kanonikus között)
 *
 * https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html#post449307
 *
 * @param[in]  dir   Irány
 */
void termios_changemode(int dir);

/**
 * @brief      Ellenőrzi, hogy valamelyik billentyű le van-e nyomva
 *
 * https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html#post449307
 *
 */
bool kbhit (void);

#endif