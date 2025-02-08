#ifndef DECOUPAGE_MCU_H
#define DECOUPAGE_MCU_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <math.h>
#include "lecture_fichier.h"
#include "sdd.h"

/**
 * @brief Découpe en MCU (liste chaînée) un fichier de types Pgm.
 * 
 * @param pgm pgm à découper.
 * @param liste_mcus liste_mcu que l'on va remplir (et donc effet de bord...).
 */
extern void decoupage_en_mcus_pgm(Pgm* pgm, Mcu_pgm** liste_mcus);


/**
 * @brief Affiche la liste des MCU pour une PGM.
 * 
 * @param liste_mcus liste à afficher.
 */
extern void affiche_mcus_pgm(Mcu_pgm *liste_mcus);


/**
 * @brief Libère un élément de type Mcu_pgm.
 * 
 * @param liste_mcus élément à libérer.
 */
extern void libere_liste_mcus_pgm(Mcu_pgm* liste_mcus);


/**
 * @brief Découpe en MCU (liste chaînée) un fichier de types Ppm.
 * 
 * @param ppm ppm à découper.
 * @param liste_mcus liste_mcu que l'on va remplir (et donc effet de bord...).
 * @param h1 hauteur des sous-mcu pour la composante Y.
 * @param v1 largeur des sous-mcu pour la composante Y.
 * @param h2 hauteur des sous-mcu pour la composante Cb.
 * @param v2 largeur des sous-mcu pour la composante Cb.
 * @param h3 hauteur des sous-mcu pour la composante Cr.
 * @param v3 largeur des sous-mcu pour la composante Cr.
 */
extern void decoupage_en_mcus_ppm(Ppm* ppm, Mcu_ppm** liste_mcus, unsigned int h1, unsigned int v1, unsigned int h2, unsigned int v2, unsigned int h3, unsigned int v3);


/**
 * @brief Affiche la liste des MCU pour une PPM.
 * 
 * @param liste_mcus liste des MCU pour une PPM.
 * @param h1 hauteur des sous-mcu pour la composante Y.
 * @param v1 largeur des sous-mcu pour la composante Y.
 * @param h2 hauteur des sous-mcu pour la composante Cb.
 * @param v2 largeur des sous-mcu pour la composante Cb.
 * @param h3 hauteur des sous-mcu pour la composante Cr.
 * @param v3 largeur des sous-mcu pour la composante Cr.
 */
extern void affiche_mcus_ppm(Mcu_ppm* liste_mcus, unsigned int h1, unsigned int v1, unsigned int h2, unsigned int v2, unsigned int h3, unsigned int v3);


/**
 * @brief Libère un élément de type Mcu_ppm.
 * 
 * @param liste_mcus élément à libérer.
 */
extern void libere_liste_mcus_ppm(Mcu_ppm* liste_mcus);

#endif