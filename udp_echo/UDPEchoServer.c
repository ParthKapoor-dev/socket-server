#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
//UDP Echo Server
#include<string.h>
#include<stdlib.h>

int main()
{
int sockfd,n,clen;
struct sockaddr_in servaddr,cli;
char buff[80];


sockfd=socket(AF_INET,SOCK_DGRAM,0);

bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(43454);

bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)

clen=sizeof(cli);

while(1)
{
bzero(buff,80);
recvfrom(sockfd,buff,sizeof(buff),0,(struct sockaddr *)&cli,&clen);
printf("\nUDP Echo Back: %s ",buff);	
sendto(sockfd,buff,strlen(buff),0,(struct sockaddr *)&cli,clen);

}
close(sockfd);
}




