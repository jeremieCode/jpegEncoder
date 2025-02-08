#ifndef ZIG_ZAG_H
#define ZIG_ZAG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include"sdd.h"

/**
 * @brief Calcul les coefficients selon le motif Zig-Zag
 * 
 * @param x abscisse du point 
 * @param y ordonnée du point 
 * @param taille dimension du carré
 * @return unsigned int 
 */
unsigned int zig_zag_coeff(unsigned int x, unsigned int y, unsigned int taille);

/**
 * @brief Transforme un Bloc en Bloc Zig-Zag
 * 
 * @param bloc bloc à transformer
 * @return Bloc_ZZ* 
 */
Bloc_ZZ* zig_zag(Bloc* bloc);

/**
 * @brief Libere la mémoire pour un bloc Zig-Zag
 * 
 * @param zz le bloc Zig-Zag en quesiton
 */
void libere_zig_zag(Bloc_ZZ* zz);

/**
 * @brief Affiche un Bloc Zig-Zag
 * 
 * @param zz le bloc Zig-Zag en quesiton
 */
void affiche_zig_zag(Bloc_ZZ* zz);

#endif