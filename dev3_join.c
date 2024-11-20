#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void join(const char *fic_Final, int nbP,char *tab[]) {
    FILE *fp = fopen(fic_Final, "wb");
    if (fp == NULL) {
        perror("Erreur création fichier final");
        exit(1);
    }

    char buf[1024];
    size_t lus;
    for (int i = 0; i < nbP; i++) {
        FILE *part = fopen(tab[i], "rb");
        if (part == NULL) {
            perror("Erreur ouverture ");
            fclose(fp);
            exit(-1);
        }
        while ((lus = fread(buf,1, sizeof(buf), part)) > 0) {
            fwrite(buf,1,lus, fp);
        }
        fclose(part);
    }

    fclose(fp);
    printf("Fichiers fusionnés dans : %s\n",fic_Final);
}
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage : %s fichier_final partie1 partie2 ... partieN\n", argv[0]);
        return 0;
    }

    const char *fic_Final =argv[1];
    char **parties = &argv[2];
    int nbP = argc - 2;

    join(fic_Final, nbP, parties);
    return 0;
}
