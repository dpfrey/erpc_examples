#include "erpc_basic_codec.h"
#include "erpc_simple_server.h"
#include "erpc_tcp_transport.h"
#include "hello_world_server.h"
#include "DynamicMessageBufferFactory.h"
#include <iostream>

erpc::TCPTransport g_transport("localhost", 12345, true);
erpc::BasicCodecFactory g_codecFactory;
erpc::Crc16 g_crc16;
DynamicMessageBufferFactory g_messageBufferFactory;
erpc::SimpleServer g_server;

void hello_world(void)
{
    std::cout << "Hello World!" << std::endl;
}

int main(int argc, char **argv)
{
    erpc_status_t err = g_transport.open();
    if (err)
    {
        std::cout << "Failed to open connection" << std::endl;
        return err;
    }

    g_transport.setCrc16(&g_crc16);

    g_server.setMessageBufferFactory(&g_messageBufferFactory);
    g_server.setTransport(&g_transport);
    g_server.setCodecFactory(&g_codecFactory);

    g_server.addService(new HelloWorld_service());

    g_server.run();

    return 0;
}
