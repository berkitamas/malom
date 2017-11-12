/**
 * @file		game.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#ifndef GAME_H
#define GAME_H


#define FPS 20 ///< Képkocka / másodperc

///Jelenleg 3 külön viewunk van, ezeket mint a jobb átláthatóság miatt egy enumba rendeztem
enum Views {
	VIEW_SPLASH, ///< Splash View
	VIEW_MAIN_MENU,///< Main Menu View
	VIEW_BOARD, ///< Board view
	VIEW_WINNER ///< Winner view
};

///Jelenleg csak kétjátékos mód van, de az egyjátékos mód ('okos' AI-al is tervben van)
enum GameMode {
	GAME_1_PLAYER, ///< Egyjátékos mód
	GAME_2_PLAYER ///< Kétjátékos mód
};

///A játék struktúrája
struct Game {
	enum Views current_view; ///< Jelenleg aktív view
	enum GameMode mode; ///< Jelenleg aktív játékmód
};

/**
 * @brief      Inicializája a játékot, a main fgv. hívja meg
 */
void game_init();

/**
 * @brief      Interrupt handler
 *
 * @param[in]  sig   Interrupt signal
 *
 * Gyakoratilag egy hookként lehet jellemezni, arra való, hogyha a felhasználó meg szeretné
 * szakítani a folyamatot, akkor ennek a blokkjában lévő kódsor még lefut. Létezésének oka az,
 * hogy elég masszívan módosítjuk a terminál viselkedését (raw mode, alt. screen).
 *
 */
void int_handler(int sig);

/**
 * @brief      Átállítja a termiost raw módba, alt. screenre rakja a terminált, eltűnteti a kurzort
 */
void set_terminal_mode();

/**
 * @brief      Visszaállítja a termiost kanonikus módba, visszaállítja a terminált alt. screenből, megjeleníti a kurzort
 */
void restore_terminal_mode();

/**
 * @brief      Hozzákapcsolja az int_handler() fgv.-t az interrupt signalokhoz.
 */
void set_signal_handler();

/**
 * @brief      Megnézi, hogy a terminál jelenlegi dimenziója elég nagy-e a játék futtatásához
 *
 * @return     Elegendő-e?
 */
bool validate_dimensions();

/**
 * @brief      Kilép a játékból
 *
 * @param[in]  ret   A program kilépésének return kódja
 */
void exit_game(int ret);

/**
 * @brief      Előre lép a viewok között
 */
void game_next_view();

/**
 * @brief      Visszalép a viewok között
 */
void game_prev_view();

/**
 * @brief      Beállítja a játékmódot (1 játékos, 2 játékos)
 *
 * @param[in]  mode  Játékmód
 */
void set_game_mode(enum GameMode mode);

/**
 * @brief      Ez egy absztrakt eljárás, amivel egységesíteni lehet a viewok fő részét.
 *
 * Az alapelv az, hogy minden viewnak van egy game loopja, ami három részből áll:\n
 *  - Input kezelése\n
 *  - A view logikája\n
 *  - A view kirajzolása\n\n
 *
 * A viewok pedig csak a logikában, meg a kirajzolás mögötti algoritmusban különböznek egymástól,
 * tehát ezeket egységesíteni lehetett egy függvénybe. Ez a fajta megvalósítás hasonlít az
 * OO paradigmában megvalósított interfészekre.
 *
 * @param[in]  update  Az update függvény
 * @param[in]  render  A render függvény
 */
void game_loop(void (*update)(input_t input, bool *running), void (*render)());

#endif