# include<stdio.h>
# include <unistd.h>
# include <string.h>
# include<stdlib.h>
# include<sys/types.h>
# include<sys/socket.h>
# include<netinet/in.h>
# include<netdb.h>
# include<time.h>
# include<sys/stat.h>
# include<sys/ioctl.h>
# include<pcap.h>
# include<net/if_arp.h>//used to manupulate arp request structure and its data member .
# include<arpa/inet.h>// used to convert internet between ascii string and  network byte orderded binary value. 
# include<errno.h>// set error number when error occured .
int main(){
    char *ip ="127.0.0.1";
    int port =1999;
    int bd,sd;
    char buff[1024];
    struct sockaddr_in cliaddr,servaddr;
  



    //socket creating 

    sd = socket(AF_INET,SOCK_DGRAM,0);

    printf("[+]server created");
    memset(&servaddr, '\0', sizeof(servaddr));


    //socket addr structure

    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(ip);
    servaddr.sin_port=port;
    
    
      socklen_t clilen;
    clilen = sizeof(cliaddr);

    // Binding 

    bd = bind(sd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    printf("server is Running .....\n");

    //server to return next completed connection 

    while(1){
        // ad= accept(sd,(struct sockaddr*)&cliaddr,&clilen);
        bzero(&buff,1024);
        if(recvfrom(sd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,&clilen)<0){
            perror("cannot receive data");

        }
        printf(" Messege Received : %s \n",buff);
        //receiving message 
        if(sendto(sd,buff,sizeof(buff),0,(struct sockaddr*)&cliaddr,clilen)<0)
            {
                perror("Cannot send data to client");

            }
        printf("Send data to UDP Client: %s",buff); 
    }
        close(sd);
        return 0;



}