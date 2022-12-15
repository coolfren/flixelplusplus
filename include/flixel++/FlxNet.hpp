#ifndef FLXNET_HPP
#define FLXNET_HPP

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <memory.h>
#endif

namespace Flx {
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
        void connect();
    };
}

#endif