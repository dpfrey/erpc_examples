#include "erpc_basic_codec.h"
#include "erpc_client_manager.h"
#include "erpc_tcp_transport.h"
#include "counter.h"
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

    std::cout << "counter_set(15)" << std::endl;
    counter_set(15);
    std::cout << "counter_get() -> " << counter_get() << std::endl;
    std::cout << "counter_increment() -> " << counter_increment() << std::endl;
    std::cout << "counter_decrement() -> " << counter_decrement() << std::endl;
    std::cout << "counter_decrement_by(20) -> " << counter_decrement_by(20) << std::endl;
    std::cout << "counter_increment_by(30) -> " << counter_increment_by(30) << std::endl;

    return 0;
}
