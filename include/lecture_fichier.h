#ifndef LECTURE_FICHIER_H
#define LECTURE_FICHIER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <math.h>

#include "sdd.h"

/**
 * @brief Permet de lire les en-têtes des fichiers PGM/PPM et vérifie si elles sont cohérante.
 * 
 * @param fichier fichier à lire.
 * @param type_lu tableau représentant le futur type du fichier (P5 ou P6).
 * @param largeur largeur de l'image.
 * @param hauteur hateur de l'image.
 * @return int: Renvoie 0 si le fichier est bon, -1 sinon.
 */
extern int lire_en_tete(FILE* fichier, char* type_lu, unsigned int* largeur, unsigned int* hauteur);


/**
 * @brief Peremt de lire et parser une image PGM en la mettant dans la sdd Pgm.
 * 
 * @param fichier fichier à lire. 
 * @return Pgm* 
 */
extern Pgm* lire_image_pgm(FILE* fichier);


/**
 * @brief Peremt de lire et parser une image PPM en la mettant dans la sdd Ppm.
 * 
 * @param fichier fichier à lire. 
 * @return Ppm* 
 */
extern Ppm* lire_image_ppm(FILE* fichier);


/**
 * @brief Permet de convertir un pixel RGB en Y.
 * 
 * @param r rouge.
 * @param g vert.
 * @param b bleu.
 * @return int16_t 
 */
extern int16_t converti_y(int16_t r, int16_t g, int16_t b);


/**
 * @brief Permet de convertir un pixel RGB en Cb.
 * 
 * @param r rouge.
 * @param g vert.
 * @param b bleu.
 * @return int16_t 
 */
extern int16_t converti_cb(int16_t r, int16_t g, int16_t b);


/**
 * @brief Permet de convertir un pixel RGB en Cr.
 * 
 * @param r rouge.
 * @param g vert.
 * @param b bleu.
 * @return int16_t 
 */
extern int16_t converti_cr(int16_t r, int16_t g, int16_t b);


/**
 * @brief Alloue une matrice de pixel de taille hauteur * largeur.
 * 
 * @param hauteur hauteur de la matrice.
 * @param largeur largeur de la matrice.
 * @return Pixel** 
 */
extern Pixel** alloue_matrice_ppgm(unsigned int hauteur, unsigned int largeur);


/**
 * @brief Permet de liberer une matrice de pixel.
 * 
 * @param matrice matrice de pixel.
 * @param largeur largeur de la matrice.
 */
extern void libere_matrice_pixel(Pixel** matrice, unsigned int largeur);


/**
 * @brief Permet de liberer une Pgm.
 * 
 * @param pgm
 */
extern void libere_pgm(Pgm* pgm);


/**
 * @brief Permet de liberer une Ppm.
 * 
 * @param ppm
 */
extern void libere_ppm(Ppm* ppm);


/**
 * @brief Peremt d'afficher une image au format Pgm.
 * 
 * @param pgm 
 */
extern void affiche_image_pgm(Pgm* pgm);


/**
 * @brief Peremt d'afficher une image au format Ppm.
 * 
 * @param ppm 
 */
extern void affiche_image_ppm(Ppm* ppm);


/**
 * @brief Permet d'écrire une image pgm dans un un fichier. Attnetion c'est au format P2.
 * 
 * @param pgm pgm à écrire dans un fichier.
 * @param nom_du_fichier nom du fichier à écrire dedans.
 */
extern void ecrit_image_pgm(Pgm* pgm, const char* nom_du_fichier);


/**
 * @brief Permet d'écrire une image pgm dans un un fichier. Attnetion c'est au format P3.
 * 
 * @param pgm ppm à écrire dans un fichier.
 * @param nom_du_fichier nom du fichier à écrire dedans.
 */
extern void ecrit_image_ppm(Ppm* ppm, const char* nom_du_fichier);


/**
 * @brief Affiche un bloc (e taille 8x8).
 * 
 * @param bloc 
 */
extern void affiche_bloc(Bloc* bloc);

#endif


