#include <htables.h>
// #include "../include/htables.h"
// #include <stdint.h>


/* Table des symboles DC, Y */
uint8_t htables_symbols_DC_Y[] = {
 0x00,
 0x01, 0x02, 0x03, 0x04, 0x05,
 0x06,
 0x07,
 0x08,
 0x09,
 0x0A,
 0x0B
};

/* Table des symboles DC, Cb et Cr */
uint8_t htables_symbols_DC_CbCr[] = {
 0x00, 0x01, 0x02,
 0x03,
 0x04,
 0x05,
 0x06,
 0x07,
 0x08,
 0x09,
 0x0A,
 0x0B
};

/* Table des symboles AC, Y */
uint8_t htables_symbols_AC_Y[] = {
 /* 2 */
 0x01, 0x02,
 /* 3 */
 0x03,
 /* 4 */
 0x00, 0x04, 0x11,
 /* 5 */
 0x05, 0x12, 0x21,
 /* 6 */
 0x31, 0x41,
 /* 7 */
 0x06, 0x13, 0x51, 0x61,
 /* 8 */
 0x07, 0x22, 0x71,
 /* 9 */
 0x14, 0x32, 0x81, 0x91, 0xA1,
 /* 10 */
 0x08, 0x23, 0x42, 0xB1, 0xC1,
 /* 11 */
 0x15, 0x52, 0xD1, 0xF0,
 /* 12 */
 0x24, 0x33, 0x62, 0x72,
 /* 15 */
 0x82,
 /* 16 */
 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x25,
 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34, 0x35, 0x36,
 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46,
 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56,
 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66,
 0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76,
 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85, 0x86,
 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95,
 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4,
 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3,
 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2,
 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA,
 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
 0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5,
 0xF6, 0xF7, 0xF8, 0xF9, 0xFA
};

/* Table des symboles AC, Cb et Cr */
uint8_t htables_symbols_AC_CbCr[] = {
 /* 2 */
 0x00, 0x01,
 /* 3 */
 0x02,
 /* 4 */
 0x03, 0x11,
 /* 5 */
 0x04, 0x05, 0x21, 0x31,
 /* 6 */
 0x06, 0x12, 0x41, 0x51,
 /* 7 */
 0x07, 0x61, 0x71,
 /* 8 */
 0x13, 0x22, 0x32, 0x81,
 /* 9 */
 0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1,
 /* 10 */
 0x09, 0x23, 0x33, 0x52, 0xF0,
 /* 11 */
 0x15, 0x62, 0x72, 0xD1,
 /* 12 */
 0x0A, 0x16, 0x24, 0x34,
 /* 14 */
 0xE1,
 /* 15 */
 0x25, 0xF1,
 /* 16 */
 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27, 0x28, 0x29,
 0x2A, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43,
 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53,
 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63,
 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x73,
 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82,
 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A,
 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,
 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5,
 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE2, 0xE3, 0xE4,
 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3,
 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA
};

/*
 Table des nombres de symboles par longueur, indexée par le type
 d'échantillon (DC ou AC), la composante de couleur (Y, Cb ou Cr) et la
 longueur du symbole (comprise entre 0 et 15).
*/
uint8_t htables_nb_symb_per_lengths[NB_SAMPLE_TYPES][NB_COLOR_COMPONENTS][16] = {
 {
 /* DC */
 { 0, 1, 5, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, // Y
 { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 }, // Cb
 { 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 } // Cr
 }, {
 /* AC */
 { 0, 2, 1, 3, 3, 2, 4, 3, 5, 5, 4, 4, 0, 0, 1, 125 }, // Y
 { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 119 }, // Cb
 { 0, 2, 1, 2, 4, 4, 3, 4, 7, 5, 4, 4, 0, 1, 2, 119 } // Cr
 }
};

/*
 Table des symboles, indexée par le type d'échantillon (DC ou AC) et la
 composante de couleur (Y, Cb ou Cr).
*/
uint8_t *htables_symbols[NB_SAMPLE_TYPES][NB_COLOR_COMPONENTS] = {
 {
 /* DC */
 htables_symbols_DC_Y, // Y
 htables_symbols_DC_CbCr, // Cb
 htables_symbols_DC_CbCr // Cr
 }, {
 /* AC */
 htables_symbols_AC_Y, // Y
 htables_symbols_AC_CbCr, // Cb
 htables_symbols_AC_CbCr // Cr
 }
};

/*
 Table des longueurs des tableaux de symboles, indexée par le type
 d'échantillon (DC ou AC) et la composante de couleur (Y, Cb ou Cr).
*/
uint8_t htables_nb_symbols[NB_SAMPLE_TYPES][NB_COLOR_COMPONENTS] = {
 {
 /* DC */
 12, // Y
 12, // Cb
 12 // Cr
 }, {
 /* AC */
 162, // Y
 162, // Cb
 162 // Cr
 }
};

Arbre *creer_arbre_simple(int profondeur, char *valeur){
    Arbre *simple = malloc(sizeof(Arbre));
    simple->profondeur = profondeur;
    simple->val = valeur;
    simple->fils_droit = NULL;
    simple->fils_gauche = NULL;
    return simple;
}


void affiche_liste(Liste_arbre *liste){
    if(liste != NULL){
        while(liste->suivant != NULL){
            if (liste->arbre_huff != NULL){
                printf("%d\t",liste->arbre_huff->profondeur);
                printf("->");
            }
            liste = liste->suivant;
        }
        printf("%d\t",liste->arbre_huff->profondeur);
        printf("\n");
    }
    else{
        printf("liste vide\n");
    }
}

Liste_arbre *inverse_liste(Liste_arbre *liste){
    Liste_arbre *prec = NULL;
    Liste_arbre *courant = liste;
    Liste_arbre *suiv = NULL;
    while(courant != NULL){
        suiv = courant->suivant;
        courant->suivant = prec;
        prec = courant;
        courant = suiv;
    }
    return prec;
}


void affiche_arbre(Arbre *a){
    if(a->val[0] != '\0'){
        printf("%d ->", a->profondeur);
    }
    if(a->fils_droit != NULL){
        affiche_arbre(a->fils_droit);
    }
    if (a->fils_gauche != NULL){
        affiche_arbre(a->fils_gauche);
    }
}



Liste_arbre *insere_liste(Liste_arbre *liste, Arbre *a){
    Liste_arbre *l_a = malloc(sizeof(Liste_arbre));
    l_a->arbre_huff = a;
    l_a->suivant = NULL;
    if (liste == NULL){
        return l_a;
    }
    else if (a->profondeur < liste->arbre_huff->profondeur){
        l_a->suivant = liste;
        return l_a;
    }
    else{
        Liste_arbre *courant = liste;
        while((courant->suivant != NULL) && (courant->arbre_huff->profondeur < a->profondeur)){
            courant = courant->suivant;
        }
        l_a->suivant = courant->suivant;
        courant->suivant = l_a;
        return liste;
    }
}


Liste_arbre *creer_liste(uint8_t htables_nb_symb_per_lengths[16], uint8_t htables_symbols[]){
    Liste_arbre *l = malloc(sizeof(Liste_arbre));
    Liste_arbre *pt = l;
    char *val = malloc(6 * sizeof(char));
    uint8_t cnt = 0;
    for(int i = 0; i < 16; i++){
        for(int j = 0;j < htables_nb_symb_per_lengths[i]; j++){
            Liste_arbre *new = malloc(sizeof(Liste_arbre));
            sprintf(val,"%x",htables_symbols[cnt]);
            cnt ++;
            new->arbre_huff = creer_arbre_simple(i + 1,val);
            new->suivant = NULL;
            l->suivant = new;
            l = new;
        }
    }
    free(val);
    Liste_arbre *liste = pt->suivant;
    free(pt);
    return liste;
}


Arbre *merge(Arbre *a, Arbre *b){
    if(a == NULL){
        return b;
    }
    else if (b == NULL) return a;
    else{
    Arbre *nouv = malloc(sizeof(Arbre));
    nouv->profondeur = a->profondeur-1;
    nouv->val = "";
    nouv->fils_gauche = a;
    nouv->fils_droit = b;
    return nouv;
    }
}


Arbre *arbre_huffman(uint8_t htables_nb_symb_per_lengths[16], uint8_t htables_symbols[]){
    Liste_arbre *liste = creer_liste(htables_nb_symb_per_lengths,htables_symbols);
    int compteur;
    bool exeption = false;
    while(liste->suivant != NULL){
        compteur = 0;
        while(compteur <= 30){
            exeption = false;
            Liste_arbre *temp = NULL;
            while(liste->suivant != NULL){
                Arbre *a1 = liste->arbre_huff;
                Arbre *a2 = liste->suivant->arbre_huff;
                Liste_arbre *libere = liste;
                if (a1->profondeur == a2->profondeur){
                    if(liste->suivant->suivant != NULL){
                        liste = liste->suivant->suivant;
                        free(libere->suivant);
                        free(libere);
                    }
                    else{
                        free(liste->suivant);
                        liste->suivant = NULL;
                        exeption = true;
                    }
                    Arbre *b = merge(a1,a2);
                    temp = insere_liste(temp,b);
                }
                else{
                    temp = insere_liste(temp,liste->arbre_huff);
                    Liste_arbre *libere = liste;
                    liste = liste->suivant;
                    free(libere);
                }
            }
            if ((!exeption) && (liste != NULL)){
                temp = insere_liste(temp, liste->arbre_huff);
            }
            free(liste);
            liste = temp;
            //affiche_liste(liste);
            compteur ++;
        }
        if(liste->suivant != NULL){
            liste = inverse_liste(liste);
            Arbre *fusion = creer_arbre_simple(liste->arbre_huff->profondeur,"\0");
            Arbre *new = merge(liste->arbre_huff, fusion);
            Liste_arbre *libere_2 = liste;
            liste = liste->suivant;
            free(libere_2);
            liste = inverse_liste(liste);
            liste = insere_liste(liste,new);
        }
    }
    Arbre *res = liste->arbre_huff;
    free(liste);
    return res;
}


int indice = 0;

void table_huffman(Arbre *arbre_huffman, char *code, int profondeur, uint8_t htables_symbols[]){
    extern int indice;
    if (arbre_huffman->val[0] != '\0'){
        printf("0b%s, \t", code);
        indice = indice + 1;
    }
    if((arbre_huffman->fils_gauche != NULL) ||(arbre_huffman->fils_droit != NULL)){
            if(arbre_huffman->fils_gauche != NULL){
                code[profondeur] = '0';
                table_huffman(arbre_huffman->fils_gauche,code,profondeur + 1, htables_symbols);
            }
            if(arbre_huffman->fils_droit != NULL){
                code[profondeur] = '1';
                table_huffman(arbre_huffman->fils_droit,code,profondeur + 1, htables_symbols);
            }
    }
}


void libere_arbre(Arbre *arbre){
    if (arbre != NULL){
        libere_arbre(arbre->fils_gauche);
        libere_arbre(arbre->fils_droit);
        free(arbre);
    }
}

#ifdef EXECUTE_MAIN_HTABLES
int main(){
    // Arbre *test = malloc(sizeof(Arbre));
    // test->val = "\0";
    // test->profondeur = 0;
    // test->fils_droit = malloc(sizeof(Arbre));
    // test->fils_droit->val = "C";
    // test->fils_droit->profondeur = 1;
    // test->fils_droit->fils_droit = NULL;
    // test->fils_droit->fils_gauche = NULL;
    // test->fils_gauche = NULL;
    // Arbre *racine = malloc(sizeof(Arbre));
    // racine->val = "\0";
    // racine->profondeur = 0;
    // racine->fils_droit = malloc(sizeof(Arbre));
    // racine->fils_droit->val = "A";
    // racine->fils_droit->profondeur = 1;
    // racine->fils_droit->fils_droit = NULL;
    // racine->fils_droit->fils_gauche = NULL;
    // racine->fils_gauche = malloc(sizeof(Arbre));
    // racine->fils_gauche->val = "B";
    // racine->fils_gauche->profondeur = 1;
    //Arbre *b = merge(test,racine);
    //char *code1 = malloc(16 * sizeof(char));
    //table_huffman(b, code1, 0);
    char *code = malloc(16 * sizeof(char));
    Arbre *Y = arbre_huffman(htables_nb_symb_per_lengths[0][0],htables_symbols[0][0]);
    table_huffman(Y,code,0,htables_symbols[0][0]);
    free(code);
    libere_arbre(Y);
    return 0;
}
#endif