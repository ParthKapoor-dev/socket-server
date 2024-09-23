#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 5000
#define MAXLINE 1024

int main() {

    fd_set soc_set;

    char *ip;
    int client_port;

    char buffer[MAXLINE];
    char str[MAXLINE];

    int tcp_soc = socket(AF_INET, SOCK_STREAM, 0);
    int udp_soc = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_address, client_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(tcp_soc, (struct sockaddr*) &server_address, sizeof(server_address));
    listen(tcp_soc, 10);

    bind(udp_soc, (struct sockaddr*) &server_address, sizeof(server_address));

    FD_ZERO(&soc_set);

    int MAX_FD = (tcp_soc > udp_soc ? tcp_soc : udp_soc) + 1;

    while (1) {

        FD_SET(tcp_soc, &soc_set);
        FD_SET(udp_soc, &soc_set);

        int ready_sockets = select(MAX_FD , &soc_set, NULL, NULL, NULL);

        if (FD_ISSET(tcp_soc, &soc_set)) {

            printf("Connected to a TCP Client Successfully \n");

            socklen_t client_len = sizeof(client_address);  // Fix
            int client_soc = accept(tcp_soc, (struct sockaddr*) &client_address, &client_len);  // Fix
            
            ip = inet_ntoa(client_address.sin_addr); 
            client_port = ntohs(client_address.sin_port);
            
            printf("Client IP Address : %s:%i \n" , ip , client_port);

            if (fork() == 0) {

                close(tcp_soc);

                while (1) {

                    bzero(buffer , sizeof(buffer));
                    bzero(str , sizeof(str));

                    recv(client_soc, &str, MAXLINE, 0);

                    printf("TCP CLIENT : %s \n Write your Message now : ", str);

                    fgets(buffer, MAXLINE, stdin);

                    send(client_soc, &buffer, sizeof(buffer), 0);

                    printf("Information Sent Successfully \n");
                }

                close(client_soc);
                exit(0);
            }
        }

        if (FD_ISSET(udp_soc, &soc_set)) {

            socklen_t client_len = sizeof(client_address);  // Fix
            bzero(buffer, sizeof(buffer));

            recvfrom(udp_soc, buffer, sizeof(buffer), 0, (struct sockaddr*) &client_address, &client_len);  // Fix

            printf("TCP CLIENT : %s \n Write your Message now : ", str);

            fgets(buffer, 100, stdin);

            sendto(udp_soc, buffer, sizeof(buffer), 0, (struct sockaddr*) &client_address, client_len);
        }
    }
}
