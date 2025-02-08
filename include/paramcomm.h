#ifndef PARAMCOMM_H
#define PARAMCOMM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "sdd.h"

/**
* @brief Renvoie un pointeur vers une Entree contenant les paramètres données en ligne de commande.
* 
* @param argc Le nombre d'argmuents dans la ligne de commande (int).
* @param argv Le tableau de char* des arguments en question (char** ).
* @return  Une structure Entree contenant toutes les informations nécessaires (cf sdd.h) (Entree *).
*/
extern Entree* param_entree(int argc, char* argv[]);

/**
* @brief Vérifie la validité d'une valeur de sampling donnée (entre 1 et 4 par ex.).
* 
* @param h_or_v Une valeur issue de --sample=h1xv1,... (int).
* @return  1 si valide, 0 sinon (int).
*/
extern int est_valide(int h_or_v);

/**
* @brief Vérifie si a divise b.
* 
* @param a Le diviseur (int).
* @param b Le divisé (int).
* @return  1 si a divise parfaitement b, 0 sinon (int).
*/
extern int divise(int a, int b);

/**
* @brief Récupère le parsing de --sample=... et le convertit en un tableau d'entiers.
* 
* @param entree La structure contenant les paramètres données en ligne de commande (Entree *).
* @return  Un tableau de 2, 4 ou 6 entiers correspondant aux valeurs de sampling (de Y, Cb et Cr) (int *).
*/
extern int* valeur_sampling(Entree* entree);

/**
* @brief Vérifie si le parsing de --sample=... est conforme aux exigences du programme.
* 
* @param valeurs_sample La chaîne de caractère donnée en ligne de commande de la forme --sample=... (char *).
* @return  1 si ces valeurs sont conformes, 0 sinon (int).
*/
extern int verif_sample(char* valeurs_sample);

/**
* @brief Parsing des données sur la ligne de commande, et stocke la donnée obtenue dans entree.
* 
* @param param La chaîne de caractère à reconnaitre (char *).
* @param entree La structure dans laquelle seront stockées les données ainsi récupérées (Entree *).
* @return 1 si tout s'est bien passé, 0 sinon (int).
*/
extern int lis_param(char* param, Entree* entree);

/**
* @brief Regarde à quelle option la chaîne de caractère donnée correspond.
* 
* @param param La chaîne de caractère à reconnaitre (char *).
* @return 1,2,3 ou 4 selon la donnée reconnue, ou -1 si aucune ne correspond.
*/
extern int reconnait_param(char* param);

/**
* @brief Free de entree
* 
* @param entree La structure Entree* à libérer (Entree *).
*/
extern void libere_entree(Entree* entree);

/**
* @brief Affiche les valeurs stockées dans entree.
* 
* @param entree La structure de données correspondante (Entree *).
*/
extern void affiche_entree(Entree* entree);

#endif