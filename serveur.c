#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "common.h"
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Erreur: nombre d'arguments insuffisant.\n");
        printf("Usage: %s et port\n", argv[0]);
        return -1;
    }

    int socketServeur, socketClient;
    struct sockaddr_in addrServeur = {0}, addrClient = {0};
    socklen_t taille = sizeof(addrClient);

    socketServeur = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServeur == -1) {
        perror("Erreur de création de la socket serveur");
        exit(-1);
    }

    addrServeur.sin_family = AF_INET;
    addrServeur.sin_port = htons(atoi(argv[1]));
    addrServeur.sin_addr.s_addr = INADDR_ANY;

    int resultat=bind(socketServeur,(struct sockaddr *)&addrServeur,sizeof(addrServeur));
    if (resultat==-1) {
        perror("Erruer de Bind----------------\n");
        return 0;
    }
    // Listen 
    resultat=listen(socketServeur,5);
    if (resultat==-1) {
        perror("Erreur de Listen----------------");
        return 0;
    }
    printf("Listen-----------------ok sur le port %d \n",atoi(argv[1]));
   
    // Accept
    socketClient=accept(socketServeur,(struct sockaddr *)&addrClient, &taille);
    if (socketClient==-1) {
        perror("Erreur de Accept-----------------------");
        return 0;
    }
    printf("Client connecté.\n");

    struct Message msg = { .compteur = 0 };
    while (1) {
        if (send(socketClient, &msg, sizeof(msg), 0) == -1) {
            perror("Erreur de send-----------------------NOK");
            break;
        }

        if (recv(socketClient, &msg, sizeof(msg), 0) <= 0) {
            perror("Erreur de recv-----------------------NOK");
            break;
        }
        printf("Compteur reçu du client: %d\n", msg.compteur);

        msg.compteur++;
        printf("Compteur incrémenté à: %d\n", msg.compteur);
        sleep(1);
    }

    close(socketClient);
    close(socketServeur);
    return 0;
}
