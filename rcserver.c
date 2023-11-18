#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 9002
#define MAXSIZE 1000

int main(){
    char buffer[MAXSIZE];
    char message[100] = "Command executed Successfully\n";
    int socketDescriptor = socket(AF_INET,SOCK_DGRAM,0);
    
    struct sockaddr_in serverAddress,clientAddress;
    bzero(&serverAddress,sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    socklen_t clientLength;
    clientLength = sizeof(clientAddress);
    
    bind(socketDescriptor,(struct sockaddr*) &serverAddress,sizeof(serverAddress));
    printf("Server has started\n");
    while(1){
       bzero(buffer, sizeof(buffer));
       recvfrom(socketDescriptor, buffer, sizeof(buffer), 0 ,(struct sockaddr*) &clientAddress,&clientLength);
        
        //system call will execute the command present inside the buffer charecter array
        system(buffer);
        printf("Command executed %s\n",buffer);
        sendto(socketDescriptor, message, sizeof(message), 0, (struct sockaddr*) &clientAddress, clientLength);
    }
    
    close(socketDescriptor);
}