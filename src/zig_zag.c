#include "../include/zig_zag.h"

unsigned int zig_zag_coeff(unsigned int x, unsigned int y, unsigned int taille){
    if ((x + y) < taille){
        if ((x + y) % 2 == 0){
            return 0.5 * ((x + y) * (x + y + 1)) + y;
        }
        return 0.5 * ((x + y) * (x + y + 1)) + x;
    }

    int r = (x + y) - taille + 1;
    if ((x + y) % 2 == 0){
        return 0.5 * ((x + y) * (x + y + 1)) + y - r*r;
    } 
    else {
        return 0.5 * ((x + y) * (x + y + 1)) + x - r*r;
    }
}


Bloc_ZZ* zig_zag(Bloc* bloc){
    if (bloc == NULL){
        return NULL;
    }
    Bloc_ZZ* zz = (Bloc_ZZ* )malloc(sizeof(Bloc_ZZ));
    if (zz == NULL) {
        perror("Echec: Allocation (malloc) pour zz (Bloc_ZZ*).\n");
        return NULL;
    }
    for (unsigned int x = 0; x < TAILLE_BLOC; x++){
        for (unsigned int y = 0; y < TAILLE_BLOC; y++){
            zz->vecteur_pixels_zz[zig_zag_coeff(x, y, TAILLE_BLOC)] = bloc->matrice_pixels[x][y];
        }
    }
    return zz;
}

void libere_zig_zag(Bloc_ZZ* zz){
    if (zz != NULL){
        free(zz);
    }
}

void affiche_zig_zag(Bloc_ZZ* zz){
    for(unsigned int x = 0; x < (TAILLE_BLOC_ZZ); x++){
        if (x != 0 && (x%8==0)) {
            printf("\n");
        }
        printf("%04x ", zz->vecteur_pixels_zz[x].peu_importe);
    }
}

#ifdef EXECUTE_MAIN_ZIG_ZAG
Bloc* cree_bloc_zz_gris_test(){
    Bloc* bloc = (Bloc* )malloc(sizeof(Bloc));
    if (bloc == NULL){
        perror("Echec: Allocation (malloc) pour bloc (Bloc*).\n");
        return NULL;
    }
    int16_t valeur_composante = 0;
    for (unsigned int x = 0; x < TAILLE_BLOC; x++){
        for (unsigned int y = 0; y < TAILLE_BLOC; y++){
            bloc->matrice_pixels[x][y].peu_importe = valeur_composante%256;
            valeur_composante++;
        }
    }
    return bloc;
}

void affiche_bloc(Bloc* bloc){
    
    if (bloc == NULL) {
        printf("Le bloc est NULL.\n");
        return;
    }
    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
        printf("%04x, ", bloc->matrice_pixels[i][j].peu_importe);
        }
        printf("\n");
    }
}

void libere_bloc_pour_zz(Bloc* bloc){
    if (bloc != NULL){
        free(bloc);
    }
}

int main() {
    unsigned int taille = 8;
    Bloc* bloc = NULL;
    Bloc_ZZ* bloc_zz = NULL;
    bloc = cree_bloc_zz_gris_test(taille);
    bloc_zz = zig_zag(bloc);
    printf("Bloc avant transformation en zig-zag:\n");
    affiche_bloc(bloc);
    printf("=============================\n");
    printf("Bloc après transformation en zig-zag:\n");
    affiche_zig_zag(bloc_zz);
    libere_bloc_pour_zz(bloc);
    libere_zig_zag(bloc_zz);
    return EXIT_SUCCESS;
}
#endif