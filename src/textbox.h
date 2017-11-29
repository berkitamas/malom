/**
 * @file		textbox.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#ifndef TEXTBOX_H
#define TEXTBOX_H

/**
 * Textbox távolsága a táblától
 */
#define TEXTBOX_OFFSET 2

/**
 * Textbox szélessége
 */
#define TEXTBOX_WIDTH 30

/**
 * Textbox magassága
 */
#define TEXTBOX_HEIGHT 9

/**
 * Textboxba helyezhető szöveg pozíciója
 */
#define TEXTBOX_DYNAMIC_MSG 6

/**
 * @brief      A textbox megadott sorának kirajzolása
 *
 * @param      str   A kimeő string
 * @param[in]  row   A kirajzolandó sor
 */
void draw_textbox(char *str, int row);

/**
 * @brief      Beállítja a textboxban megjelenő üzenetet.
 *
 * @param      msg   Az üzenet
 */
void set_textbox_msg(char *msg);

/**
 * @brief       Beállítja a textboxban megjelenő hibaüzenetet.
 *
 * @param      msg   Az üzenet
 */
void set_textbox_error(char *msg);


/**
 * @brief      Felszabadítja a textbox által lefoglalt helyet.
 */
void textbox_free();
#endif