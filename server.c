#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

#define PORT 3000

int main(){

  int soc = socket( AF_INET , SOCK_STREAM, 0);
  
  struct sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  int bind_status = bind( soc , ( struct sockaddr *) &server_address , sizeof(server_address));

  if(bind_status == 0){
    printf("Binding is successful");

  }else {
    printf("Binding Failed!");
  }
  
}
