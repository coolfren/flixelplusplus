#ifndef FLXNET_HPP
#define FLXNET_HPP

#ifdef USE_SOCKETS

#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <memory.h>
#include <arpa/inet.h>
#include <stdlib.h>
#endif

namespace Flx {
    /*
    * Provides a platform independent way of handling sockets.
    */
    class Net {
    private:
        #ifdef _WIN32
        SOCKET sock;
        #else
        int sock;
        sockaddr_in addr;
        #endif
    public:
        Net(const char* host, int port);
        ~Net();
        void listen(int connections);
        void send(const char* data);
        std::string read();
        std::string readUntil(char until);
        void connect();
    };
}

#endif
#endif