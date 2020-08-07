#include "erpc_basic_codec.h"
#include "erpc_simple_server.h"
#include "erpc_tcp_transport.h"
#include "counter_server.h"
#include "DynamicMessageBufferFactory.h"
#include <iostream>

erpc::TCPTransport g_transport("localhost", 12345, true);
erpc::BasicCodecFactory g_codecFactory;
erpc::Crc16 g_crc16;
DynamicMessageBufferFactory g_messageBufferFactory;
erpc::SimpleServer g_server;

int32_t g_counter = 0;

void counter_set(int32_t count)
{
    g_counter = count;
}

int32_t counter_get(void)
{
    return g_counter;
}

int32_t counter_increment_by(int32_t increment)
{
    g_counter += increment;
    return g_counter;
}

int32_t counter_decrement_by(int32_t decrement)
{
    g_counter -= decrement;
    return g_counter;
}

int32_t counter_increment(void)
{
    return counter_increment_by(1);
}

int32_t counter_decrement(void)
{
    return counter_decrement_by(1);
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

    g_server.addService(new Counter_service());

    g_server.run();

    return 0;
}
