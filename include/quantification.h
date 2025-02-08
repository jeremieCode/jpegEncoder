#ifndef QUANTIFICATION_H
#define QUANTIFICATION_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "qtables.h"
#include "sdd.h"

/**
 * @brief Applique la quantification en place
 * 
 * @param bloc_zz Le bloc Zig-Zag à quantifier.
 * @param composante Selon le type des pixels: GRIS_COMPO, Y, CB, CR
 */
void quantification(Bloc_ZZ* bloc_zz, composante composante);
#endif