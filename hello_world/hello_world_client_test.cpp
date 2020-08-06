#include "erpc_basic_codec.h"
#include "erpc_client_manager.h"
#include "erpc_tcp_transport.h"
#include "hello_world.h"
#include "DynamicMessageBufferFactory.h"
#include <iostream>

erpc::TCPTransport g_transport("localhost", 12345, false);
erpc::BasicCodecFactory g_codecFactory;
erpc::Crc16 g_crc16;
DynamicMessageBufferFactory g_messageBufferFactory;
erpc::ClientManager *g_client;

int main(int argc, char **argv)
{
    g_client = new erpc::ClientManager();

    erpc_status_t err = g_transport.open();
    if (err)
    {
        std::cout << "Failed to open connection" << std::endl;
        return err;
    }

    g_transport.setCrc16(&g_crc16);
    g_client->setMessageBufferFactory(&g_messageBufferFactory);
    g_client->setTransport(&g_transport);
    g_client->setCodecFactory(&g_codecFactory);

    hello_world();

    return 0;
}
