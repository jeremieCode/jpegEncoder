#include <paramcomm.h>

Entree* param_entree(int argc, char* argv[]) {
    Entree* entree =  (Entree*) malloc(sizeof(Entree));
    if (entree == NULL) {
        perror("Échec allocation de entree\n");
        return NULL;
    }
    entree->outfile = NULL;
    entree->fichier = NULL;
    entree->sample = NULL;
    entree->sample_int = NULL;
    entree->verbose = 0;
    if (argc == 1) {
        printf("Echec d'utilisation: voir ./ppm2jpg --help \n");
        return entree;
    };
    int index = 1;
    while (index < argc) {
        int verif = lis_param(argv[index], entree);
        if (!verif) {
            free(entree);
            return NULL;
        }
        index++;
    }
    if (entree->outfile == NULL) {
        int n = strlen(entree->fichier);
        char* fichier_outfile = (char*) malloc((n+1)*sizeof(char));
        if (fichier_outfile == NULL) {
            perror("Échec allocation fichier_outfile\n");
            free(entree);
            return NULL;
        }
        memcpy(fichier_outfile, entree->fichier, n-3);
        fichier_outfile[n] = '\0';
        fichier_outfile[n-1] = 'g';
        fichier_outfile[n-2] = 'p';
        fichier_outfile[n-3] = 'j';
        entree->outfile = fichier_outfile;
    }
    entree->sample_int = valeur_sampling(entree);
    return entree;
}

int est_valide(int h_or_v) {
    if (h_or_v == 1 || h_or_v == 2 || h_or_v == 3 || h_or_v == 4) {
        return 1;
    }
    return 0;
}

int divise(int a, int b) {
    if (b%a == 0) {
        return 1;
    }
    return 0;
}

int* valeur_sampling(Entree* entree) {
    int* val_sample = (int*) calloc(6,sizeof(int));
    if (entree->sample != NULL) {
        int n = strlen(entree->sample);
        assert(val_sample);
        if (n > 2) {
            val_sample[0] = entree->sample[0] - '0';
            val_sample[1] = entree->sample[2] - '0';
            if (n > 6) {
                val_sample[2] = entree->sample[4] - '0';
                val_sample[3] = entree->sample[6] - '0';
                if (n > 10) {
                    val_sample[4] = entree->sample[8] - '0';
                    val_sample[5] = entree->sample[10] - '0';
                }
            }
        }
    } else {
        for (int i = 0; i < 6; i++) {
            val_sample[i] = 1;
        }
    }
    return val_sample;
}

int verif_sample(char* val_sample) {
    int taille_sample = strlen(val_sample);
    int index = 0;
    char ccurent = val_sample[index];
    /* Facteur pour la luminance */
    int h_l = 0, v_l = 0;
    /* Les autres facteurs */
    int h_i = 0, v_i = 0;
    int prod_tot = 0;
    /* Vérifie si on check bien la luminance */
    int lumi = 0;
    /* Vérifie si on est sur h ou v */
    int compte = 0;
    while (index < taille_sample) {
        while (ccurent != ',' && ccurent != '\0' && index < taille_sample) {
            if (ccurent != 'x') {
                if (compte == 0) {
                    if (!lumi) {
                        h_l = ccurent - '0';
                    } else {
                        h_i = ccurent - '0';
                    }
                    compte = 1;
                } else {
                    if (!lumi) {
                        v_l = ccurent - '0';
                        prod_tot = h_l*v_l;
                    } else {
                        v_i = ccurent - '0';
                    }
                    compte = 0;
                }
            }
            index++;
            ccurent = val_sample[index];
        }
        if (ccurent == ',') {
            index++;
            ccurent = val_sample[index];
        }
        prod_tot = prod_tot + h_i*v_i;
        if (prod_tot > 10) {
            printf("La somme des produits est supérieure à 10 \n");
            return 0;
        }
        if (!lumi) {
            if (!est_valide(h_l) || !est_valide(v_l)) {
                printf("Les facteurs de luminance ne sont pas tous compris entre 1 et 4\n");
                return 0;
            }
        } else {
            if (!est_valide(h_i) || !est_valide(v_i)) {
                printf("Les facteurs de chrominance ne sont pas tous compris entre 1 et 4\n");
                return 0;
            } else if (!divise(h_i, h_l) || !divise(v_i, v_l)) {
                printf("Les facteurs de chrominance ne divisent pas parfaitement ceux de luminance \n");
                return 0;
            }
        }
        lumi = 1;
    }
    return 1;
}

int lis_param(char* param, Entree* entree) {
    int choix = reconnait_param(param);
    if (choix == HELP) {
        printf("Utilisation : ./ppm2jpg <fichier.{pgm|ppm}> \n");
        printf("Option : \n");
        printf("  --help \n");
        printf("  --outfile=chemin/de/sortie/sortie.jpg\n");
        printf("  --sample=h1xv1,h2xv2,h3xv3\n");
        printf("  --verbose\n");
    } else if (choix == OUTFILE) {
        uint8_t cc_x = 10;
        int taille_param = strlen(param) - 10;
        char ccurent = param[cc_x];
        char* nom_outfile = (char*) malloc((taille_param+1)*sizeof(char));
        if (nom_outfile == NULL) {
            perror("Échec allocation nom_outfile\n");
            return 0;
        }
        int index = 0;
        while (index < taille_param) {
            nom_outfile[index] = ccurent;
            index++, cc_x++;
            ccurent = param[cc_x];
        }
        nom_outfile[index] = '\0';
        entree->outfile = nom_outfile;
    } else if (choix == SAMPLE) {
        uint8_t cc_x = 9;
        int taille_param = strlen(param) - 9;
        char ccurent = param[cc_x];
        char* val_sample = (char*) malloc((taille_param+1)*sizeof(char));
        if (val_sample == NULL) {
            perror("Échec allocation val_sample\n");
            return 0;
        }
        int index = 0;
        while (index < taille_param) {
            val_sample[index] = ccurent;
            index++, cc_x++;
            ccurent = param[cc_x];
        }
        val_sample[index] = '\0';
        if (verif_sample(val_sample)) {
            entree->sample  = val_sample;
        } else {
            printf("Erreur de format de sampling \n");
            return 0;
        }
    } else if (choix == FICHIER_PGM) {
        entree->fichier  = param;
        entree->type = GRIS;
    } else if (choix == FICHIER_PPM) {
        entree->fichier = param;
        entree->type = RGB;
    } else if (choix == VERBOSE) {
        entree->verbose = 1;
    }
    else {
        printf("Erreur de paramètre, voir ./ppm2jpg --help \n");
        return 0;
    }
    return 1;
}

int reconnait_param(char* param) {
    char* param_slice1 = (char*) malloc(11*sizeof(char));
    if (param_slice1 == NULL) {
        perror("Échec allocation param_slice1\n");
        return -1;
    }
    char* param_slice2 = (char*) malloc(10*sizeof(char));
    if (param_slice2 == NULL) {
        perror("Échec allocation param_slice2\n");
        return -1;
    }
    char* param_slice3 = (char*) malloc(10*sizeof(char));
    if (param_slice3 == NULL) {
        perror("Échec allocation param_slice3\n");
        return -1;
    }
    int choix;
    memcpy(param_slice1, param, 10);
    param_slice1[10] = '\0';
    memcpy(param_slice2, param, 9);
    param_slice2[9] = '\0';
    memcpy(param_slice3, param, 9);
    param_slice3[9] = '\0';
    unsigned int taille_ch = strlen(param);
    if (!strcmp(param,"--help")) {
        choix = HELP;
    }
    else if (!strcmp(param_slice1,"--outfile=")) {
        choix = OUTFILE;
    }
    else if (!strcmp(param_slice2,"--sample=")) {
        choix = SAMPLE;
    }
    else if (!strcmp(param_slice3,"--verbose")) {
        choix = VERBOSE;
    }
    else if (param[taille_ch-1] == 'm' && param[taille_ch-2] == 'g' && param[taille_ch-3] == 'p') {
        choix = FICHIER_PGM;
    }
    else if (param[taille_ch-1] == 'm' && param[taille_ch-2] == 'p' && param[taille_ch-3] == 'p') {
        choix = FICHIER_PPM;
    }
    else {
        choix = -1;
    }
    free(param_slice1);
    free(param_slice2);
    free(param_slice3);
    return choix;
}

void libere_entree(Entree* entree) {
    if (entree !=  NULL) {
        free(entree->outfile);
        free(entree->sample);
        free(entree->sample_int);
        free(entree);
    }
}

void affiche_entree(Entree* entree) {
    if (entree == NULL){
        printf("L'entrée est nulle.\n");
        return;
    }
    printf("  Paramètre d'entrée :\n");
    if (entree->fichier != NULL) {
        printf("\t-Entrée : %s\n",entree->fichier);
    } else {
        printf("\t-Entrée : erreur, non spécifié\n");
    }
    if (entree->sample != NULL) {
        printf("\t-Sample : %s\n",entree->sample);
    } else {
        printf("\t-Sample : non spécifié (4:4:4 par défaut)\n");
    }
    if (entree->outfile != NULL) {
        printf("\t-Sortie : %s\n",entree->outfile);
    } else {
        printf("\t-Sortie : non spécifié (1x1,1x1,1x1 par défaut)\n");
    }
}

#ifdef EXECUTE_MAIN_PARAMCOMM

int main(int argc, char* argv[]) {
    Entree* entree = param_entree(argc, argv);
    /* Pour vérifier que l'entrée soit conforme :*/
    affiche_entree(entree);
    libere_entree(entree);
    return 0;
}

#endif