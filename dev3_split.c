#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void decouperFichier(char *fic, int taillePart) {
    FILE *fp = fopen(fic, "rb");
    if (fp == NULL) {
        perror("Erreur ouverture fichier principal \n");
        exit(1);
    }
    char nomPart[256];
    int numPart = 1;
    size_t t;
    char *buf= malloc(taillePart);
    if (buf == NULL) {
        perror("Erreur mémoire detecter !!!!\n");
        fclose(fp);
        exit(1);
    }

    while ((t=fread(buf,1,taillePart, fp)) > 0) {
        snprintf(nomPart,sizeof(nomPart),"%s.part%d",fic,numPart++);
        FILE *part = fopen(nomPart, "wb");
        if (part == NULL) {
            perror("Erreur création d'une partie\n");
            free(buf);
            fclose(fp);
            exit(1);
        }

        fwrite(buf,1,t, part);
        fclose(part);
    }

    free(buf);
    fclose(fp);
    printf("Fichier %s découpé en %d parties de %d octets\n",fic,numPart - 1, taillePart);
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage : %s fichier taille\n", argv[0]);
        return 0;
    }

    const char *nomFichier= argv[1];
    int taillePart = atoi(argv[2]);
    if (taillePart <= 0) {
        printf("La taille doit être un entier positif\n");
        return 0;
    }
    decouperFichier(nomFichier,taillePart);

    return 0;
}
