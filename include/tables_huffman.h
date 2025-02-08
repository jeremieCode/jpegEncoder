#ifndef TABLES_HUFFMAN_H
#define TABLES_HUFFMAN_H

#include <stdint.h>

#define TAILLE_CODE_HUFFMAAN_DC 12
#define TAILLE_CODE_HUFFMAAN_AC 162


/**
 * @brief Table des code de Huffan DC pour Y
 * 
 */
extern uint16_t code_huffman_DC_Y[TAILLE_CODE_HUFFMAAN_DC];

/**
 * @brief Table des code de Huffan DC pour Cb et Cr
 * 
 */
extern uint16_t code_huffman_DC_CbCr[TAILLE_CODE_HUFFMAAN_DC];

/**
 * @brief Table des code de Huffan AC pour Y
 * 
 */extern uint16_t code_huffman_AC_Y[TAILLE_CODE_HUFFMAAN_AC];

/**
 * @brief Table des code de Huffan AC pour Cb et Cr
 * 
 */extern uint16_t code_huffman_AC_CbCr[TAILLE_CODE_HUFFMAAN_AC];

#endif