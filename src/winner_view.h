/**
 * @file		winner_view.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 05.
 */

#ifndef WINNER_VIEW_H
#define WINNER_VIEW_H

/**
 * @brief      Inicializálja a győztes viewot
 */
void winner_view_init();

/**
 * @brief      Az input alapján frissíti a győztes viewot
 *
 * @param[in]  input    Az input
 * @param      running  Cikluskilépéshez átadjuk a pointert
 */
void winner_view_update(input_t input, bool *running);

/**
 * @brief      Rendereli a győztes viewot
 */
void winner_view_render();

#endif