#ifndef ECRITURE_FLUX_H
#define ECRITURE_FLUX_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "sdd.h"
#include "compression.h"
#include "htables.h"
#include "qtables.h"

/**
* @brief Ajoute un 1 ou un 0 en fin de Byte.
* 
* @param byte Le byte en question (Byte*).
* @param un_ou_zero Valeur a ajouter (uint_8).
*/
extern void incremente(Byte* byte, uint8_t un_ou_zero);

/**
* @brief Remet à zéro un Byte.
* 
* @param byte Le byte en question (Byte*).
*/
extern void reset(Byte* byte);

/**
* @brief Crée un Byte.
* 
* @return Renvoie un byte nul.
*/
extern Byte* creer_byte();

/**
* @brief Remet à zéro le byte courant.
* 
* @param current_byte Le byte courant en question (Byte_courant*).
*/
extern void reset_current_byte(Byte_courant* current_byte);

/**
* @brief Affiche la valeur d'un byte et sa taille.
* 
* @param byte Le byte en question (Byte *).
*/
extern void affiche_byte(Byte* byte);

/**
* @brief Affiche la valeur d'un byte courant et sa taille.
* 
* @param current_byte Le byte en question (Byte_courant *).
*/
extern void affiche_current_byte(Byte_courant* current_byte);

/**
* @brief Écris la valeur d'un byte dans un  fichier.
* 
* @param fichier_final Le fichier en question (FILE *).
* @param byte Le byte en question (Byte *).
*/
extern void ecris_byte(FILE* fichier_final, Byte* byte);

/**
* @brief Écris la valeur d'un byte possiblement incomplet dans un  fichier.
* 
* @param fichier_final Le fichier en question (FILE *).
* @param byte Le byte en question (Byte *).
*/
extern void ecris_byte_restant(FILE* fichier_final, Byte* byte);

/**
* @brief Ajoute un ou des zéros en fin de byte courant.
* 
* @param current_byte Le fichier en question (Byte_courant *).
* @param nb_caractere Nombre de zéros à ajouter (uint8_t).
*/
extern void ajoute_zero(Byte_courant* current_byte, uint8_t nb_caractere);

/**
* @brief Écris la valeur de byte courant dans byte et lance l'écriture dans un fichier quand ce dernier atteint une taille de 8.
* 
* @param fichier_final Le fichier en question (FILE *).
* @param byte Le byte en question (Byte *).
* @param current_byte Le byte courant en question (Byte_courant *).
*/
extern void ecris_dans_byte(FILE* fichier_final, Byte* byte, Byte_courant* current_byte);

/**
* @brief Gère l'écriture globale du bitstream dans un fichier.
* 
* @param fichier_final Le fichier en question (FILE *).
* @param bytes Tableau d'Encode_composante (Encode_composante  **).
* @param reste Reste non écrit du byte précédent (Byte *).
*/
extern void ecris_bitstream(FILE* fichier_final, Encode_composante** bytes, Byte* reste);

#endif