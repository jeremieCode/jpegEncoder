#ifndef SDD_H
#define SDD_H

#include <stdint.h>


#define TAILLE_BLOC 8
#define TAILLE_BLOC_ZZ 64
#define TAILLE_MCU_PGM 8 
#define NB_BITS 32


typedef enum {GRIS, RGB} couleur;
typedef enum {GRIS_COMPO, Y, CB, CR} composante;
typedef enum {HELP, OUTFILE, SAMPLE, FICHIER_PGM, FICHIER_PPM, VERBOSE} option;


/**
* @brief Données récupérées sur la ligne de commande.
* 
*/
typedef struct entree{
    // Fichier de sortie, optionnel (char*)
    char* outfile;
    // Sampling sous la forme  "h1xv1,h2x...", optionnel (char*).
    char* sample;
    // Fichier source (char*).
    char* fichier;
    // Sampling sous la forme d'un tableau d'int, par défaut un tableau de 1 (int*).
    int* sample_int;
    // type Type de l'image (GRIS  ou RGB) (couleur).
    couleur type;
    // Mode verbose ou non
    int verbose;
} Entree;

/**
 * @brief Donné représentant un pixel: Y, ou Cb, ou Cr. Peu_importe pour 
 * appliquer des opérations sur les pixels peut importe ce qu'il représente.
 * 
 */
typedef union pixel{
    // gris 
    int16_t gris;
    // luminance (Y).
    int16_t y;
    // chrominance (Cb).
    int16_t cb;
    // chrominance (Cr).
    int16_t cr;
    // peu_importe
    int16_t peu_importe;
} Pixel;

/**
 * @brief Donné représentant un pixel: Y, ou Cb, ou Cr. Peu_importe pour 
 * appliquer des opérations sur les pixels peut importe ce qu'il représente.
 * Cette fois ci le pixel est un de flottant.
 * 
 */
typedef union pixel_float{
    // gris.
    float gris;
    // luminance (Y).
    float y;
    // chrominance (Cb).
    float cb;
    // chrominance (Cr).
    float cr;
    // peu_importe.
    float peu_importe;
} Pixel_float;


/**
 * @brief Matrice des pixels correspondant à l'image en niveau de gris.
 * 
 */
typedef struct pgm{
    // hauteur de l'image.
    unsigned int hauteur;
    // largeur de l'image.
    unsigned int largeur;
    // matrice des niveaus de gris.
    Pixel** matrice_gris;
} Pgm;


/**
 * @brief 3 Matrices des pixels correspondant à l'image en  YCbCr.
 * 
 */
typedef struct ppm{
    // hauteur de l'image.
    unsigned int hauteur;
    // laregur de l'image.
    unsigned int largeur;
    // matrice Y.
    Pixel** matrice_y;
    // matrice Cb.
    Pixel** matrice_cb;
    // matrice Cr.
    Pixel** matrice_cr;
} Ppm;


/**
 * @brief Plus petite donnée sous forme MCU (taille 8x8). Contient des Pixels. 
 * 
 */
typedef struct bloc{
    // matrice des pixels.
    Pixel matrice_pixels[TAILLE_BLOC][TAILLE_BLOC];
} Bloc;


/**
 * @brief Plus petite donnée sous forme MCU (taille 8x8). Contient des Pixels sour forme flottant.
 * 
 */
typedef struct bloc_float{
    // matrice des pixels sous forme flottant.
    Pixel_float matrice_pixels_float[TAILLE_BLOC][TAILLE_BLOC];
} Bloc_float;

/**
 * @brief Reorganisation du bloc sous la taille 64x1.
 * 
 */
typedef struct bloc_zig_zag{
    Pixel vecteur_pixels_zz[TAILLE_BLOC_ZZ];
} Bloc_ZZ;


/**
 * @brief Liste chaînée représentant où chaque maillon représente un bloc de pixel gris.
 * 
 */
typedef struct mcu_pgm{
    // Nombre MCU total pour couvrir toute l'image.
    unsigned int nb_blocs;
    // Bloc pour une MCU.
    Bloc bloc_gris;
    // Prochaine MCU.
    struct mcu_pgm *suivant;
} Mcu_pgm;

/**
 * @brief Liste chaînée où chaque maillon à 3 tableaux de blocs pour Y, Cb et Cr.
 * 
 */
typedef struct mcu_ppm{
    // taille du tableau pour Y.
    unsigned int nb_blocs_y;
    // taille du tableau pour Cb.
    unsigned int nb_blocs_cb;
    // taille du tableau pour Cr.
    unsigned int nb_blocs_cr;
    // tableau contennant les blocs Y.
    Bloc* blocs_y;
    // tableau contennant les blocs Cb.
    Bloc* blocs_cb;
    // tableau contennant les blocs Cr.
    Bloc* blocs_cr;
    // Prochaine MCU.
    struct mcu_ppm *suivant;
} Mcu_ppm;


/**
 * @brief Structure d'arbre.
 * 
 */
typedef struct arbre{
    // profondeur du noeud
    int profondeur;
    // symbole du noeud
    char *val;
    struct arbre *fils_gauche;
    struct arbre *fils_droit;
} Arbre;


/**
 * @brief Liste chainée d'arbres.
 * 
 */
typedef struct liste_arbre{
    Arbre *arbre_huff;
    struct liste_arbre *suivant;
} Liste_arbre;



/**
 * @brief Contient les symboles de après la première compression par RLE d'un bloc
 * 
 */
typedef struct tuple_encodage_sans_huff{
    // valeur de la classe et du nombre de 0 en hexa
    uint8_t nb0_magnitude;
    // indice dans la classe
    uint16_t indice_classe;
    // classe
    uint8_t classe;
    // fin du bloc
    int fin;
} Tuple_encodage_sans_huffman;


/**
 * @brief Contient les symboles de après la deuxième compression par Huffman d'un bloc
 * 
 */
typedef struct tuple_encodage_avec_huff{
    // valeur de la classe et du nombre de 0 encodé par huffman
    uint16_t nb0_magnitude_huff;
    uint16_t indice_classe;
    uint8_t classe;
    uint8_t nb_caractere;
} Tuple_encodage_avec_huffman;



/**
 * @brief Donné contenant la valeur de l'encodage d'un symbole et le nombre de caractère pour le codage.
 * 
 */
typedef struct encode_composante{
    uint32_t valeur;
    uint8_t nb_caractere;
} Encode_composante;


/**
* @brief Structure stockant jusqu'à un octet et la taille en binaire de sa valeur
* 
*/
typedef struct byte {
    // Taille en bits de la valeur (uint8_t).
    uint8_t taille;
    // Valeur jusqu'à un octet (uint8_t).
    uint8_t valeur;
} Byte;


/**
* @brief Structure stockant un/des octet(s) en cours d'écriture
* 
*/
typedef struct byte_courant {
    // Tableau de bits (uint8_t*).
    uint8_t valeurs[NB_BITS];
    // Nombre de bits stockés (uint8_t).
    uint8_t taille;
} Byte_courant;

#endif