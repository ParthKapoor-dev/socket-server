#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#define PORT 3000

int main(){
  
  char str[100];
  
  int soc = socket( AF_INET , SOCK_STREAM, 0);
  
  struct sockaddr_in server_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  bind( soc , ( struct sockaddr *) &server_address , sizeof(server_address));
  
  int listening_status =  listen( soc , 10);

  if(listening_status == 0){
    printf("Server is Listening at Port %d \n" , PORT);

    while(1){
      int client_soc = accept( soc , (struct sockaddr*) NULL , NULL );
      bzero(str , 100);
      recv( client_soc , str , 100 , 0 );
      printf("Received Info : %s \n" , str);

      send( client_soc , str , strlen(str) , 0);
      close(client_soc);
    }

  }else {
    printf("Binding Failed!");
  }
  
}
