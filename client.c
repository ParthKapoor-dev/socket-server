#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 80
#define IP "142.250.194.238"

int main(){

  int soc = socket(AF_INET, SOCK_STREAM , 0);
  
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = inet_addr(IP);
  
  printf("Socket return values is : %d \n" , soc);

  int connection = connect(soc , (struct sockaddr *) &server_address , sizeof(server_address));
  
  printf("Connection return values is : %d \n" , connection);

  if(connection == 0){
    printf("Connection is Established");
  }else{
    printf("Connection couldn't be established");
  }

}
