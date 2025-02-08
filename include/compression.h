#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sdd.h>
#include <zig_zag.h>
#include <htables.h>
#include <tables_huffman.h> 


/**
* @brief Renvoie la classe de magnitude d'un entier.
* 
* @param p Un entier (int).
* @return  Classe de magnitude (int).
*/
extern int magnitude(int p);


/**
* @brief Renvoie la position dans la classe de magnitude.
* 
* @param val entier dont on cherche la position (int16_t).
* @param classe La classe associé à une valeur (uint8_t).
* @return Position dans la classe (uint16_t).
*/
extern uint16_t num_classe_entier(int16_t val, uint8_t classe);


/**
* @brief Renvoie la position d'un élément dans le tableau de huffman.
* 
* @param val entier dont on cherche la position (uint8_t).
* @param htables_sympbols Le tableau de huffman (uint8_t*).
* @param size taille du tableau (uint8_t).
* @return indice dans le tableau (int).
*/
extern int trouve_indice(uint8_t val, uint8_t htables_symbols[], uint8_t size);


/**
* @brief Renvoie la longueur du code de huffman d'une valeur.
* 
* @param p entier dont on cherche la longueur (uint8_t).
* @param htable_nb_symb_per_lengths table du nombre de symbole par longueur de code de Huffman (uint8_t*).
* @return longueur du code (uint8_t).
*/
extern uint8_t profondeur_huffman(int p, uint8_t htables_nb_symb_per_lengths[16]);


/**
* @brief Renvoie la compression RLE de la partie AC du bloc zig zag.
* 
* @param bloc_entree un vecteur de taille 64 transformé par zig zag (Bloc_ZZ*).
*
* @return Tableau de nombre en hexadécimal contenant des informations dessus (Tuple_encodage_sans_huffman**).
*/
extern Tuple_encodage_sans_huffman **codage_rle(Bloc_ZZ *bloc_entree);


/**
* @brief Renvoie la compression RLE et le code de Huffman de la partie DC du bloc zig zag.
* 
* @param encode tableau contenant la compression de la partie AC de zig zag (Tuple_encodage_avec_huffman**).
* @param table_huffman_DC tableau des codes de huffman de la composante DC (uint16_t*).
* @param htables_symbols_DC table de huffman de la composante DC (uint8_t*).
* @param zz un vecteur de taille 64 transformé par zig zag du bloc actuel (Bloc_ZZ*).
* @param prec un vecteur de taille 64 transformé par zig zag du bloc précédent (Bloc_ZZ*).
* @param htable_nb_symb_per_lengths table du nombre de symbole par longueur de code de Huffman (uint8_t*).
*
* @return Tableau de nombre en hexadécimal contenant l'encodage final du bloc donné (Tuple_encodage_avec_huffman**).
*/
extern Tuple_encodage_avec_huffman **composante_DC(Tuple_encodage_avec_huffman **encode, uint16_t *table_huffman_DC, uint8_t htables_symbols_DC[], Bloc_ZZ *zz, Bloc_ZZ *prec, uint8_t htables_nb_symb_per_lengths[16]);


/**
* @brief Renvoie la compression par huffman de la partie AC du bloc zig zag.
* 
* @param prem_encodage un vecteur de taille 64 qui contient l'encodage RLE de la partie AC (Tuple_encodage_sans_huffman**).
* @param table_huffman_AC tableau des codes de huffman de la composante AC (uint16_t*).
* @param htables_symbols_AC table de huffman de la composante AC (uint8_t*).
* @param htable_nb_symb_per_lengths table du nombre de symbole par longueur de code de Huffman (uint8_t*).
*
* @return Tableau contenant le codage de chaque composante et la longueur du code (Tuple_encodage_avec_huffman**).
*/
extern Tuple_encodage_avec_huffman **huffman(Tuple_encodage_sans_huffman **prem_encode, uint16_t *table_huffman_AC, uint8_t htables_symbols_AC[], uint8_t htables_nb_symb_per_lengths[16]);


/**
* @brief Renvoie la compression final du bloc zig zag en ajoutant le code de la position dans la classe.
* 
* @param encode un vecteur de taille 64 qui contient l'encodage RLE et de huffman du bloc zig_zag (Tuple_encodage_avec_huffman**).
*
* @return Tableau contenant le codage de chaque composante et la longueur du code (Enconde_composante**).
*/

extern Encode_composante **encode_final(Tuple_encodage_avec_huffman **encode);


/**
* @brief Renvoie la compression du bloc zig-zag en effectuant toutes les étapes.
* 
* @param entree un vecteur de taille 64 transformé par zig zag du bloc actuel (Bloc_ZZ*).
* @param prec un vecteur de taille 64 transformé par zig zag du bloc précédent (Bloc_ZZ*).
* @param composante paramètre pour savoir si on traite une image pgm ou ppm (composante)
*
* @return Tableau contenant le codage finale du bloc zig_zag (Encode_composante**).
*/
extern Encode_composante **encodage_rle_huffman(Bloc_ZZ *entree, Bloc_ZZ *prec, composante composante);


/**
* @brief Libère la mémoire d'un élément du type Encode_composante**
*
* @param encode un tableau qui contient l'encodage d'un bloc (Encode_composante**).
*/
extern void libere_encode_composante(Encode_composante **encode);


/**
* @brief Affiche le codage binaire d'un nombre
*
* @param temp le nombre que l'on veut traiter (uint32_t).
*/
extern void affiche_binaire(uint32_t temp);


/**
* @brief Affiche le codage binaire d'un bloc
*
* @param entree l'encodage du bloc que l'on veut afficher (Encode_composante**).
*/
extern void affiche_encodage(Encode_composante **entree);

#endif