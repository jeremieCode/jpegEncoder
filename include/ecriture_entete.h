#ifndef ECRITURE_ENTETE_H
#define ECRITURE_ENTETE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "sdd.h"
#include "htables.h"
#include "qtables.h"

#define  TAILLE_ENTETE 20
extern int entete[TAILLE_ENTETE+1]; 

/**
* @brief Force l'écriture d'une valeur sur 4 octets dans un fichier.
* 
* @param fichier Le fichier en question (FILE *).
* @param valeur Valeur en question (int).
*/
extern void ecris_val_4octets(FILE* fichier, int valeur);

/**
* @brief Convertit une chaine de charactère en entier.
* 
* @param binaire Le fichier en question (char *).
* @return Renvoie la valeur ainsi obtenue.
*/
extern int char_to_dec(char* binaire);

/**
* @brief Affiche le contenu d'un fichier.
* 
* @param fichier Le fichier en question (FILE *).
*/
extern void affiche_fichier(FILE* fichier);

/**
* @brief Écris le même commentaire que celui des profs en entête JPEG.
* 
* @param fichier Le fichier destination (FILE *).
*/
extern void ecriture_comm_test(FILE* fichier);

/**
* @brief Écris un commentaire en entête JPEG.
* 
* @param fichier Le fichier destination (FILE *).
* @param comm Le commentaire à écrire (char *).
*/
extern void ecriture_comm(FILE* fichier, char* comm);

/**
* @brief Écris l'entête JFIF.
* 
* @param fichier Le fichier destination (FILE *).
*/
extern void ecriture_entete_jfif(FILE* fichier);

/**
* @brief Définis les tables de quantification en entête JPEG.
* 
* @param fichier Le fichier destination (FILE *).
* @param type Le type d'image (ppm ou pgm) (couleur).
*/
extern void ecriture_dqt(FILE* fichier, couleur type);

/**
* @brief Écris la section SOFx (Start of Frame) de l'entête JPEG.
* 
* @param fichier Le fichier destination (FILE *).
* @param entree Les données récupérées sur la ligne de commande (Entree *).
* @param largeur Largeur de l'image (int).
* @param hauteur Hauteur de l'image (int).
* @param type Type de  l'image (couleur).
*/
extern void ecriture_frame(FILE* fichier, Entree* entree, int largeur, int hauteur, couleur type);

/**
* @brief Définis les tables de Huffman en entête JPEG.
* 
* @param fichier Le fichier destination (FILE *).
* @param y_ou_cbcr Composante Y ou Cb/Cr (0 ou 1) (int).
* @param dc_or_ac Composante AC ou DC (0 ou 1) (int).
*/
extern void ecriture_dht(FILE* fichier, int y_ou_cbcr, int dc_or_ac);

/**
* @brief Écris la section SOS de l'entête JPEG.
* 
* @param fichier Le fichier destination (FILE *).
* @param type Type de  l'image (couleur).
*/
extern void ecriture_sos(FILE* fichier, couleur type);

/**
* @brief Gère l'écriture générale des entêtes pour les images pgm.
* 
* @param fichier Le fichier destination (FILE *).
* @param entree Les données récupérées sur la ligne de commande (Entree *).
* @param pgm Matrice de pixels correposant à l'image pgm (Pgm *)
*/
extern void ecriture_entete_pgm(FILE* fichier, Entree* entree, Pgm* pgm);

/**
* @brief Gère l'écriture générale des entêtes pour les images ppm.
* 
* @param fichier Le fichier destination (FILE *).
* @param entree Les données récupérées sur la ligne de commande (Entree *).
* @param ppm Matrice de pixels correposant à l'image ppm (Ppm *)
*/
extern void ecriture_entete_ppm(FILE* fichier, Entree* entree, Ppm* ppm);

/**
* @brief Écris la balise de fin d'image.
* 
* @param fichier Le fichier destination (FILE *).
*/
extern void ecriture_fin(FILE* fichier);

#endif