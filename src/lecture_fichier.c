#include "../include/lecture_fichier.h"

int lire_en_tete(FILE* fichier, char* type_lu, unsigned int* largeur, unsigned int* hauteur){

    if (fichier == NULL){
        perror("Echec: Absence de fichier (FILE*).\n");
        return -1;
    }

    if (fscanf(fichier, "%2c\n", type_lu) != 1){
        /* Normalement on passe des images valides, 
        mais ca ne coute rien de verifier ... */
        perror("Echec: Problème lors du parsage de l'image pour le format\n");
        return -1;
    }

    if (type_lu[0] != 'P'){
        /* Normalement on passe des images valides, 
        mais ca ne coute rien de verifier ... */
        perror("Echec: Problème lors du parsage de l'image pour le format ('P')\n");
        return -1;
    }

    if (fscanf(fichier, "%u %u\n", largeur, hauteur) != 2){
        /* Normalement on passe des images valides, 
        mais ca ne coute rien de verifier ... */
        perror("Echec: Problème lors du parsage de l'image pour la dimension\n");
        return -1;
    }

    uint8_t nb_val_possible;
    if (fscanf(fichier, "%hhu\n", &nb_val_possible) != 1){
        /* Normalement on passe des images valides, 
        mais ca ne coute rien de verifier ... */
        perror("Echec: Problème lors du parsage pour nombre de valeur possible.\n");
        return -1;
    }

    if (nb_val_possible != 255){
        /* Normalement on passe des images valides, 
        mais ca ne coute rien de verifier ... */
        perror("Echec: Problème le nombre de valeur possible est incorrecte.\
                On se limte seulement à des valeurs entre 0 et 255.\n");
        return -1;
    }

    return 0;
}


Pgm* lire_image_pgm(FILE* fichier){

    char type_lu[2];
    unsigned int largeur, hauteur;

    if (lire_en_tete(fichier, type_lu, &largeur, &hauteur) != 0){
        perror("Echec: Problème lors du parsage de l'image...\n");
        return NULL;
    } 
    
    if(type_lu[1] != '5'){
        perror("Echec: Echec: Problème lors du parsage de l'image pour le format \
                n'est pas suporté par notre encodeur (uniquement format 'P5' ou 'P6').\n");
        return NULL;
    }

    Pgm* pgm = (Pgm*)malloc(sizeof(Pgm));
    if (pgm == NULL){
        perror("Echec: Allocation (malloc) pour pgm (Pgm*).\n");
        return NULL;
    }

    pgm->hauteur = hauteur;
    pgm->largeur = largeur;
    pgm->matrice_gris = alloue_matrice_ppgm(hauteur, largeur);
    if (pgm->matrice_gris == NULL){
        perror("Echec: Allocation (calloc) pour ppm->matrice_gris (Pixel**).\n");
        free(pgm);
        return NULL;
    }

    int gris;

    for (unsigned int i = 0; i < hauteur; i++){
        for (unsigned int j = 0; j < largeur; j++){
            gris = fgetc(fichier);
                /* [...] */
                if (gris == EOF){
                    perror("Echec : Probleme lors du parsage des valeurs gris du pixel (EOF atteint).\n");
                    libere_pgm(pgm);
                    return NULL;
                }
                pgm->matrice_gris[i][j].gris = (int16_t)gris;
        }
    }
    return pgm;
}


Ppm* lire_image_ppm(FILE* fichier){

    char type_lu[2];
    unsigned int largeur, hauteur;

    if (lire_en_tete(fichier, type_lu, &largeur, &hauteur) != 0){
        perror("Echec: Problème lors du parsage de l'image...\n");
        return NULL;
    } 
    
    if(type_lu[1] != '6'){
        perror("Echec: Echec: Problème lors du parsage de l'image pour le format \
                n'est pas suporté par notre encodeur (uniquement format 'P5' ou 'P6').\n");
        return NULL;
    }

    Ppm* ppm = (Ppm*)malloc(sizeof(Ppm));
    if (ppm == NULL){
        perror("Echec: Allocation (malloc) pour ppm (Ppm*).\n");
        return NULL;
    }

    ppm->hauteur = hauteur;
    ppm->largeur = largeur;
    ppm->matrice_y = alloue_matrice_ppgm(hauteur, largeur);
    if (ppm->matrice_y == NULL){
        perror("Echec: Allocation (calloc) pour pgm->matrice_y (Pixel**).\n");
        free(ppm);
        return NULL;
    }
    ppm->matrice_cb = alloue_matrice_ppgm(hauteur, largeur);
    if (ppm->matrice_cb == NULL){
        perror("Echec: Allocation (calloc) pour pgm->matrice_cb (Pixel**).\n");
        libere_ppm(ppm);
        return NULL;
    }
    ppm->matrice_cr = alloue_matrice_ppgm(hauteur, largeur);
    if (ppm->matrice_cr == NULL){
        perror("Echec: Allocation (calloc) pour ppm->matrice_cr (Pixel**).\n");
         libere_ppm(ppm);
        return NULL;
    }

    int16_t r, g, b;
    for (unsigned int i = 0; i < hauteur; i++){
        for (unsigned int j = 0; j < largeur; j++){
            r = fgetc(fichier);
            g = fgetc(fichier);
            b = fgetc(fichier);
            /* [...] */
            if (r == EOF || g == EOF || b == EOF){
                perror("Echec : Probleme lors du parsage des valeurs RGB du pixel (EOF atteint).\n");
                libere_ppm(ppm);
                return NULL;
            }
            ppm->matrice_y[i][j].y = converti_y(r, g, b);
            ppm->matrice_cb[i][j].cb = converti_cb(r, g, b);
            ppm->matrice_cr[i][j].cr = converti_cr(r, g, b);
        }
    }
    return ppm;
}


int16_t converti_y(int16_t r, int16_t g, int16_t b){
    return (int16_t) (roundf(0.299*r + 0.587*g + 0.114*b));
};

int16_t converti_cb(int16_t r, int16_t g, int16_t b){
    return (int16_t) (roundf(-0.1687*r - 0.3313*g + 0.5*b + 128.0));
};

int16_t converti_cr(int16_t r, int16_t g, int16_t b){
    return (int16_t) (roundf(0.5*r - 0.4187*g - 0.0813*b + 128.0));
};


Pixel** alloue_matrice_ppgm(unsigned int hauteur, unsigned int largeur){

    Pixel** matrice = (Pixel** )calloc(hauteur, sizeof(Pixel*));
    if (matrice == NULL){
        return NULL;
    }
    for (unsigned int i = 0; i < hauteur; i++){
        matrice[i] = (Pixel* )calloc(largeur, sizeof(Pixel));
        if (matrice[i] == NULL){
            for (unsigned int j = 0; j < i; j++){
                free(matrice[j]);
            }
            free(matrice);
            return NULL;
        }
    }
    return matrice;
}


void libere_matrice_pixel(Pixel** matrice, unsigned int hauteur){

    if (matrice != NULL){
        for (unsigned int i = 0; i < hauteur; i++){
            if (matrice[i] != NULL){
                free(matrice[i]);
            }
        }
        free(matrice);
    }
}


void libere_pgm(Pgm* pgm){

    if (pgm != NULL){
        libere_matrice_pixel(pgm->matrice_gris, pgm->hauteur);
        free(pgm);
    }
}


void libere_ppm(Ppm* ppm){

    if (ppm != NULL){
        unsigned int hauteur = ppm->hauteur;
        libere_matrice_pixel(ppm->matrice_y, hauteur);
        libere_matrice_pixel(ppm->matrice_cb, hauteur);
        libere_matrice_pixel(ppm->matrice_cr, hauteur);
        free(ppm);
    }
}


void affiche_image_pgm(Pgm* pgm){
    if (pgm == NULL){
        perror("Echec : Pas d'image pgm (Pgm*).\n");
        return;
    }
    printf("Type: PGM.\n");
    printf("Hauteur: %u\n", pgm->hauteur);
    printf("Largeur: %u\n", pgm->largeur);
    printf("Matrice de pixel:\n");
    for (unsigned int i = 0; i < pgm->hauteur; i++){
        for (unsigned int j = 0; j < pgm->largeur; j++){
            printf("%02x ", pgm->matrice_gris[i][j].gris);
        }
        printf("\n");
    }
}


void affiche_image_ppm(Ppm* ppm){
    if (ppm == NULL){
        perror("Echec : Pas d'image ppm (Ppm*).\n");
        return;
    }
    printf("Type: PPM.\n");
    printf("Hauteur: %u\n", ppm->hauteur);
    printf("Largeur: %u\n", ppm->largeur);
    printf("Matrice de pixel:\n");
    for (unsigned int i = 0; i < ppm->hauteur; i++){
        if ((i % (TAILLE_BLOC)) == 0){
                printf("\n");
            }
        for (unsigned int j = 0; j < ppm->largeur; j++){
            if ((j % (TAILLE_BLOC)) == 0){
                printf("| ");
            }
            printf("%02x-%02x-%02x ", ppm->matrice_y[i][j].y, \
            ppm->matrice_cb[i][j].cb, ppm->matrice_cr[i][j].cr);
        }
        printf("\n");
    }
}


void ecrit_image_pgm(Pgm* pgm, const char* nom_du_fichier){
    /* ATTENTION ECRIT LE FICHIER AU FORMAT RGB, COMME VU EN BPI, PAS EN BINARISE !!
    Si on ne décommente pas les lignes 142 à 145, l'image n'est pas en RGB. */
    if (pgm == NULL){
        perror("Echec : Absence d'image pgm (Pgm*).\n");
        return;
    }
    FILE* fichier = NULL;
    fichier = fopen(nom_du_fichier, "w");
    if (fichier == NULL){
        perror("Echec: problème à l'ouverture du fichier (FILE*).\n");
        return;
    }
        fprintf(fichier, "P2\n");
    fprintf(fichier, "%u %u\n", pgm->largeur, pgm->hauteur);
    fprintf(fichier, "255\n");
    for (unsigned int i = 0; i < pgm->hauteur; i++){
        for (unsigned int j = 0; j < pgm->largeur; j++){
            fprintf(fichier, "%d ", pgm->matrice_gris[i][j].gris);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}


void ecrit_image_ppm(Ppm* ppm, const char* nom_du_fichier){
    /* ATTENTION ECRIT LE FICHIER AU FORMAT RGB, COMME VU EN BPI, PAS EN BINARISE !!
    Si on ne décommente pas les lignes 142 à 145, l'image n'est pas en RGB. */
    if (ppm == NULL){
        perror("Echec : Absence d'image ppm (Ppm*).\n");
        return;
    }
    FILE* fichier = NULL;
    fichier = fopen(nom_du_fichier, "w");
    if (fichier == NULL){
        perror("Echec: problème à l'ouverture du fichier (FILE*).\n");
        return;
    }
        fprintf(fichier, "P3\n");
    fprintf(fichier, "%u %u\n", ppm->largeur, ppm->hauteur);
    fprintf(fichier, "255\n");
    for (unsigned int i = 0; i < ppm->hauteur; i++){
        for (unsigned int j = 0; j < ppm->largeur; j++){
            fprintf(fichier, "%d %d %d ", ppm->matrice_y[i][j].y, ppm->matrice_cb[i][j].cb, 
                    ppm->matrice_cr[i][j].cr);

        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}


void affiche_bloc(Bloc* bloc){
    if (bloc != NULL){
        for (unsigned int i = 0; i < TAILLE_BLOC; i++){
            for (unsigned int j = 0; j < TAILLE_BLOC; j++){
                printf("%04x ", bloc->matrice_pixels[i][j].peu_importe);
            }
            printf("\n");
        }
    }
    
}



#ifdef EXECUTE_MAIN_LECTURE_FICHIER
int main(){
    // PPM
    FILE* fichier_ppm = NULL;
    fichier_ppm = fopen("./images/thumbs.ppm", "rb");
    if (fichier_ppm == NULL) {
        perror("Echec: Problème d'ouverture du fichier PPM");
        return EXIT_FAILURE;
    }
    Ppgm* ppm = lire_image(fichier_ppm);
    fclose(fichier_ppm);
    affiche_image(ppm);
    ecrit_image(ppm, "img_1_gen.ppm");
    // PGM
    FILE* fichier_pgm = fopen("./images/my-gris.pgm", "rb");
    if (fichier_pgm == NULL){
        perror("Echec: Problème d'ouverture du fichier PGM");
        return EXIT_FAILURE;
    }
    Pgm* pgm = lire_image_pgm(fichier_pgm);
    fclose(fichier_pgm);
    affiche_image(pgm);
    ecrit_image(pgm, "img_2_gen.pgm");
    free
    libere_ppgm(ppm);
    libere_ppgm(pgm);
    return EXIT_SUCCESS;
}
#endif
