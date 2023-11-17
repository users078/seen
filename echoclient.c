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
    char *ip="127.0.0.1";
    int port =1999;
    int sd;
    char buff[1024];
    struct sockaddr_in cliaddr,servaddr;
    
    //  creating a socket

    sd = socket(AF_INET,SOCK_DGRAM,0);
 
   

    memset(&servaddr, '\0', sizeof(servaddr));
    // socket address structure
    servaddr.sin_family  = AF_INET;
    //  memcpy((char*)&servaddr.sin_addr.s_addr,h->h_addr_list[0],h->h_length);
    servaddr.sin_addr.s_addr=inet_addr(ip);
    servaddr.sin_port =1999;
    //conection establishment
    
    socklen_t serverlength;
    serverlength=sizeof(servaddr);
    // cd = connect(sd,(struct sockaddr*)&servaddr ,sizeof(servaddr));
  

   while(1){
        printf("Enter Your Messeage :\n");

        //read the message from std input
        bzero(buff,sizeof(buff));
        fgets(buff,100,stdin);

        // send message
        if(sendto (sd,buff,sizeof (buff),0,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        {
            perror("Cannot send data");
           
        }
        printf("Data sent to UDP Server:%s",buff); 
        bzero(buff,sizeof(buff)); 

        if(recvfrom (sd,buff,sizeof(buff),0,(struct sockaddr*)&servaddr,&serverlength)<0)
        {
            perror("Cannot receive data");

        }
        printf("Received Data from server: %s",buff); 

    }
    close(sd);
    return 0;
}