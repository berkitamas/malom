/**
 * @file		main_menu.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#define MAIN_MENU_WIDTH 40 ///< Főmenü szélessége

/// A főmenü enumja
typedef enum {
	//MENU_1_PLAYER terv
	MENU_2_PLAYER, ///< 2 játékos
	MENU_QUIT_GAME ///< Kilépés a játékból
} mainmenu_t;

/**
 * @brief      Inicializálja a főmenüt
 */
void main_menu_init();

/**
 * @brief      Az input alapján frissíti a főmenüt
 *
 * @param[in]  input    Az input
 * @param      running  Cikluskilépéshez átadjuk a pointert
 */
void main_menu_update(input_t input, bool *running);

/**
 * @brief      Rendereli a főmenüt
 */
void main_menu_render();

#endif