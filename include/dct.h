#ifndef DCT_H
#define DCT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "sdd.h"
#define PI 3.14159265358979323846


/**
* @brief Gère l'arrondi sur les imprécisions (par ex.  3.9991 => 4).
* 
* @param valeur Valeur à arrondir (float).
* @return La valeur arrondie (uint16_t).
*/
extern uint16_t arrondi(float valeur);


/**
* @brief Crée le tableau des valeurs de cosinus.
* 
* @return matrice des valeurs des cosinus (float**).
*/
extern float **creer_tab_cos();

/**
* @brief Calcule de la DCT version naïve.
* 
* @param bloc un bloc à traiter (Bloc*).
* 
* @return bloc contenant la transformation par DCT (Bloc*).
*/
extern Bloc* dct(Bloc* bloc);


/**
* @brief Calcule de la DCT optimisé avec des tableaux de cosinus version 2.
* 
* @param bloc un bloc à traiter (Bloc*).
* 
* @return bloc contenant la transformation par DCT (Bloc*).
*/
extern Bloc* dct_opt_1(Bloc* bloc, float **tab_cos);


/**
* @brief Calcul des coefficients par DCT.
* 
* @param component tableau de float contenat les valeurs à transformer (float*).
*/
extern void ForwardDCTComponent(float *component);

/**
* @brief Calcule de la DCT optimisé version 2 en utilisant la première fonction.
* 
* @param bloc un bloc à traiter (Bloc*).
* 
* @return bloc contenant la transformation par DCT (Bloc*).
*/
extern Bloc* dct_opt_2(Bloc* bloc);


/**
* @brief Crée un bloc vide.
* 
* @return bloc vide (Bloc*).
*/
extern Bloc* creer_bloc_freq();


/**
* @brief Crée un bloc contenant des flottants.
* 
* @return bloc pouvant contenir des flottants (Bloc_float*).
*/
extern Bloc_float* creer_bloc_freq_float();


/**
* @brief Libère un tableau 2D.
*
* @param tab le tableau à libérer (float **).
* @param nb_ligne le nombre de ligne à traiter (unsigned int). 
*/
extern void libere_tab_2D(float** tab, unsigned int nb_ligne);

/**
* @brief Libère un bloc de flottants.
*
* @param freq_float bloc à libérer (Bloc_float*).
*/
extern void libere_bloc_float(Bloc_float *freq_float);

/**
* @brief Libère un bloc.
*
* @param freq bloc à libérer (Bloc*).
*/
extern void libere_bloc(Bloc *freq);


#endif