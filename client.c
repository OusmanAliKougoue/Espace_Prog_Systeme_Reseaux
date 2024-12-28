#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"

int main(int argc, char* argv[]) {
    if(argc<3){
        printf("Erruer nombre arguments petit");
        printf("Usage:%s \n",argv[0]);
        return -1;
    }

    int socketClient = socket(AF_INET, SOCK_STREAM, 0);
    if (socketClient == -1) {
        perror("Erreur lors de la création de la socket TCP");
        return 0;
    }

    struct sockaddr_in addrServeur = {0};
    addrServeur.sin_family = AF_INET;
    addrServeur.sin_port = htons(atoi(argv[2]));
    addrServeur.sin_addr.s_addr = inet_addr(argv[1]);

    int resultat = connect(socketClient, (struct sockaddr *)&addrServeur, sizeof(addrServeur));
    if ( resultat==-1) {
        perror("Erreur de connect------------NOK");
        return 0;
    }
    printf("Connect-------------------OK.\n");

    struct Message msg;
    while (1) {
        if (recv(socketClient, &msg, sizeof(msg), 0) <= 0) {
            perror("Erreur de réception");
            break;
        }
        printf("Compteur reçu du serveur: %d\n", msg.compteur);
        
        msg.compteur++;
        printf("Compteur incrémenté à: %d\n", msg.compteur);

        if (send(socketClient, &msg, sizeof(msg), 0) == -1) {
            perror("Erreur d'envoi");
            break;
        }
        sleep(1);
    }

    close(socketClient);
    return 0;
}
