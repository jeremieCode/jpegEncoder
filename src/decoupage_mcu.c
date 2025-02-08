# include "../include/decoupage_mcu.h"
#include "../include/lecture_fichier.h"

void decoupage_en_mcus_pgm(Pgm* pgm, Mcu_pgm** liste_mcus){

    if (pgm == NULL){
        perror("Echec : Absence d'image pgm (Pgm*).\n");
        return;
    }

    // nombre de pixel
    unsigned int pgm_hauteur = pgm->hauteur;
    unsigned int pgm_largeur = pgm->largeur;

    // nombre de mcus pour recouvrir toute l'image
    unsigned int nb_mcu_hauteur = ceil((double) pgm_hauteur / TAILLE_MCU_PGM);
    unsigned int nb_mcu_largeur = ceil((double) pgm_largeur / TAILLE_MCU_PGM);
    
    /* On le met à null afin de commencer une nouvelle liste:
       Remarque: c'est pour cela qu'on devait passer un double pointeur 
       car on modifie le pointeur de (tete) de liste_mcus directement: 
       comme pour Alibaba et BrainFuck...
    */
    *liste_mcus = NULL;
    Mcu_pgm* mcu_precedent = NULL;
    
    for (unsigned int i = 0; i < nb_mcu_hauteur; i++){
        for (unsigned int j = 0; j < nb_mcu_largeur; j++){

            Mcu_pgm* mcu_actuel = (Mcu_pgm* )malloc(sizeof(Mcu_pgm));
            if (mcu_actuel == NULL){
                libere_liste_mcus_pgm(*liste_mcus);
                perror("Echec: Allocation (malloc) pour mcu_actuel (Mcu_pgm*).\n");
                return;
            }
            mcu_actuel->nb_blocs = nb_mcu_hauteur * nb_mcu_largeur;
            mcu_actuel->suivant = NULL;

            // On recopie chaque valeur du bloc... 
            for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                    unsigned int reel_position_hauteur = i * TAILLE_BLOC + y;
                    unsigned int reel_position_largeur = j * TAILLE_BLOC + x;
                    // On prend la dernière valeur de la ligne/colonne en cas de dépassement...
                    reel_position_hauteur = (reel_position_hauteur >= pgm_hauteur) ? pgm_hauteur - 1 : reel_position_hauteur;
                    reel_position_largeur = (reel_position_largeur >= pgm_largeur) ? pgm_largeur - 1 : reel_position_largeur;
                    mcu_actuel->bloc_gris.matrice_pixels[y][x] = pgm->matrice_gris[reel_position_hauteur][reel_position_largeur];
                }
            }
            // On ajoute le bloc actuel à la liste de nos mcus
            if (*liste_mcus == NULL){
                *liste_mcus = mcu_actuel;
            } 
            else{
                mcu_precedent->suivant = mcu_actuel;
            }
            mcu_precedent = mcu_actuel;
        }
    }
}


void decoupage_en_mcus_ppm(Ppm* ppm, Mcu_ppm** liste_mcus, unsigned int h1, unsigned int v1, unsigned int h2, unsigned int v2, unsigned int h3, unsigned int v3){
    // En réalité inutile de passer h3 et v3 car il est dit dans le sujet que c'est égale à h2 et v2...  Mais on est inviter à prévoir plus de 
    // motif de subsampling possible...
    if (ppm == NULL){
        perror("Echec : Absence d'image ppm (Ppm*).\n");
        return;
    }

    // nombre de pixel
    unsigned int ppm_hauteur = ppm->hauteur;
    unsigned int ppm_largeur = ppm->largeur;

    // nombre de mcus pour recouvrir toute l'image
    unsigned int nb_mcu_hauteur = ceil((double) ppm_hauteur / (v1 * TAILLE_MCU_PGM));
    unsigned int nb_mcu_largeur = ceil((double) ppm_largeur / (h1 * TAILLE_MCU_PGM));
    
    /* On le met à null afin de commencer une nouvelle liste:
       Remarque: c'est pour cela qu'on devait passer un double pointeur 
       car on modifie le pointeur de (tete) de liste_mcus directement: 
       comme pour Alibaba et BrainFuck...
    */
    *liste_mcus = NULL;
    Mcu_ppm* mcu_precedent = NULL;

    for (unsigned int i = 0; i < nb_mcu_hauteur; i++){
        for (unsigned int j = 0; j < nb_mcu_largeur; j++){

            Mcu_ppm* mcu_actuel = (Mcu_ppm* )malloc(sizeof(Mcu_ppm));
             if (mcu_actuel == NULL){
                libere_liste_mcus_ppm(*liste_mcus);
                perror("Echec: Allocation (malloc) pour mcu_actuel (Mcu_ppm*).\n");
                return;
            }
            
            mcu_actuel->suivant = NULL;
            mcu_actuel->nb_blocs_y = h1 * v1;
            mcu_actuel->nb_blocs_cb = h2 * v2;
            mcu_actuel->nb_blocs_cr = h3 * v3;
            mcu_actuel->blocs_y = (Bloc* )malloc(h1 * v1 * sizeof(Bloc));
            if (mcu_actuel->blocs_y == NULL){
                libere_liste_mcus_ppm(*liste_mcus);
                perror("Echec: Allocation (malloc) pour mcu_actuel->blocs_y (Bloc*).\n");
                return;
            }
            mcu_actuel->blocs_cb = (Bloc* )malloc(h2 * v2 * sizeof(Bloc));
            if (mcu_actuel->blocs_cb == NULL){
                libere_liste_mcus_ppm(*liste_mcus);
                perror("Echec: Allocation (malloc) pour mcu_actuel->blocs_cb (Bloc*).\n");
                return;
            }
            mcu_actuel->blocs_cr = (Bloc* )malloc(h3 * v3 * sizeof(Bloc));
            if (mcu_actuel->blocs_cr == NULL){
                libere_liste_mcus_ppm(*liste_mcus);
                perror("Echec: Allocation (malloc) pour mcu_actuel->blocs_cr (Bloc*).\n");
                return;
            }

            // Blocs pour composante Y
            for (unsigned int s_b_y = 0; s_b_y < v1; s_b_y++){
                for (unsigned int s_b_x = 0; s_b_x < h1; s_b_x++){
                    unsigned int s_b_pos = s_b_y * h1 + s_b_x;
                    for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                        for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                            unsigned int reel_position_hauteur = i * v1 * TAILLE_BLOC + s_b_y * TAILLE_BLOC + y;
                            unsigned int reel_position_largeur = j * h1 * TAILLE_BLOC + s_b_x * TAILLE_BLOC + x;
                            // On prend la dernière valeur de la ligne/colonne en cas de dépassement...
                            reel_position_hauteur = (reel_position_hauteur >= ppm_hauteur) ? ppm_hauteur - 1 : reel_position_hauteur;
                            reel_position_largeur = (reel_position_largeur >= ppm_largeur) ? ppm_largeur - 1 : reel_position_largeur;
                            mcu_actuel->blocs_y[s_b_pos].matrice_pixels[y][x] = ppm->matrice_y[reel_position_hauteur][reel_position_largeur];
                        }
                    }
                }
            }

            // Blocs pour composante Cb avec downsampling
            for (unsigned int s_b_y = 0; s_b_y < v2; s_b_y++){
                for (unsigned int s_b_x = 0; s_b_x < h2; s_b_x++){
                    unsigned int s_b_pos = s_b_y * h2 + s_b_x;
                    for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                        for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                            unsigned int reel_position_hauteur = i * v1 * TAILLE_BLOC + s_b_y * TAILLE_BLOC + y;
                            unsigned int reel_position_largeur = j * h1 * TAILLE_BLOC + s_b_x * TAILLE_BLOC + x;
                            // On prend la dernière valeur de la ligne/colonne en cas de dépassement...
                            reel_position_hauteur = (reel_position_hauteur >= ppm_hauteur) ? ppm_hauteur - 1 : reel_position_hauteur;
                            reel_position_largeur = (reel_position_largeur >= ppm_largeur) ? ppm_largeur - 1 : reel_position_largeur;
                            mcu_actuel->blocs_cb[s_b_pos].matrice_pixels[y][x] = ppm->matrice_cb[reel_position_hauteur][reel_position_largeur];
                        }
                    }
                }
            }

            // Blocs pour composante Cr avec downsampling
            for (unsigned int s_b_y = 0; s_b_y < v3; s_b_y++){
                for (unsigned int s_b_x = 0; s_b_x < h3; s_b_x++){
                    unsigned int s_b_pos = s_b_y * h3 + s_b_x;
                    for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                        for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                            unsigned int reel_position_hauteur = i * v1 * TAILLE_BLOC + s_b_y * TAILLE_BLOC + y;
                            unsigned int reel_position_largeur = j * h1 * TAILLE_BLOC + s_b_x * TAILLE_BLOC + x;
                            // On prend la dernière valeur de la ligne/colonne en cas de dépassement...
                            reel_position_hauteur = (reel_position_hauteur >= ppm_hauteur) ? ppm_hauteur - 1 : reel_position_hauteur;
                            reel_position_largeur = (reel_position_largeur >= ppm_largeur) ? ppm_largeur - 1 : reel_position_largeur;
                            mcu_actuel->blocs_cr[s_b_pos].matrice_pixels[y][x] = ppm->matrice_cr[reel_position_hauteur][reel_position_largeur];
                        }
                    }
                }
            }

            if (*liste_mcus == NULL){
                *liste_mcus = mcu_actuel;
            } 
            else{
                mcu_precedent->suivant = mcu_actuel;
            }
            mcu_precedent = mcu_actuel;
        }
    }
}


void affiche_mcus_pgm(Mcu_pgm* liste_mcus){
    unsigned int cpt = 0;
    while (liste_mcus != NULL){
        printf("[MCU #%u]\n", cpt);
        printf("[GRIS | Y]:\n\t");
        for (unsigned int y = 0; y < TAILLE_BLOC; y++){
            for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                printf("%02x ", liste_mcus->bloc_gris.matrice_pixels[y][x].gris);
            }
            printf("\n\t");
        }
        printf("\n");
        liste_mcus = liste_mcus->suivant;
        cpt++;
    }
}


void affiche_mcus_ppm(Mcu_ppm* liste_mcus, unsigned int h1, unsigned int v1, unsigned int h2, unsigned int v2, unsigned int h3, unsigned int v3){
    Mcu_ppm* mcu_actuelle = liste_mcus;
    unsigned int cpt = 0;
    while (mcu_actuelle != NULL){
        printf("[MCU #%u]\n", cpt);
        printf("[Y]:\n");
        for (unsigned int i = 0; i < (h1 * v1); i++){
            printf("Y_%u\n\t", i);
            for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                    printf("%02x ", mcu_actuelle->blocs_y[i].matrice_pixels[y][x].y);
                }
                printf("\n\t");
            }
            printf("\n");
        }
        printf("\n");
        printf("[Cb]:\n");
        for (unsigned int i = 0; i < h2 * v2; i++){
            printf("Cb_%u\n\t", i);
            for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                    printf("%02x ", mcu_actuelle->blocs_cb[i].matrice_pixels[y][x].y);
                }
                printf("\n\t");
            }
            printf("\n");
        }
        printf("\n");
        printf("[Cr]:\n");
        for (unsigned int i = 0; i < h3 * v3; i++){
            printf("Cr_%u\n\t", i);
            for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                    printf("%02x ", mcu_actuelle->blocs_cr[i].matrice_pixels[y][x].y);
                }
                printf("\n\t");
            }
            printf("\n");
        }
        printf("\n\n");
        mcu_actuelle = mcu_actuelle->suivant;
        cpt++;
    }
}


void libere_liste_mcus_pgm(Mcu_pgm* liste_mcus){
    if (liste_mcus != NULL){
        Mcu_pgm* bloc_courant = liste_mcus;
        Mcu_pgm* bloc_suivant = NULL;
        while (bloc_courant != NULL){
            bloc_suivant = bloc_courant->suivant;
            free(bloc_courant);
            bloc_courant = bloc_suivant;
        }
    }
}


void libere_liste_mcus_ppm(Mcu_ppm* liste_mcus){
    if (liste_mcus != NULL){
        Mcu_ppm* mcu_courant = liste_mcus;
        Mcu_ppm* mcu_suivant = NULL;
        while (mcu_courant != NULL){
            free(mcu_courant->blocs_y);
            free(mcu_courant->blocs_cb);
            free(mcu_courant->blocs_cr);
            mcu_suivant = mcu_courant->suivant;
            free(mcu_courant);
            mcu_courant = mcu_suivant;
        }
    }
}


#ifdef EXECUTE_MAIN_DECOUPAGE_MCU
int main(){
    // PGM
    FILE* fichier_pgm = fopen("./images/invader.pgm", "rb");
    if (fichier_pgm == NULL){
        perror("Echec: Problème d'ouverture du fichier PGM");
        return EXIT_FAILURE;
    }
    Pgm* pgm = lire_image_pgm(fichier_pgm);
    fclose(fichier_pgm);
    Mcu_pgm* liste_mcus_pgm = NULL;
    decoupage_en_mcus_pgm(pgm, &liste_mcus_pgm);
    affiche_mcus_pgm(liste_mcus_pgm);
    libere_liste_mcus_pgm(liste_mcus_pgm);
    libere_pgm(pgm);

    // PPM
    FILE* fichier_ppm = fopen("./images/random_20_20.ppm", "rb");
    if (fichier_ppm == NULL){
        perror("Echec: Problème d'ouverture du fichier PPM");
        return EXIT_FAILURE;
    }
    Ppm* ppm = lire_image_ppm(fichier_ppm);
    affiche_image_ppm(ppm);
    fclose(fichier_ppm);
    Mcu_ppm* liste_mcus_ppm = NULL;
    decoupage_en_mcus_ppm(ppm, &liste_mcus_ppm, 2, 2, 1, 2, 1, 2);
    affiche_mcus_ppm(liste_mcus_ppm, 2, 2, 1, 2, 1, 2);
    libere_liste_mcus_ppm(liste_mcus_ppm);
    libere_ppm(ppm);
    return EXIT_SUCCESS;
}
#endif