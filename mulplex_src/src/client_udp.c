
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5000
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Create a UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address setup
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Communication loop
    while (1) {
        fgets(buffer, MAXLINE, stdin);  // Read message from user
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

        // Get response from server
        memset(buffer, 0, MAXLINE);
        recvfrom(sockfd, buffer, MAXLINE, 0, NULL, NULL);
        printf("Message from server: %s\n", buffer);
    }

    // Close the socket
    close(sockfd);
}
