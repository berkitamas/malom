/**
 * @file		element.c
 * @author		Berki Tamás - PDRE31
 * @date		2017. 11. 01.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "element.h"

static element_t elements[ELEMENT_ROW][ELEMENT_COLUMN];  ///< Az elemek tulajdonságait tartalmazó változó

element_t *element(int row, int col)
{
	if (row < 0 || row >= ELEMENT_ROW) {
		return NULL;
	}
	if (col < 0 || col >= ELEMENT_COLUMN) {
		return NULL;
	}
	return &elements[row][col];
}

void element_init()
{
	init_element_statuses();
}

void prepare_element(char type, element_t *element)
{
	element->type = type;
	if (type == 'x') {
		element->status = E_EMPTY;
	} else {
		element->status = E_STATIC;
	}
}

void prepare_row(const char *format, element_t *row)
{
	int i;

	for (i = 0; format[i] != '\0'; i++) {
		prepare_element(format[i], &row[i]);
	}
}

void init_element_statuses()
{
	int i;

	/**
	 * A tábla dizájnja
	 */
	const char *rows[ELEMENT_ROW] = {
		"abbbbbabbbbba",
		"xaaaaaxaaaaax",
		"abbbbbabbbbba",
		"cbbbbbcbbbbbc",
		"cbbbbbcbbbbbc",
		"cbbbbbcbbbbbc",
		"cbabbbabbbabc",
		"cbxaaaxaaaxbc",
		"cbabbbabbbabc",
		"cbcbbbcbbbcbc",
		"cbcbbbcbbbcbc",
		"cbcbbbcbbbcbc",
		"cbcbabababcbc",
		"cbcbxaxaxbcbc",
		"cbcbabababcbc",
		"cbcbcbbbcbcbc",
		"cbcbcbbbcbcbc",
		"cbcbcbbbcbcbc",
		"abababbbababa",
		"xaxaxbbbxaxax",
		"abababbbababa",
		"cbcbcbbbcbcbc",
		"cbcbcbbbcbcbc",
		"cbcbcbbbcbcbc",
		"cbcbabababcbc",
		"cbcbxaxaxbcbc",
		"cbcbabababcbc",
		"cbcbbbcbbbcbc",
		"cbcbbbcbbbcbc",
		"cbcbbbcbbbcbc",
		"cbabbbabbbabc",
		"cbxaaaxaaaxbc",
		"cbabbbabbbabc",
		"cbbbbbcbbbbbc",
		"cbbbbbcbbbbbc",
		"cbbbbbcbbbbbc",
		"abbbbbabbbbba",
		"xaaaaaxaaaaax",
		"abbbbbabbbbba"
	};

	for (i = 0; i < ELEMENT_ROW; ++i) {
		prepare_row(rows[i], elements[i]);
	}

}