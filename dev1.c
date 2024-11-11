#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int funcF(int a) {
    int p = 1, i = 1;
    while (i <= a) {
        p = 2 * p;
        i++;
    }
    return p;
}
int funcG(int a) { return 2 * a;}
int main(int argc, char *argv[]) {
    int opt;
    int entier = -1;
    int f_est_appele = 0;
	int g_est_appele = 0;
    if (argc == 3) {  //Ici seulement l'une des options avec comme argument l'entier est fournie
        opt = getopt(argc, argv, "f:g:");
        switch (opt) {
            case 'f':
                entier = atoi(optarg);
				printf("L'option -%c est fournie avec comme argument: %s\n", opt, optarg);
                printf("La fonction f est exécutée : 2^%d = %d\n", entier, funcF(entier));
                break;
            case 'g':
                entier = atoi(optarg);
				printf("L'option -%c est fournie avec comme argument: %s\n", opt, optarg);
                printf("La fonction g est exécutée : 2 * %d = %d\n", entier, funcG(entier));
                break;
            case '?':
                printf("Erreur : option inconnue -%c\n", optopt);
                return 1;
        }
    } else if (argc == 4) {  // si  ./prog -f n -g ou ./prog -g n -f
        opt = getopt(argc, argv, "f:g:");
        switch (opt) {
            case 'f':
                f_est_appele = 1;
                entier = atoi(optarg);
                if (strcmp(argv[3], "-g") == 0) {
                    printf("La fonction fog(%d) = %d\n", entier, funcF(funcG(entier)));
                } else {
                    printf("Erreur, donner : ./prog -f n -g\n");
                    return 1;
                }
                break;
            case 'g':
                g_est_appele = 1;
                entier = atoi(optarg);
                if (strcmp(argv[3], "-f") == 0) {
                    printf("La fonction gof(%d) = %d\n", entier, funcG(funcF(entier)));
                } else {
                    printf("Erreur, Utiliser : ./prog -g n -f\n");
                    return 1;
                }
                break;
            case '?':
                printf("Erreur : option inconnue -%c\n", optopt);
                return 1;
        }
    } else {
        printf("Erreur : veuillez fournir les bonnes options !!\n");
        return 1;
    }

    return 0;
}
