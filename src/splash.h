/**
 * @file		splash.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#ifndef SPLASH_H
#define SPLASH_H

/**
 * @brief      Inicializálja a splash screent
 */
void splash_init();

/**
 * @brief      Az input alapján frissíti a splash screent
 *
 * @param[in]  input    Input
 * @param      running  Cikluskilépéshez átadjuk a pointert
 */
void splash_update(input_t input, bool *running);

/**
 * @brief      Rendereli a splash screent
 */
void splash_render();

#endif