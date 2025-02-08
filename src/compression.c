
#include <compression.h>
#include <tables_huffman.h>
#include <htables.h>

// #include "../include/compression.h"
// #include "../include/tables_huffman.h"
// #include "../include/htables.h"


/* Fonction qui renvoie la partie entière log en base 2 de la valeur absolue d'un nombre pour trouver sa classe*/
int magnitude(int p){
    int cnt = 0;
    while (p != 0){
        p = p / 2;
        cnt = cnt + 1;
    }
    return cnt;
}


uint16_t num_classe(uint16_t val, uint8_t classe){
    if(val > 0){
        return val;
    }
    else{
        val = val + ((1 << classe) - 1);
    }
    return val;
}


uint16_t num_classe_entier(int16_t val, uint8_t classe){
    uint16_t p;
    if(val > 0){
        p = (uint16_t) val;
    }
    else{
        val = val + ((1 << classe) - 1);
        p = (uint16_t) val;
    }
    return p;
}


int trouve_indice(uint8_t val, uint8_t htables_symbols[], uint8_t size){
    for (int i = 0; i < size; i++){
        if(val == htables_symbols[i]){
            return i;
        }
    }
    return -1;
}


uint8_t profondeur_huffman(int p, uint8_t htables_nb_symb_per_lengths[16]){
    for (unsigned int i = 0; i < 16; i++){
        if (p < 0){
            return i;
        }
        p -= htables_nb_symb_per_lengths[i];
    }
    return 16;
}


Tuple_encodage_sans_huffman **codage_rle(Bloc_ZZ *bloc_entree){
    Tuple_encodage_sans_huffman **tab = malloc(TAILLE_BLOC_ZZ * sizeof(Tuple_encodage_sans_huffman*));
    if (tab == NULL){
        perror("Échec allocation de tab (Tuple_encodage_sans_huffman)\n");
        return NULL;
    }
    for (int i = 0; i < TAILLE_BLOC_ZZ; i++){
        tab[i] = NULL;
    }


    uint16_t cnt = 0;
    int indice = 1;
    int nb_16 = 0;
    uint8_t last_check = 0;
    for (unsigned int i = 1; i < TAILLE_BLOC_ZZ ; i ++){
        if (cnt == 16) {
            nb_16++;
            cnt = 0;
        }
        if (bloc_entree->vecteur_pixels_zz[i].peu_importe == 0) {
                cnt++;
        }
        else{
            while (nb_16 > 0) {
                Tuple_encodage_sans_huffman *t_1 = malloc(sizeof(Tuple_encodage_sans_huffman));
                if (t_1 == NULL){
                    return NULL;
                }
                t_1->nb0_magnitude = 0xF0;
                t_1->indice_classe = 0b0;
                t_1->classe = 0;
                t_1->fin = 0;
                tab[indice] = t_1;

                indice++;
                nb_16--;
            }
            if (i == 63) {
                last_check = 1;
            }


            Tuple_encodage_sans_huffman *t_2 = malloc(sizeof(Tuple_encodage_sans_huffman));
            if (t_2 == NULL){
                return NULL;
            }

            uint8_t temp = magnitude(bloc_entree->vecteur_pixels_zz[i].peu_importe);
            uint16_t premier_bits = cnt << 4;
            t_2->nb0_magnitude = premier_bits + temp;
            t_2->indice_classe = num_classe_entier(bloc_entree->vecteur_pixels_zz[i].peu_importe,temp);
            t_2->classe = temp;

            if (last_check) {
                t_2->fin = 1;
            }
            else t_2->fin = 0;

            tab[indice] = t_2;
            indice++;
            cnt = 0;
        }
    }

    if (!last_check) {
        Tuple_encodage_sans_huffman *t_3 = malloc(sizeof(Tuple_encodage_sans_huffman));
        if (t_3 == NULL){
                return NULL;
        }
        t_3->nb0_magnitude = 0x00;
        t_3->indice_classe = 0b00;
        t_3->classe = 0;
        t_3->fin = 1;
        tab[indice] = t_3;
    }

    return tab;
}


Tuple_encodage_avec_huffman **composante_DC(Tuple_encodage_avec_huffman **encode, uint16_t *table_huffman_DC, uint8_t htables_symbols_DC[], Bloc_ZZ *zz, Bloc_ZZ *prec, uint8_t htables_nb_symb_per_lengths[16]){
    int16_t y_temp;
    if (prec == NULL){
        y_temp = zz->vecteur_pixels_zz[0].peu_importe;
    }
    else y_temp = zz->vecteur_pixels_zz[0].peu_importe - prec->vecteur_pixels_zz[0].peu_importe;


    int y_magn = magnitude(y_temp);
    int p = trouve_indice(y_magn,htables_symbols_DC,12);
    Tuple_encodage_avec_huffman *t_0 = malloc(sizeof(Tuple_encodage_avec_huffman));
    if (t_0 == NULL){
        return NULL;
    }
    t_0->nb0_magnitude_huff =  table_huffman_DC[p];
    t_0->indice_classe = num_classe_entier(y_temp,y_magn);
    t_0->classe = y_magn;
    t_0->nb_caractere = profondeur_huffman(p, htables_nb_symb_per_lengths) + t_0->classe;
    encode[0] = t_0;

    return encode;
}


Tuple_encodage_avec_huffman **huffman(Tuple_encodage_sans_huffman **prem_encode, uint16_t *table_huffman_AC, uint8_t htables_symbols_AC[], uint8_t htables_nb_symb_per_lengths[16]){
    Tuple_encodage_avec_huffman **encode_huff = malloc(TAILLE_BLOC_ZZ * sizeof(Tuple_encodage_avec_huffman*));
    if (encode_huff == NULL){
        perror("Échec allocation de encode_huff (Tuple_encodage_avec_huffman)\n");
        return NULL;
    }
    for (int i = 0; i < TAILLE_BLOC_ZZ; i++){
        encode_huff[i] = NULL;
    }

    int i = 1;
    int p = 0;

    while(prem_encode[i]->fin != 1){
        Tuple_encodage_avec_huffman *t = malloc(sizeof(Tuple_encodage_avec_huffman));
        if (t == NULL){
        return NULL;
    }

        p = trouve_indice(prem_encode[i]->nb0_magnitude,htables_symbols_AC,162);
        t->nb0_magnitude_huff =  table_huffman_AC[p];
        t->indice_classe = prem_encode[i]->indice_classe;
        t->classe = prem_encode[i]->classe;
        t->nb_caractere = profondeur_huffman(p, htables_nb_symb_per_lengths) + prem_encode[i]->classe;
        encode_huff[i] = t;


        free(prem_encode[i]);
        i++;
    }

    Tuple_encodage_avec_huffman *t = malloc(sizeof(Tuple_encodage_avec_huffman));
    if (t == NULL){
        return NULL;
    }

    p = trouve_indice(prem_encode[i]->nb0_magnitude,htables_symbols_AC,162);
    t->nb0_magnitude_huff =  table_huffman_AC[p];
    t->indice_classe = prem_encode[i]->indice_classe;
    t->classe = prem_encode[i]->classe;
    t->nb_caractere = profondeur_huffman(p, htables_nb_symb_per_lengths) + prem_encode[i]->classe;
    encode_huff[i] = t;


    free(prem_encode[i]);
    free(prem_encode);
    return encode_huff;
}


Encode_composante **encode_final(Tuple_encodage_avec_huffman **encode){
    Encode_composante **tab = malloc(TAILLE_BLOC_ZZ * sizeof(Encode_composante*));
    if (tab == NULL){
        perror("Échec allocation de tab (Encode_composante)\n");
        return NULL;
    }
    for (int k = 0; k < TAILLE_BLOC_ZZ; k++){
        tab[k] = NULL;
    }


    int i = 0;
    while(encode[i] != NULL){
        uint32_t temp_huff = (uint32_t) encode[i]->nb0_magnitude_huff;
        uint32_t temp_indice = (uint32_t) encode[i]->indice_classe;
        uint32_t test = temp_huff << encode[i]->classe;

        tab[i] = malloc(sizeof(Encode_composante));
        if (tab[i] == NULL){
        return NULL;
        }

        tab[i]->valeur = test + temp_indice;
        tab[i]->nb_caractere = encode[i]->nb_caractere;

        free(encode[i]);
        i++;
    }

    for(int j = i; j < TAILLE_BLOC_ZZ; j++){
        tab[j] = malloc(sizeof(Encode_composante));
        if (tab[j] == NULL){
        return NULL;
        }
        tab[j]->valeur = 0;
        tab[j]->nb_caractere = 0;
    }

    free(encode);
    return tab;
}


Encode_composante **encodage_rle_huffman(Bloc_ZZ *entree, Bloc_ZZ *prec, composante composante){
    Tuple_encodage_sans_huffman** rle_AC;
    rle_AC = codage_rle(entree);
    Tuple_encodage_avec_huffman** huffman_AC;
    Tuple_encodage_avec_huffman** rle_AC_DC;

    if (composante == GRIS_COMPO || composante == Y){
        huffman_AC = huffman(rle_AC,code_huffman_AC_Y,htables_symbols[1][0],htables_nb_symb_per_lengths[1][0]);
        rle_AC_DC = composante_DC(huffman_AC,code_huffman_DC_Y,htables_symbols[0][0],entree,prec,htables_nb_symb_per_lengths[0][0]);
    }
    else {
        huffman_AC = huffman(rle_AC,code_huffman_AC_CbCr,htables_symbols[1][1],htables_nb_symb_per_lengths[1][1]);
        rle_AC_DC = composante_DC(huffman_AC,code_huffman_DC_CbCr,htables_symbols[0][1],entree,prec,htables_nb_symb_per_lengths[0][1]);
    }
    Encode_composante **fin = encode_final(rle_AC_DC);
    // affiche_encodage(fin);
    return fin;
}


void libere_encode_composante(Encode_composante **encode){
    if (encode != NULL){
        for (int i = 0; i < TAILLE_BLOC_ZZ; i++){
            if (encode[i] != NULL){
                free(encode[i]);
            }
        }
        free(encode);
    }
}




void affiche_binaire(uint32_t temp){
    if (temp != 0){
        affiche_binaire(temp/2);
        printf("%d",temp%2);
    }
}


void affiche_encodage(Encode_composante **entree){
        int i = 0;
        while((i < TAILLE_BLOC_ZZ) && (entree[i] != NULL)){
            uint32_t temp = entree[i]->valeur;
            if (entree[i]->nb_caractere != 0) {
                affiche_binaire(temp);
                printf(" = %x",temp);
                printf(", Nombre de caractère : %d \t", entree[i]->nb_caractere);
                printf("\n");
            }
            i++;
        }
    printf("\n");
}


#ifdef EXECUTE_MAIN_RLE

int main(){
    uint16_t p = 0x004d;
    uint8_t i = magnitude(p);
    printf("%d\n",i);
    return 0;
}
#endif
