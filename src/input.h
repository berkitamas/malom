/**
 * @file		input.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#ifndef INPUT_H
#define INPUT_H

/**
 * Az input enumja, így könnyebben átlátható, hogy mi-mit jelent, plusz könnyebben is módosítható
 */
typedef enum {
	NO_INPUT, ///< Nincs vagy ismeretlen input
	INPUT_UP, ///< Fel
	INPUT_DOWN, ///< Le
	INPUT_LEFT, ///< Balra
	INPUT_RIGHT, ///< Jobbra
	INPUT_PAUSE, ///< Játék szüneteltetése
	INPUT_ENTER, ///< Bevitel
	INPUT_CANCEL ///< Mégse
} input_t;

/**
 * @brief      Átalakítja az inputot az enumban megfelelőre (az ismeretlen is NO_INPUT)
 *
 * @return     Feldolgozott input
 */
input_t input_process();

#endif