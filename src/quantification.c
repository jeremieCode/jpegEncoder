#include "../include/quantification.h"

void quantification(Bloc_ZZ* bloc_zz, composante composante){

    if (bloc_zz == NULL){
        return;
    }
    
    int16_t coeff_y = 0, coeff_cb_cr = 0;
    
    for (unsigned int i = 0; i < TAILLE_BLOC_ZZ; i++){
        // On utilise la table de la luminance 
        if (composante == GRIS_COMPO || composante == Y){
            coeff_y = (int16_t) quantification_table_Y[i];
            bloc_zz->vecteur_pixels_zz[i].peu_importe = (int16_t)(bloc_zz->vecteur_pixels_zz[i].peu_importe / coeff_y);
        }
        // On utilise la table de la chrominance
        else if (composante == CB || composante == CR){
            coeff_cb_cr = (int16_t) quantification_table_CbCr[i];
            bloc_zz->vecteur_pixels_zz[i].peu_importe = (int16_t)(bloc_zz->vecteur_pixels_zz[i].peu_importe / coeff_cb_cr);
        }
    }
}

#ifdef EXECUTE_MAIN_QUANTIFICATION
int main() {
    printf("On testera peut-être plus tard (si on a le temps) car le code est facile...\n");
    return EXIT_SUCCESS;
}
#endif
