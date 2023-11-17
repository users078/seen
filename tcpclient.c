#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SIZE 1000

int main(){
    // Defining the Socket Descriptor
    int socketDescriptor = socket(AF_INET,SOCK_STREAM,0);
    
    // Defining the Server Information
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9002);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    // Connecting to the server
    connect(socketDescriptor, (struct sockaddr*) &serverAddress, sizeof(serverAddress));
    
    // Recieving the message
    char serverResponse[SIZE];
    recv(socketDescriptor, &serverResponse, sizeof(serverResponse),0);

    printf("The server response is : %s",serverResponse);
    close(socketDescriptor);
    return 0;
}