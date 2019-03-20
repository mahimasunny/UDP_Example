#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>  /* for fprintf */
#include <string.h> /* for memcpy */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define PORT 8080

int main(int argc, char const *argv[]) 
{ 

    struct hostent *hp;     /* host information */
    struct sockaddr_in serv_addr;    /* server address */
    char *my_message = "this is a test message";
    // char *host_name = "server";
    int fd = 0;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("cannot create socket");
        return 0;
    }

    /* fill in the server's address and data */
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);


    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    /* send a message to the server */
    if (sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("sendto failed");
        return 0;
    }
}
