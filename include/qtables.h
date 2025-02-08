#ifndef QTABLES_H
#define QTABLES_H

#include <stdint.h>
#define TAILLE_TABLE_QUANTIFICATION 64
/* Tables de "The GIMP" (cf sujet). */

/**
 * @brief Table de quantification pour la composante Y.
 * 
 */
extern uint8_t quantification_table_Y[TAILLE_TABLE_QUANTIFICATION];


/**
 * @brief Table de quantification pour la composante Cb et Cr.
 * 
 */
extern uint8_t quantification_table_CbCr[TAILLE_TABLE_QUANTIFICATION];

#endif /* QTABLES_H */