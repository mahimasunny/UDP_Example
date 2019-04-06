#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>  /* for fprintf */
#include <string.h> /* for memcpy */
#include <netinet/in.h>
#include <stdexcept>
#include <stdlib.h> 


// #include <sys/socket.h>
// #include <netinet/in.h> 
// #include "elma.h"
// #include "json/json.h"
// #include "udp_server.h"

// #include <stdexcept>

#define PORT 8080
#define BUFFER_SIZE 2048

using namespace std;

class UDP_Server {

        public:
        UDP_Server() {
                /* create a UDP socket */
                struct sockaddr_in _addr;      /* our address */

                if ((_server_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
                        throw "cannot create socket";
                }

                /* bind the socket to any valid IP address and a specific port */
                memset((char *)&_addr, 0, sizeof(_addr));
                _addr.sin_family = AF_INET;
                _addr.sin_addr.s_addr = htonl(INADDR_ANY);
                _addr.sin_port = htons(PORT);

                // if (bind(_server_file_descriptor, (struct sockaddr *)&_addr, sizeof(_addr)) != 0) {
                try {
                        bind(_server_file_descriptor, (struct sockaddr *)&_addr, sizeof(_addr));

                } catch (const std::exception& e) {
                        std::cout<< "bind failed"<<std::endl;
                }
                // f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen                          
                
        }

        void receive() {
                struct sockaddr_in remaddr;     /* remote address */
                socklen_t addrlen = sizeof(remaddr);            /* length of addresses */
                int recvlen;                    /* # bytes received */        
                unsigned char buffer[BUFFER_SIZE];     /* receive buffer */  
                /* now loop, receiving data and printing what we received */
                for (;;) {
                        cout<<"waiting on port " << PORT<<endl;
                        recvlen = recvfrom(_server_file_descriptor, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
                        cout<<"received " << recvlen << " bytes"<<endl;
                        if (recvlen > 0) {
                                buffer[recvlen] = 0;
                                cout<<"received message:  "<<buffer<<endl;
                        } else if (recvlen < 0) {
                                throw "recvfrom failed";
                        }
                }
                /* never exits */
        }

        private:
        int _server_file_descriptor;                         /* our socket */
        struct sockaddr_in _addr;      /* our address */

};

int main(int argc, char const *argv[]) {

        UDP_Server s;
        s.receive();
        // while(1) {
        //      s.receive();   
        // }
}