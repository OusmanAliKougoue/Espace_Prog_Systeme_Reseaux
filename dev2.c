#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
typedef struct {
    int taille;
    int **mat;
} matrice;
void detruire_Matrice(matrice *m) {
    for (int i = 0; i < m->taille; i++) {
        free(m->mat[i]);
    }
    free(m->mat);
    free(m);
}
void creer_Matrice(matrice *m) {
    for (int i = 0; i < m->taille; i++) {
        for (int j = 0; j < m->taille; j++) {
            m->mat[i][j] = rand() % 100 + 1; 
        }
    }
}

void ecrire_Matrice_Binaire(const char *fic, matrice *m) {
    int fd = open(fic, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Erreur d'ouverture du fichier binaire");
        exit(-1);
    }

    for (int i = 0; i < m->taille; i++) {
        if (write(fd, m->mat[i], m->taille * sizeof(int)) == -1) {
            perror("Erreur d'écriture dans le fichier binaire");
            close(fd);
            exit(1);
        }
    }

    close(fd);
    printf("Matrice écrite dans le fichier binaire : %s\n",fic);
}
void ecrire_Matrice_Texte(const char *fic, matrice *m) {
    FILE *file = fopen(fic, "w");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier texte");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m->taille; i++) {
        for (int j = 0; j < m->taille; j++) {
            fprintf(file, "%d ", m->mat[i][j]);
        }
        fprintf(file, "\n"); 
    }

    fclose(file);
    printf("Matrice écrite  dans le fichier texte : %s\n", fic);
}
void afficher_Texte(const char *fic) {
    FILE *file = fopen(fic, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier texte");
        exit(-1);
    }

    int valeur;
    printf("Matrice format texte :\n");
    while (fscanf(file, "%d", &valeur) == 1) {
        printf("%d ", valeur);
        if (fgetc(file) == '\n') {
            printf("\n");
        }
    }

    fclose(file);
}
void affichage_Matrice(const char *fic, int taille) {
    int fd = open(fic, O_RDONLY);
    if (fd == -1) {
        perror("Erreur d'ouverture du fichier binaire");
        exit(2);
    }

    int temp[taille];
    printf("---------Matrice---------\n");
    for (int i = 0; i < taille; i++) {
        if (read(fd, temp, taille * sizeof(int)) == -1) {
            perror("Erreur de lecture du fichier binaire");
            close(fd);
            exit(3);
        }

        for (int j = 0; j < taille; j++) {
            printf("%d ", temp[j]);
        }
        printf("\n");
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    int opt, taille = 0;
    int creation = 0, affichage = 0, modeTexte = 0;
    if(argc <6){
	      printf("Erreur : Nombre d'arguments petit\n");
	      printf("Usage : %s nomfichier :%s ",argv[0]);
	      return 0;
    }
    while ((opt = getopt(argc, argv, "cad:f:t")) != -1) {
        switch (opt) {
            case 'c':
                creation = 1;
                break;
            case 'a':
                affichage = 1;
                break;
            case 'd':
                taille = atoi(optarg);
                if (taille <= 0) {
                    printf("donner un entier positif.\n");
                    return 0;
                }
                break;
            case 'f':
                argv[5] = optarg;
                break;
            case 't':
                modeTexte = 1;
                break;
            default:
                printf("les arguments ne sont pas valides\n");
                return 0;
        }
    }

    if (argv[5]==NULL || taille == 0 || (!creation && !affichage)) {
        printf("veillez donner les options dans le bon ordre s'il vous plait !!!\n");
        printf("Usage : %s -c|-a -d n -f nomfichier \n", argv[0]);
        return 0;
    }
    matrice *m = NULL;
     if (creation) {
        m = (matrice *)malloc(sizeof(matrice));
        m->taille = taille;
        m->mat = (int **)malloc(taille * sizeof(int *));
        for (int i = 0; i < taille; i++) {
            m->mat[i] = (int *)malloc(taille * sizeof(int));
        }

        creer_Matrice(m);
        if (modeTexte) {
             ecrire_Matrice_Texte(argv[5],m);
        }else {
            ecrire_Matrice_Binaire(argv[5],m);
        }
        detruire_Matrice(m);
    }
    if (affichage) {
        if (!modeTexte) {
            affichage_Matrice(argv[5], taille);
        } else {
           afficher_Texte(argv[5]);
        }
    }

    return 0;
}
