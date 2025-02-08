#include <dct.h>

uint16_t arrondi(float valeur) {
    uint16_t arr1 = (uint16_t) valeur;
    if (valeur > 0) {
        if ((valeur > (arr1 + 0.999)) && (valeur < (arr1 + 1))) {
            arr1++;
        }
        return arr1;
    } else {
        if ((valeur < (arr1 - 0.999)) && (valeur > (arr1 - 1))) {
            arr1--;
        }
        return arr1;
    }
}

float **creer_tab_cos(){
    float **tab_cos = (float **)malloc(TAILLE_BLOC * sizeof(float*));
    if (tab_cos == NULL){
        perror("Echec: Allocation (malloc) pour tab_cos (Pixel**).\n");
        return NULL;
    }

    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        tab_cos[i] = (float* )malloc(TAILLE_BLOC * sizeof(float));
        if (tab_cos[i] == NULL){
            perror("Echec: Allocation (malloc) pour tab_cos[i] (Pixel*).\n");
            for (unsigned int j = 0; j < i; j++){
                free(tab_cos[j]);
            }
            free(tab_cos);
            perror("Attention DCT n'as pas pu être fait!\n");
            return NULL;
        }
    }

    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            tab_cos[i][j] = cos(((2 * i + 1) * PI * j) / (2.0 * TAILLE_BLOC));
        }
    }
    return tab_cos;
}


Bloc* dct(Bloc* bloc){

    if (bloc == NULL){
        return NULL;;
    }

    Bloc* freq = creer_bloc_freq();
    if (freq == NULL){
        return NULL;
    }
    Bloc_float* freq_float = creer_bloc_freq_float();
    if (freq_float == NULL){
        return NULL;
    }

    float** tab_couleur = (float **)malloc(TAILLE_BLOC * sizeof(float*));
        if (tab_couleur == NULL){
        perror("Echec: Allocation (malloc) pour tab_couleur (Pixel**).\n");
        return NULL;
    }
    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        tab_couleur[i] = (float* )malloc(TAILLE_BLOC * sizeof(float));
        if (tab_couleur[i] == NULL){
            perror("Echec: Allocation (malloc) pour tab_cos[i] (Pixel*).\n");
            for (unsigned int j = 0; j < i; j++){
                free(tab_couleur[j]);
            }
            free(tab_couleur);
            perror("Attention DCT n'as pas pu être fait!\n");
            return NULL;
        }
    }

    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            tab_couleur[i][j] = bloc->matrice_pixels[i][j].peu_importe - 128.0;
        }
    }

    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                    freq_float->matrice_pixels_float[i][j].peu_importe += \
                    tab_couleur[x][y] * cosf(((2 * x + 1) * PI * i) / (2.0 * TAILLE_BLOC)) \
                    * cosf(((2 * y + 1) * PI * j) / (2.0 * TAILLE_BLOC));
                }
            }
            if ((i == 0) && (j == 0)){
                 freq_float->matrice_pixels_float[i][j].peu_importe /= TAILLE_BLOC;
            }
            else if ((i == 0) || (j == 0)){
                freq_float->matrice_pixels_float[i][j].peu_importe *= (sqrt(2) / TAILLE_BLOC);
                    
            }
            else{
                freq_float->matrice_pixels_float[i][j].peu_importe *= (2.0 / TAILLE_BLOC);
            }
        }
    }
    for (int i = 0; i < TAILLE_BLOC; i++){
        for (int j = 0; j < TAILLE_BLOC; j++){
            printf(" Valeur : %f devient ",freq_float->matrice_pixels_float[i][j].peu_importe);
            freq->matrice_pixels[i][j].peu_importe = arrondi(freq_float->matrice_pixels_float[i][j].peu_importe);
            printf("%d \n",freq->matrice_pixels[i][j].peu_importe);
        }
    }
    libere_tab_2D(tab_couleur, TAILLE_BLOC);
    libere_bloc_float(freq_float);
    return freq;
}


Bloc* dct_opt_1(Bloc* bloc, float **tab_cos){

    if (bloc == NULL){
        return NULL;;
    }

    Bloc* freq = creer_bloc_freq();
    if (freq == NULL){
        return NULL;
    }
    Bloc_float* freq_float = creer_bloc_freq_float();
    if (freq_float == NULL){
        return NULL;
    }

    float** tab_couleur = (float **)malloc(TAILLE_BLOC * TAILLE_BLOC * sizeof(float*));
        if (tab_couleur == NULL){
        perror("Echec: Allocation (malloc) pour tab_couleur (Pixel**).\n");
        return NULL;
    }
    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        tab_couleur[i] = (float* )malloc(TAILLE_BLOC * sizeof(float));
        if (tab_couleur[i] == NULL){
            perror("Echec: Allocation (malloc) pour tab_cos[i] (Pixel*).\n");
            for (unsigned int j = 0; j < i; j++){
                free(tab_couleur[j]);
            }
            free(tab_couleur);
            perror("Attention DCT n'as pas pu être fait!\n");
            return NULL;
        }
    }

    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            tab_couleur[i][j] = bloc->matrice_pixels[i][j].peu_importe - 128.0;
        }
    }


    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            for (unsigned int x = 0; x < TAILLE_BLOC; x++){
                for (unsigned int y = 0; y < TAILLE_BLOC; y++){
                    freq_float->matrice_pixels_float[i][j].peu_importe += \
                    tab_couleur[x][y] * tab_cos[x][i] * tab_cos[y][j];
                }
            }
            if ((i == 0) && (j == 0)){
                 freq_float->matrice_pixels_float[i][j].peu_importe /= TAILLE_BLOC;
            }
            else if ((i == 0) || (j == 0)){
                freq_float->matrice_pixels_float[i][j].peu_importe *= (sqrt(2) / TAILLE_BLOC);
                    
            }
            else{
                freq_float->matrice_pixels_float[i][j].peu_importe *= (2.0 / TAILLE_BLOC);
            }
        }
    }
    for (int i = 0; i < TAILLE_BLOC; i++){
        for (int j = 0; j < TAILLE_BLOC; j++){
            freq->matrice_pixels[i][j].peu_importe = arrondi(freq_float->matrice_pixels_float[i][j].peu_importe);
        }
    }
    libere_tab_2D(tab_couleur, TAILLE_BLOC);
    libere_bloc_float(freq_float);
    return freq;
}


/*
Sources UNIQUEMENT POUR **ForwardDCTComponent** : Forward DCT inspired by // https://unix4lyfe.org/dct-1d/ et 
https://codereview.stackexchange.com/questions/265527/faster-aan-algorithm-for-calculating-discrete-cosine-transform
*/

//Compute forward dct
void ForwardDCTComponent(float *component){
    /*Forward DCT constants*/
    const float a1 = 0.707;
    const float a2 = 0.541;
    const float a3 = 0.707;
    const float a4 = 1.307;
    const float a5 = 0.383;

    const float s0 = 0.353553;
    const float s1 = 0.254898;
    const float s2 = 0.270598;
    const float s3 = 0.300672;
    const float s4 = s0;
    const float s5 = 0.449988;
    const float s6 = 0.653281;
    const float s7 = 1.281458;
    /*Forward DCT constants*/


    for(int i = 0; i < 8; i++)
    {
        const float b0 = component[0*8 + i] + component[7*8 + i];
        const float b1 = component[1*8 + i] + component[6*8 + i];
        const float b2 = component[2*8 + i] + component[5*8 + i];
        const float b3 = component[3*8 + i] + component[4*8 + i];
        const float b4 =-component[4*8 + i] + component[3*8 + i];
        const float b5 =-component[5*8 + i] + component[2*8 + i];
        const float b6 =-component[6*8 + i] + component[1*8 + i];
        const float b7 =-component[7*8 + i] + component[0*8 + i];
        
        const float c0 = b0 + b3;
        const float c1 = b1 + b2;
        const float c2 =-b2 + b1;
        const float c3 =-b3 + b0;
        const float c4 =-b4 - b5;
        const float c5 = b5 + b6;
        const float c6 = b6 + b7;
        const float c7 = b7;
        
        const float d0 = c0 + c1;
        const float d1 =-c1 + c0;
        const float d2 = c2 + c3;
        const float d3 = c3;
        const float d4 = c4;
        const float d5 = c5;
        const float d6 = c6;
        const float d7 = c7;
        const float d8 = (d4+d6) * a5;
        
        const float e0 = d0;
        const float e1 = d1;
        const float e2 = d2 * a1;
        const float e3 = d3;
        const float e4 = -d4 * a2 - d8;
        const float e5 = d5 * a3;
        const float e6 = d6 * a4 - d8;
        const float e7 = d7;
        
        const float f0 = e0;
        const float f1 = e1;
        const float f2 = e2 + e3;
        const float f3 = e3 - e2;
        const float f4 = e4;
        const float f5 = e5 + e7;
        const float f6 = e6;
        const float f7 = e7 - e5;
        
        const float g0 = f0;
        const float g1 = f1;
        const float g2 = f2;
        const float g3 = f3;
        const float g4 = f4 + f7;
        const float g5 = f5 + f6;
        const float g6 = -f6 + f5;
        const float g7 = f7 - f4;   
        
        component[0*8 + i] = g0 * s0;
        component[4*8 + i] = g1 * s4;
        component[2*8 + i] = g2 * s2;
        component[6*8 + i] = g3 * s6;
        component[5*8 + i] = g4 * s5;
        component[1*8 + i] = g5 * s1;
        component[7*8 + i] = g6 * s7;
        component[3*8 + i] = g7 * s3;       
    }
    for(int i = 0; i < 8; i++){
        const float b0 = component[i*8 + 0]  + component[i*8 + 7];
        const float b1 = component[i*8 + 1]  + component[i*8 + 6];
        const float b2 = component[i*8 + 2]  + component[i*8 + 5];
        const float b3 = component[i*8 + 3]  + component[i*8 + 4];
        const float b4 =-component[i*8 + 4]  + component[i*8 + 3];
        const float b5 =-component[i*8 + 5]  + component[i*8 + 2];
        const float b6 =-component[i*8 + 6]  + component[i*8 + 1];
        const float b7 =-component[i*8 + 7]  + component[i*8 + 0] ;
        
        const float c0 = b0 + b3;
        const float c1 = b1 + b2;
        const float c2 =-b2 + b1;
        const float c3 =-b3 + b0;
        const float c4 =-b4 - b5;
        const float c5 = b5 + b6;
        const float c6 = b6 + b7;
        const float c7 = b7;
        
        const float d0 = c0 + c1;
        const float d1 =-c1 + c0;
        const float d2 = c2 + c3;
        const float d3 = c3;
        const float d4 = c4;
        const float d5 = c5;
        const float d6 = c6;
        const float d7 = c7;
        const float d8 = (d4+d6) * a5;
        
        const float e0 = d0;
        const float e1 = d1;
        const float e2 = d2 * a1;
        const float e3 = d3;
        const float e4 = -d4 * a2 - d8;
        const float e5 = d5 * a3;
        const float e6 = d6 * a4 - d8;
        const float e7 = d7;
        
        const float f0 = e0;
        const float f1 = e1;
        const float f2 = e2 + e3;
        const float f3 = e3 - e2;
        const float f4 = e4;
        const float f5 = e5 + e7;
        const float f6 = e6;
        const float f7 = e7 - e5;
        
        const float g0 = f0;
        const float g1 = f1;
        const float g2 = f2;
        const float g3 = f3;
        const float g4 = f4 + f7;
        const float g5 = f5 + f6;
        const float g6 = -f6 + f5;
        const float g7 = f7 - f4;   
        
        component[i*8 + 0] = g0 * s0;
        component[i*8 + 4] = g1 * s4;
        component[i*8 + 2] = g2 * s2;
        component[i*8 + 6] = g3 * s6;
        component[i*8 + 5] = g4 * s5;
        component[i*8 + 1] = g5 * s1;
        component[i*8 + 7] = g6 * s7;
        component[i*8 + 3] = g7 * s3;   
    }
}


Bloc* dct_opt_2(Bloc* bloc){

    if (bloc == NULL){
        return NULL;;
    }

    Bloc* freq = creer_bloc_freq();
    if (freq == NULL){
        return NULL;
    }

    float freq_float[TAILLE_BLOC][TAILLE_BLOC] = {
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                        {.0, .0, .0, .0, .0, .0, .0, .0},
                                                    };

    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            freq_float[i][j] = (float) (bloc->matrice_pixels[i][j].peu_importe - 128.0);
        }
    }
    ForwardDCTComponent(*freq_float);

    for (int i = 0; i < TAILLE_BLOC; i++){
        for (int j = 0; j < TAILLE_BLOC; j++){
            freq->matrice_pixels[i][j].peu_importe = arrondi(freq_float[i][j]);
        }
    }
    return freq;
}


Bloc* creer_bloc_freq(){
    
    Bloc* bloc_freq = (Bloc* )malloc(sizeof(Bloc));
    if (bloc_freq == NULL){
        perror("Echec: Allocation (malloc) pour bloc_freq (Bloc*).\n");
        return NULL;
    }
    
    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            bloc_freq->matrice_pixels[i][j].peu_importe = 0;
        }
    }
       
    return bloc_freq;
}


Bloc_float* creer_bloc_freq_float(){
    
    Bloc_float* bloc_freq = (Bloc_float* )malloc(sizeof(Bloc_float));
    if (bloc_freq == NULL){
        perror("Echec: Allocation (malloc) pour bloc_freq (Bloc_float*).\n");
        return NULL;
    }
    
    for (unsigned int i = 0; i < TAILLE_BLOC; i++){
        for (unsigned int j = 0; j < TAILLE_BLOC; j++){
            bloc_freq->matrice_pixels_float[i][j].peu_importe = 0;
        }
    }
       
    return bloc_freq;
}


void libere_tab_2D(float** tab, unsigned int nb_ligne){
    if (tab != NULL){
        for (unsigned int i = 0; i < nb_ligne; i++){
            free(tab[i]);
        }
        free(tab);
    }
}

void libere_bloc_float(Bloc_float *freq_float){
    if (freq_float != NULL){
        free(freq_float);
    }
}

void libere_bloc(Bloc *freq){
    if (freq != NULL){
        free(freq);
    }
}


#ifdef EXECUTE_MAIN_DCT
int main(){
    printf("A tester plus tard!\n");
    printf("PI: %f.\n", PI);
    return 0;
}
#endif