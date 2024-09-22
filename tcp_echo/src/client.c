#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// Localhost
#define PORT 3000
#define IP "127.0.0.1"

int main(){
  
  char sendline[100];
  char recvline[100];

  int soc = socket(AF_INET, SOCK_STREAM , 0);
  
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = inet_addr(IP);
  
  printf("Socket return values is : %d \n" , soc);

  int connection = connect(soc , (struct sockaddr *) &server_address , sizeof(server_address));
  
  if(connection == 0){

    printf("Connection is Established \n");
  
    fgets(sendline , 100 , stdin);
    ssize_t sent_status = send(soc , sendline , strlen(sendline) , 0);
    ssize_t recv_status = recv(soc , recvline , 100 , 0);


    printf("Sent_Status : %ld \n" , sent_status);
    printf("Recv_Status : %ld \n" , recv_status);

    printf("Recived Info : %s", recvline);

  }else{
    printf("Connection couldn't be established : %d" , connection);
  }

}
