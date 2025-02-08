#include <ecriture_flux.h>

int nb_bit = 0;
int nb_donnees = 0;

void incremente(Byte* byte, uint8_t un_ou_zero) {
    byte->valeur *= 2;
    byte->valeur += un_ou_zero;
    byte->taille++;
}

void reset(Byte* byte) {
    byte->valeur = 0b0;
    byte->taille = 0;
}

Byte* creer_byte() {
    Byte* byte = (Byte*) malloc(sizeof(Byte));
    if (byte == NULL) {
        perror("Échec d'allocation de byte\n");
        return NULL;
    }
    byte->valeur = 0;
    byte->taille = 0;
    return byte;
}

void reset_current_byte(Byte_courant* current_byte) {
    for (int i = 0; i < 32; i++) {
        current_byte->valeurs[i] = 0;
    }
    current_byte->taille = 0;
}

void affiche_byte(Byte* byte) {
    printf("Valeur : %u et taille : %d \n",byte->valeur,byte->taille);
}

void affiche_current_byte(Byte_courant* current_byte) {
    int index = 0;
    printf("\nByte en cours : ");
    while (index < current_byte->taille) {
        printf("%d ->",current_byte->valeurs[index]);
        index++;
    }
    printf(" END, taille : %d\n",current_byte->taille);
}

void ecris_byte(FILE* fichier, Byte* byte) {
    if (byte->valeur == 0xFF) {
        fputc(0xFF, fichier);
        fputc(0x00, fichier);
    } else {
        fputc(byte->valeur,fichier);
    }
    reset(byte);
}

void ecris_byte_restant(FILE* fichier, Byte* byte) {
    if (byte->taille != 8) {
        byte->valeur = byte->valeur << (8 - byte->taille);
    }
    if (byte->valeur == 0xFF) {
        fputc(0xFF, fichier);
        fputc(0x00, fichier);
    } else {
        fputc(byte->valeur,fichier);
    }
    reset(byte);
}

void ajoute_zero(Byte_courant* current_byte, uint8_t nb_caractere) {
    int difference = nb_caractere - current_byte->taille;
    while (difference > 0) {
        current_byte->valeurs[current_byte->taille] = 0;
        current_byte->taille++;
        difference--;
    }
}

void ecris_dans_byte(FILE* fichier, Byte* byte, Byte_courant* current_byte) {
    int index = current_byte->taille - 1;
    while (index >= 0) {
        incremente(byte, current_byte->valeurs[index]);
        if (byte->taille == 8) {
            ecris_byte(fichier, byte);
        }
        index--;
    }
    reset_current_byte(current_byte);
}

void ecris_bitstream(FILE* fichier, Encode_composante **bytes, Byte* reste) {
    int i = 0;
    Byte_courant* current_byte = (Byte_courant*) malloc(sizeof(Byte_courant));
    if (current_byte == NULL) {
        perror("Échec allocation de current_byte\n");
        return;
    }
    reset_current_byte(current_byte);
    while ((i < 64)) {
        nb_donnees++;
        Encode_composante *current = bytes[i];
        int index = 0;
        while(current->valeur != 0) {
            current_byte->valeurs[index] = current->valeur%2;
            current_byte->taille++;
            index++;
            current->valeur /= 2;
        }
        if (current_byte->taille != current->nb_caractere) {
            ajoute_zero(current_byte, current->nb_caractere);
        }
        ecris_dans_byte(fichier, reste, current_byte);
        i++;
        }
    free(current_byte);
}

#ifdef EXECUTE_MAIN_ECRITURE_FLUX

int main() {
    /* Test invaders */
    // int donnees[] = {0xd8,0xc7,0xc3,0xdf,0xec,0x8f,0xec,0xff,0x00,0xf8,0x43,0x75,0xff,0x00,0xb0,0xff,0x00,0xc8,0x6b,0xfb,0x33,0xc8,0xb7,0xfe,0xd0,0xfb,0x6e,0xdf,0x2b,0x3b,0xbe,0xd9,0xff,0x00,0x1f,0x7f,0x6d,0xfe,0x3f,0x2b,0xc8,0xff,0x00,0x98,0x7e,0xdf,0xb4,0x7e,0xe6,0x80};
    // int taille_donnee = 50;
    FILE* fichier = NULL;
    fichier = fopen("blabla.txt", "w");
    Byte* reste = (Byte*) malloc(sizeof(Byte));
    if (reste == NULL) {
        perror("Échec d'allocation de reste\n");
        return 0;
    }
    reste->valeur = 0b0;
    reste->taille = 0;
    ecris_bitstream(fichier, donnees, reste);
    fputc(reste->valeur,fichier);
    free(reste);
    return 0;
}
#endif