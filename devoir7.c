#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char const *argv[]) {
    if (argc < 2) {
        printf("Erreur : veuillez fournir une adresse IP à scanner.\n");
        printf("Usage : %s IP\n", argv[0]);
        return 0;
    }
    
    struct sockaddr_in addrServer;
    int port;
    
    printf("Scan des ports TCP ouverts entre 0 et 3000 sur %s...\n", argv[1]);

    for (port = 0; port <= 3000; port++) {
        int socketClientTCP = socket(AF_INET, SOCK_STREAM, 0);
        if (socketClientTCP == -1) {
            perror("Erreur lors de la création de la socket TCP");
            return 0;
        }
        memset(&addrServer, 0, sizeof(struct sockaddr_in));
        addrServer.sin_family = AF_INET;
        addrServer.sin_port = htons(port);
        addrServer.sin_addr.s_addr = inet_addr(argv[1]);
        //connexion au port
        int resultat = connect(socketClientTCP, (struct sockaddr *)&addrServer, sizeof(struct sockaddr_in));
        if (resultat == 0) {
            printf("Le port %d est ouvert.\n", port);
        }
        close(socketClientTCP);
    }
    printf("Scan terminé.\n");
    return 0;
}
