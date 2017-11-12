/**
 * @file		element.h
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#ifndef ELEMENT_H
#define ELEMENT_H

///Az elemek száma egy sorban
#define ELEMENT_ROW 39
///Az elemek száma egy oszlopban
#define ELEMENT_COLUMN 13

/**
 * @brief      Az elemek státuszának enumja
 */
enum ElementStatus {
	E_EMPTY, ///< Üres (akkor, ha ez dinamikus)
	E_STATIC, ///< Statikus (pl egy fekete vonal)
	E_P1, ///< Az első játékos bábuja tartózkodik itt
	E_P2 ///< A második játékos bábuja tartózkodik itt
};

typedef struct Piece piece_t;
typedef struct Element element_t;

/**
 * @brief      Az elemek tulajdonságai
 */
struct Element {
	/**
	 * \verbatim
	 * a - [██████]
	 * b - [      ]
	 * c - [  ██  ]
	 * x - [██  ██] (dinamikus)
	 * \endverbatim
	 */
	char type; ///< Az elem típusa
	enum ElementStatus status; ///< Az elem státusza (csak Element::type = x)
	bool blink_status; ///< A kijelölt elem villogási státusza (csak Element::type = x)
	clock_t blink_frame; ///< A kijelölt elem villogási képkockája (csak Element::type = x)
	piece_t *piece;  ///< Az elemhez tartozó bábu (csak Element::type = x, különben NULL pointer)
};

/**
 * @brief      Továbbítja a sor és az oszlop szerint az elem pointerét
 *
 * @param[in]  row   A sor
 * @param[in]  col   Az oszlop
 *
 * @return     Ezen a koordinátán elhelyezkedő elem pointere
 */
element_t *element(int row, int col);

/**
 * @brief      Inicializálja az elemeket (pl. prepare_element())
 */
void element_init();

/**
 * @brief      Elkészíti az elemet a megadott típus szerint
 *
 * @param[in]  type     A típus (Element::type)
 * @param      element  Az elem, ahova a típust írjuk
 */
void prepare_element(char type, element_t *element);

/**
 * @brief      Elkészíti a megadott sort a prepare_element() segítségével
 *
 * @param[in]  format  A formátum
 * @param      row     A sor
 */
void prepare_row(const char *format, element_t row[13]);

/**
 * @brief      Inicializálja az elemek állapotát (Element::status)
 */
void init_element_statuses();

#endif