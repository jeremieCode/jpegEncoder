#ifndef HTABLES_H

#define HTABLES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sdd.h"

#define NB_SAMPLE_TYPES 2
#define NB_COLOR_COMPONENTS 3
#define MAX_LENGTH 16
#define LENGTH_DC 12
#define LENGTH_AC 162
/**
 * @brief Table des nombres de symboles par longueur, indexée par le type
 * d'échantillon (DC ou AC), la composante de couleur (Y, Cb ou Cr) et la
 * longueur du symbole (comprise entre 0 et 15).
 * 
 */
    
extern uint8_t htables_nb_symb_per_lengths[NB_SAMPLE_TYPES][NB_COLOR_COMPONENTS][MAX_LENGTH];

/**
 * @brief Table des symboles, indexée par le type d'échantillon (DC ou AC) et la
 * composante de couleur (Y, Cb ou Cr).
 * 
 */
extern uint8_t *htables_symbols[NB_SAMPLE_TYPES][NB_COLOR_COMPONENTS];

/**
 * @brief Table des longueurs des tableaux de symboles, indexée par le type
 * d'échantillon (DC ou AC) et la composante de couleur (Y, Cb ou Cr).
 * 
 */
extern uint8_t htables_nb_symbols[NB_SAMPLE_TYPES][NB_COLOR_COMPONENTS];

/**
 * @brief Table des symboles DC pour la composante Y.
 * 
 */
extern uint8_t htables_symbols_DC_Y[LENGTH_DC];

/**
 * @brief Table des symboles DC pour la composante Cb et Cr.
 * 
 */
extern uint8_t htables_symbols_DC_CbCr[LENGTH_DC];

/**
 * @brief Table des symboles AC pour la composante Y.
 * 
 */
extern uint8_t htables_symbols_AC_Y[LENGTH_AC];

/**
 * @brief Table des symboles AC pour la composante Cb et Cr.
 * 
 */
extern uint8_t htables_symbols_AC_CbCr[LENGTH_AC];


/**
* @brief Crée un noeud contenant et sa profondeur dans l'arbre final.
*
* @param profondeur la profondeur de ce noeud dans l'arbre (int).
* @param valeur la valeur du noeud (char *).
*
* @return noeud d'un arbre (Arbre *).
*/
extern Arbre *creer_arbre_simple(int profondeur, char *valeur);


/**
* @brief affiche une liste.
*
* @param liste la liste à afficher (Liste_arbre *).
*/
extern void affiche_liste(Liste_arbre *liste);


/**
* @brief Inverse une liste.
*
* @param liste la liste à inverser (Liste_arbre *).
*
* @return la liste inversée (Liste_arbre *).
*/
extern Liste_arbre *inverse_liste(Liste_arbre *liste);


/**
* @brief affiche un arbre.
*
* @param a l'arbre à afficher (Arbre *).
*/
extern void affiche_arbre(Arbre *a);


/**
* @brief Insere un élément dans une liste.
*
* @param liste la liste dans laquelle il faut insérer (Liste_arbre *).
* @param a l'arbre qu'il faut insérer dans la liste (Arbre *).
*
* @return la liste avec le nouvel élément (Liste_arbre *).
*/
extern Liste_arbre *insere_liste(Liste_arbre *liste, Arbre *a);


/**
* @brief Crée une liste contenant les noeuds de l'arbre.
*
* @param htables_nb_symb_per_lengths table de huffman contenant le nombre de symbole par longueur de code (uint8_t*).
* @param htables_symbols table des symboles qui vont etre encodé par huffman (uint8_t*)
*
* @return la liste contenant les noeuds et leur profondeur dans l'arbre (Liste_arbre *).
*/
extern Liste_arbre *creer_liste(uint8_t htables_nb_symb_per_lengths[16], uint8_t htables_symbols[]);


/**
* @brief Fusionne deux arbres.
*
* @param a le premier arbre à fusionner qui sera le sous arbre gauche (Arbre *).
* @param b le second arbre à fusionner qui sera le sous arbre droit (Arbre *).
*
* @return la fusion des 2 arbres (Arbre *).
*/
extern Arbre *merge(Arbre *a, Arbre *b);


/**
* @brief Crée l'arbre de Huffman.
*
* @param htables_nb_symb_per_lengths table de huffman contenant le nombre de symbole par longueur de code (uint8_t*).
* @param htables_symbols table des symboles qui vont etre encodé par huffman (uint8_t*)
*
* @return l'arbre de Huffman.
*/
extern Arbre *arbre_huffman(uint8_t htables_nb_symb_per_lengths[16], uint8_t htables_symbols[]);


/**
* @brief Imprime la table des codes de Huffman.
*
* @param arbre_huffman l'arbre de huffman crée précédemment (Arbre*).
* @param code chaine de caractère contenant le code du symbole (char*).
* @param profondeur la profondeur à laquelle on se situe dans l'arbre (int).
* @param htables_symbols table des symboles qui vont etre encodé par huffman (uint8_t*).
*/
extern void table_huffman(Arbre *arbre_huffman, char *code, int profondeur, uint8_t htables_symbols[]);


/**
* @brief Libere un arbre.
*
* @param arbre l'arbre à libérer (Arbre *).
*/
extern void libere_arbre(Arbre *arbre);

#endif /* HTABLES_H */