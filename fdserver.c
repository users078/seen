#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//headers for socket and related functions
#include <sys/types.h>
#include <sys/socket.h>
//for including structures which will store information needed
#include <netinet/in.h>
#include <unistd.h>
//for gethostbyname
#include "netdb.h"
#include "arpa/inet.h"
#define MAXSIZE 1000
#define BACKLOG 5 // how many pending connections queue will hold
int main()
{
 char serverMessage[MAXSIZE];
 char clientMessage[MAXSIZE];
 //create the server socket
 int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
 
 struct sockaddr_in serverAddress;
 serverAddress.sin_family = AF_INET;
 serverAddress.sin_port = htons(9002);
 serverAddress.sin_addr.s_addr = INADDR_ANY;
 //calling bind function to oir specified IP and port
 bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); 
 listen(socketDescriptor, BACKLOG);
 
 //starting the accepting
 int client_socket = accept(socketDescriptor, NULL, NULL);
 while (1)
 {
 printf("\ntext message here .. :");
 scanf("%s", serverMessage);
 send(client_socket, serverMessage, sizeof(serverMessage) , 0);
 //recieve the data from the server
 recv(client_socket, &clientMessage, sizeof(clientMessage), 0) ;
 //recieved data from the server successfully then printing the data obtained from the server
 printf("\nCLIENT: %s", clientMessage);
 
 }
 //close the socket
 close(socketDescriptor);
 return 0;
}