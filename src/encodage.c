#include <encodage.h>
#include <time.h>

int main(int argc, char* argv[]) {

    double debut = clock();

    Entree* entree = param_entree(argc, argv); /* Allocation à libérer */


    if (entree == NULL || entree->fichier == NULL) {
        perror("Erreur : Entrée invalide ou fichier d'entrée/sortie non spécifié.");
        return EXIT_FAILURE;
    }
    
    uint8_t verb = 0;
        if (entree->verbose) {
            verb++;
    }
    
    FILE* fichier = NULL;
    FILE* fichier_final = NULL;
    fichier = fopen(entree->fichier, "rb");
    if (fichier == NULL){
        perror("Echec: Problème d'ouverture du fichier");
        libere_entree(entree);
        return EXIT_FAILURE;
    }

    // float ** tab_cos = NULL;
    // float **tab_cos = creer_tab_cos(); /* Allocation à libérer */

    printf("---------- Début de l'exécution ----------\n");

    affiche_entree(entree);

    if (entree->type == GRIS){

        Pgm* pgm = lire_image_pgm(fichier); /* Allocation à libérer */
        fclose(fichier);

        if (pgm == NULL){
            perror("Echec: Problème lors de la lecture de l'image pgm (Pgm*) est nulle");
            // libere_tab_2D(tab_cos, TAILLE_BLOC);
            libere_entree(entree);
            return EXIT_FAILURE;
        }
        

        Mcu_pgm* mcu = NULL;
        decoupage_en_mcus_pgm(pgm, &mcu); /* Allocation ici */
        Mcu_pgm* mcu_senti = mcu;
        Bloc* bloc_actuel = NULL;
        Bloc* bloc_dct = NULL;
        Bloc_ZZ* bloc_precedent = NULL;
        Bloc_ZZ* bloc_zz_actuel = NULL;
        composante composante = GRIS_COMPO;
        
        //Écriture des entêtes jpeg
        fichier_final = fopen(entree->outfile, "w");
        ecriture_entete_pgm(fichier_final, entree, pgm);
        Byte *reste = creer_byte(); /* Allocation ici */

        //DCT, Zig-Zag, Codage RLE et écriture à la volée
        int index = 0;
        while (mcu != NULL){

            bloc_precedent = bloc_zz_actuel;
            bloc_actuel = &(mcu->bloc_gris);
            if (verb) {
                printf("\n------- MCU n°%d -------\n\n",index);
                printf("Conversion en Y/Cb/Cr :\n");
                affiche_bloc(bloc_actuel);
                printf("\n");
            }
            // bloc_dct = dct_opt_1(bloc_actuel, tab_cos);
            bloc_dct = dct_opt_2(bloc_actuel); /* Allocation ici */
            if (verb) {
                printf("DCT :\n");
                affiche_bloc(bloc_dct);
                printf("\n");
            }
            bloc_zz_actuel = zig_zag(bloc_dct); /* Allcoation ici */
            if (verb) {
                printf("Zig Zag :\n");
                affiche_zig_zag(bloc_zz_actuel);
                printf("\n\n");
            }
            libere_bloc(bloc_dct);
            quantification(bloc_zz_actuel, composante);
            if (verb) {
                printf("Après quantification:\n");
                affiche_zig_zag(bloc_zz_actuel);
                printf("\n\n");
            }
            Encode_composante** encodage_final = encodage_rle_huffman(bloc_zz_actuel, bloc_precedent, composante); /* Allocation ici: fail normalement*/
            if (verb) {
                printf("Encodage RLE:\n");
                affiche_encodage(encodage_final);
                printf("\n\n");
            }
            ecris_bitstream(fichier_final, encodage_final, reste);
            libere_encode_composante(encodage_final);
            libere_zig_zag(bloc_precedent);
            mcu = mcu->suivant;
            index++;
        }

        libere_zig_zag(bloc_zz_actuel);
        ecris_byte_restant(fichier_final, reste);
        ecriture_fin(fichier_final); 

        free(reste);
        libere_liste_mcus_pgm(mcu_senti);
        free(mcu);
        libere_pgm(pgm);
    }

    else{

        Ppm* ppm = lire_image_ppm(fichier);
        fclose(fichier);

        if (ppm == NULL){
            perror("Echec: Problème lors de la lecture de l'image ppm (Ppm*) est nulle");
            libere_entree(entree);
            return EXIT_FAILURE;
        }

        Mcu_ppm* mcu = NULL;
        int h1 = entree->sample_int[0];
        int v1 = entree->sample_int[1];
        int h2 = entree->sample_int[2];
        int v2 = entree->sample_int[3];
        int h3 = entree->sample_int[4];
        int v3 = entree->sample_int[5];
        decoupage_en_mcus_ppm(ppm, &mcu, h1, v1, h2, v2, h3, v3);
        Mcu_ppm* mcu_senti = mcu;
        Bloc* bloc_actuel = NULL;
        Bloc* bloc_dct = NULL;
        Bloc_ZZ* bloc_precedent_y = NULL;
        Bloc_ZZ* bloc_zz_actuel_y = NULL;
        Bloc_ZZ* bloc_precedent_cb = NULL;
        Bloc_ZZ* bloc_zz_actuel_cb = NULL;
        Bloc_ZZ* bloc_precedent_cr = NULL;
        Bloc_ZZ* bloc_zz_actuel_cr = NULL;
        
        //Écriture des entêtes jpeg
        fichier_final = fopen(entree->outfile, "w");
        ecriture_entete_ppm(fichier_final, entree, ppm);
        Byte* reste = creer_byte();

        //DCT, Zig-Zag, Codage RLE et écriture à la volée
        int index = 0;
        while (mcu != NULL){
        // Blocs Y
            for (unsigned int i = 0; i < mcu->nb_blocs_y; i++){
                bloc_precedent_y = bloc_zz_actuel_y;
                bloc_actuel = &(mcu->blocs_y[i]);
                if (verb == 1) {
                    printf("\n------- MCU n°%d -------\n\n",index);
                    printf("Conversion en Y/Cb/Cr :\n");
                    affiche_bloc(bloc_actuel);
                    printf("\n");
                }
                bloc_dct = dct_opt_2(bloc_actuel);
                // bloc_dct = dct_opt_1(bloc_actuel,tab_cos);
                if (verb) {
                    printf("DCT :\n");
                    affiche_bloc(bloc_dct);
                    printf("\n");
                }
                bloc_zz_actuel_y = zig_zag(bloc_dct);
                libere_bloc(bloc_dct);
                quantification(bloc_zz_actuel_y, Y);
                if (verb) {
                    printf("Après quantification:\n");
                    affiche_zig_zag(bloc_zz_actuel_y);
                    printf("\n\n");
                }
                Encode_composante** encodage_final = encodage_rle_huffman(bloc_zz_actuel_y, bloc_precedent_y, Y);
                if (verb) {
                    printf("Encodage RLE:\n");
                    affiche_encodage(encodage_final);
                    printf("\n\n");
                }
                ecris_bitstream(fichier_final, encodage_final, reste);
                libere_encode_composante(encodage_final);
                libere_zig_zag(bloc_precedent_y);
            }

        // Blocs Cb
            for (unsigned int i = 0; i < mcu->nb_blocs_cb; i++){
                bloc_precedent_cb = bloc_zz_actuel_cb;
                bloc_actuel = &(mcu->blocs_cb[i]);
                if (verb) {
                        printf("  Composante Cb\n\n");
                }
                // bloc_dct = dct_opt_1(bloc_actuel,tab_cos);
                bloc_dct = dct_opt_2(bloc_actuel);
                if (verb) {
                    printf("DCT :\n");
                    affiche_bloc(bloc_dct);
                    printf("\n");
                }
                bloc_zz_actuel_cb = zig_zag(bloc_dct);
                libere_bloc(bloc_dct);
                quantification(bloc_zz_actuel_cb, CB);
                if (verb) {
                    printf("Après quantification:\n");
                    affiche_zig_zag(bloc_zz_actuel_cb);
                    printf("\n\n");
                }
                Encode_composante** encodage_final = encodage_rle_huffman(bloc_zz_actuel_cb, bloc_precedent_cb, CB);
                if (verb) {
                    printf("Encodage RLE:\n");
                    affiche_encodage(encodage_final);
                    printf("\n\n");
                }
                ecris_bitstream(fichier_final, encodage_final, reste);
                libere_encode_composante(encodage_final);
                libere_zig_zag(bloc_precedent_cb);
            }

        // Blocs Cr
            for (unsigned int i = 0; i < mcu->nb_blocs_cr; i++){
                bloc_precedent_cr = bloc_zz_actuel_cr;
                bloc_actuel = &(mcu->blocs_cr[i]);
                if (verb) {
                    printf("  Composante Cr\n\n");
                }
                // bloc_dct = dct_opt_1(bloc_actuel,tab_cos);
                bloc_dct = dct_opt_2(bloc_actuel);
                if (verb) {
                    printf("DCT :\n");
                    affiche_bloc(bloc_dct);
                    printf("\n");
                }
                bloc_zz_actuel_cr = zig_zag(bloc_dct);
                libere_bloc(bloc_dct);
                quantification(bloc_zz_actuel_cr, CR);
                if (verb) {
                    printf("Après quantification:\n");
                    affiche_zig_zag(bloc_zz_actuel_cr);
                    printf("\n\n");
                }
                Encode_composante** encodage_final = encodage_rle_huffman(bloc_zz_actuel_cr, bloc_precedent_cr, CR);
                if (verb) {
                    printf("Encodage RLE:\n");
                    affiche_encodage(encodage_final);
                    printf("\n\n");
                }
                ecris_bitstream(fichier_final, encodage_final, reste);
                libere_encode_composante(encodage_final);
                libere_zig_zag(bloc_precedent_cr);
            }

            mcu = mcu->suivant;
            index++;
        }

        ecris_byte_restant(fichier_final, reste);
        ecriture_fin(fichier_final);

        /*  Libération de la mémoire cas ppm */
        libere_zig_zag(bloc_zz_actuel_y);
        libere_zig_zag(bloc_zz_actuel_cb);
        libere_zig_zag(bloc_zz_actuel_cr);
        ecris_byte_restant(fichier_final, reste);

        free(reste);
        libere_liste_mcus_ppm(mcu_senti);
        free(mcu);
        libere_ppm(ppm);

    }

    // libere_tab_2D(tab_cos, TAILLE_BLOC);
    libere_entree(entree);
    fclose(fichier_final);      
    
    double fin = clock();
    double temps =  (double) (fin-debut)/CLOCKS_PER_SEC;
    printf("  Durée d'exéction: %lfs\n",temps);
    printf("\n---------- Exécution terminée ------------\n ");
    
    return EXIT_SUCCESS;
}