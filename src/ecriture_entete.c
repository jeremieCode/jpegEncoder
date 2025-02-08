#include <ecriture_entete.h>

int entete[] = {
    0xFF, 0xD8, 0xFF, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 
    0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, -1
};

char comm[] = {'#','t','e','a','m','4'};

void ecris_val_4octets(FILE* fichier, int valeur) {
    int masque = 0x00FF;
    if (valeur > 255) {
        int haut_val = valeur >> 8;
        fputc(haut_val, fichier);
        fputc(valeur & masque, fichier);
    }
    else {
        fputc(0x00,fichier);
        fputc(valeur,fichier);
    }
}

int char_to_dec(char* binaire) {
    uint16_t valeur = 0;
    int n = strlen(binaire);
    for (int i = 0; i < n; i++) {
        valeur *= 2;
        if (binaire[i]) {
            valeur++;
        }
    }
    return valeur;
}

void affiche_fichier(FILE* fichier) {
    char ccurent = fgetc(fichier);
    while (ccurent != EOF) {
        printf("%c",ccurent);
    }
    printf("\n");
}

void ecriture_comm_test(FILE* fichier) {
    /* Test de commentaire, pas nécessaire mais sympathique pour vérifier les résultats*/
    fputc(0xff,fichier);
    fputc(0xfe,fichier);
    fputc(0x00,fichier);
    fputc(0x10,fichier);
    int comm_love_jpeg[] = {0x3C, 0x33, 0x20, 0x6C, 0x65, 0x20, 0x70, 0x72, 0x6F, 0x6A, 0x65, 0x74, 0x20, 0x43};
    int taille_comm_love_jpeg = 14;
    for (int i = 0; i < taille_comm_love_jpeg; i++) {
        fputc(comm_love_jpeg[i],fichier);
    }
}

void ecriture_comm(FILE* fichier, char* comm) {
    fputc(0xff,fichier);
    fputc(0xfe,fichier);
    fputc(0x00,fichier);
    int taille_comm = strlen(comm) + 2;
    fputc(taille_comm,fichier);
    for (int i = 0; i < taille_comm - 2; i++) {
        fputc(comm[i],fichier);
    }
}

void ecriture_entete_jfif(FILE* fichier) {
    int index =  0;
    int nb =  entete[index];
    while (index != TAILLE_ENTETE) {
        fputc(nb,fichier);
        index++;
        nb = entete[index];
    }
}

void ecriture_dqt(FILE* fichier, couleur type) {
    fputc(0xFF,fichier);
    fputc(0xDB,fichier);
    fputc(0x00,fichier);
    fputc(0x43,fichier);
    fputc(0x00,fichier);
    int index = 0;
    while (index != 64) {
        int nb = quantification_table_Y[index];
        fputc(nb,fichier);
        index++;
    }
    if (type == RGB) {
        fputc(0xFF,fichier);
        fputc(0xDB,fichier);
        fputc(0x00,fichier);
        fputc(0x43,fichier);
        fputc(0x01,fichier);
        index = 0;
        while (index != 64) {
            int nb = quantification_table_CbCr[index];
            fputc(nb,fichier);
            index++;
        }
    }
}

void ecriture_frame(FILE* fichier, Entree* entree, int largeur, int hauteur, couleur type) {
    fputc(0xFF,fichier);
    fputc(0xC0,fichier);
    fputc(0x00,fichier);
    int n;
    if (type == GRIS) {
        n = 1;
        fputc(0x0B,fichier);
    } else {
        n = 3;
        fputc(0x11, fichier);
    }
    fputc(0x08,fichier);
    ecris_val_4octets(fichier, hauteur);
    ecris_val_4octets(fichier, largeur);
    fputc(n,fichier);
    for (uint8_t i = 0; i < n; i++) {
        fputc(i+1,fichier);
        int samp_affiche = 16*entree->sample_int[2*i] + entree->sample_int[2*i+1];
        fputc(samp_affiche, fichier);
        if (i == 0) {
            fputc(0x00,fichier);
        } else {
            fputc(0x01,fichier);
        }
    }
}

void ecriture_dht(FILE* fichier, int y_ou_cbcr, int dc_or_ac) {
    fputc(0xFF,fichier);
    fputc(0xC4,fichier);
    fputc(0x00,fichier);
    /* fputc de la longueur de la section */
    int longueur_table = htables_nb_symbols[dc_or_ac][y_ou_cbcr];
    int longueur_section = 1 + 1 + 1 + 16 + longueur_table;
    fputc(longueur_section, fichier);   
    int affiche = 16 * dc_or_ac + y_ou_cbcr;
    fputc(affiche, fichier);
    /* Nombre de symboles avec des codes de longueur 1 à 16*/
    for (uint8_t i = 0; i < 16; i++) {
        fputc(htables_nb_symb_per_lengths[dc_or_ac][y_ou_cbcr][i], fichier);
    }
    if (dc_or_ac == 1) {
        if (y_ou_cbcr) {
            for (int i = 0; i < longueur_table; i++) {
                fputc(htables_symbols_AC_CbCr[i],fichier);
            }
        }
        else {
            for (int i = 0; i < longueur_table; i++) {
                fputc(htables_symbols_AC_Y[i],fichier);
            }
        }
    }
    else {
        if (y_ou_cbcr) {
            for (int i = 0; i < longueur_table; i++) {
                fputc(htables_symbols_DC_CbCr[i],fichier);
            }
        }
        else {
            for (int i = 0; i < longueur_table; i++) {
                fputc(htables_symbols_DC_Y[i],fichier);
            }
        }
    }
}

void ecriture_sos(FILE* fichier, couleur type) {
    /* Entête Start of Scan */
    fputc(0xFF,fichier);
    fputc(0xDA,fichier);
    fputc(0x00,fichier);
    uint8_t n;
    if (type == GRIS) {
        n = 1;
        fputc(0x08,fichier);
        fputc(0x01,fichier);
    }
    else {
        n = 3;
        fputc(0x0C,fichier);
        fputc(0x03,fichier);
    }
    for (int i = 0; i != n; i++) {
        fputc(i+1,fichier);
        if (i == 0) {
            fputc(0x00,fichier);
        } else {
            fputc(0x11,fichier);
        }
    }
    fputc(0x00,fichier);
    fputc(0x3F,fichier);
    fputc(0x00,fichier);
}


void ecriture_fin(FILE* fichier) {
    fputc(0xFF,fichier);
    fputc(0xD9,fichier);
}

void ecriture_entete_pgm(FILE* fichier, Entree* entree, Pgm* pgm) {
    ecriture_entete_jfif(fichier);
    ecriture_comm_test(fichier);
    // ecriture_comm(fichier, comm);
    ecriture_dqt(fichier, GRIS);
    ecriture_frame(fichier, entree, pgm->largeur, pgm->hauteur, GRIS);
    ecriture_dht(fichier, 0, 0);
    ecriture_dht(fichier, 0, 1);
    ecriture_sos(fichier, GRIS);
}

void ecriture_entete_ppm(FILE* fichier, Entree* entree, Ppm* ppm) {
    ecriture_entete_jfif(fichier);
    ecriture_comm_test(fichier);
    // ecriture_comm(fichier, comm);
    ecriture_dqt(fichier, RGB);
    ecriture_frame(fichier, entree, ppm->largeur, ppm->hauteur, RGB);
    ecriture_dht(fichier, 0, 0);
    ecriture_dht(fichier, 0, 1);
    ecriture_dht(fichier, 1, 0);
    ecriture_dht(fichier, 1, 1);
    ecriture_sos(fichier, RGB);
}

#ifdef EXECUTE_MAIN_ECRITURE_ENTETE

int main() {
    /* VALEUR ARBITRAIRE DE TEST*/
    int largeur =  8, hauteur = 8;
    uint8_t horiz_samp = 1, vertic_samp = 1;
    char comm[] = {'#','t','e','a','m','4'};
    FILE* fichier = NULL;
    fichier = fopen("blabla.jpeg", "w");
    ecriture_entete_jfif(fichier);
    ecriture_comm(fichier, comm);
    couleur type = GRIS;
    int indice = 0;
    ecriture_dqt(fichier, type);
    ecriture_frame(fichier, largeur, hauteur, type, horiz_samp, vertic_samp);
    ecriture_dht(fichier, indice, 0, RGB);
    ecriture_dht(fichier, indice, 1, RGB);
    ecriture_dht(fichier, 1, 0, RGB);
    ecriture_dht(fichier, 1, 1, RGB);
    ecriture_sos(fichier, type);
    /* FIN TEST INVADERS*/

    ecriture_fin(fichier);
    affiche_fichier(fichier);
    fclose(fichier);
    return 1;
}

#endif