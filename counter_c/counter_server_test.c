#include "erpc_transport_setup.h"
#include "erpc_server_setup.h"
#include "erpc_mbf_setup.h"
#include "counter_server.h"
#include <stdio.h>
#include <assert.h>

static int32_t g_counter = 0;

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
    erpc_transport_t transport = erpc_transport_tcp_init("localhost", 12345, true);
    assert(transport);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_server_init(transport, message_buffer_factory);

    erpc_service_t service = create_Counter_service();
    erpc_add_service_to_server(service);

    erpc_server_run();

    return 0;
}
