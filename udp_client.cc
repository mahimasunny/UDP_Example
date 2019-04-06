#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>  /* for fprintf */
#include <string> /* for memcpy */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <cstring>


#define PORT 8080

using namespace std;

class UDP_Client {
        public:
        UDP_Client() {
            if ((socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                throw "cannot create socket";
            }
            //fill in the server's address and data
            memset((char *)&serverAddress, 0, sizeof(serverAddress));
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
            serverAddress.sin_port = htons(PORT);
            // Convert IPv4 and IPv6 addresses from text to binary form 
            if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr)<=0) { 
                throw "Invalid address/ Address not supported";
            }   
        }

        void sendMessage(string message) {
            if ( sendto(socketFileDescriptor, message.c_str(),
                message.size(), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
                throw "sendto failed";
            }
        }
        private:
            int socketFileDescriptor;
            struct sockaddr_in serverAddress;

};

int main(int argc, char const *argv[])  {
        string message = "{\"key\":\"value-alan\"}";
        UDP_Client c;
        c.sendMessage(message);
}
