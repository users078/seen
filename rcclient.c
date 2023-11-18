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

#define MAXSIZE 100
#define PORT 9002

int main(){
    char buffer[MAXSIZE],message[MAXSIZE];
    int socketDescriptor = socket(AF_INET,SOCK_DGRAM,0);
    
    struct sockaddr_in serverAddress, clientAddress;
    bzero(&serverAddress,sizeof(serverAddress));
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    
    socklen_t serverLength;
    serverLength = sizeof(serverAddress);
    
    bind(socketDescriptor,(struct sockaddr*) &serverAddress, sizeof(serverAddress));
    while(1){
        printf("Type your command for execution \n");
        fgets(buffer,sizeof(buffer),stdin);
        sendto(socketDescriptor,buffer,sizeof(buffer),0,(struct sockaddr*) &serverAddress,serverLength);
        printf("Command send to be executed successfully \n");
        recvfrom(socketDescriptor,&message,sizeof(message),0,(struct sockaddr*) &serverAddress,&serverLength);
        printf("Message received : %s",message);
}
    
    return 0;
}