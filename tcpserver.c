#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(){
    char message[256] = "Server is Ready/n";
    // Defining the socket descriptor 
    int socketDescriptor = socket(AF_INET,SOCK_STREAM,0);
    
    // Defining the server address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    
   // Binding the server to an IP address and PORT number
    bind(socketDescriptor, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
   // Listening to incoming connections - upto 5 max connections
    listen(socketDescriptor,5);
    printf("Server is Waiting for connections\n");
  // Accepting the incoming connection
    int client_socket = accept(socketDescriptor,NULL,NULL);
    
  // Sending data to client using the 'send(...)' function
    send(client_socket,message,sizeof(message),0);
    close(socketDescriptor);
    return 0;
    
}