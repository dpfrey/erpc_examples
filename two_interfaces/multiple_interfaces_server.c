#include "intf1_server.h"
#include "intf2_server.h"

#include "erpc_transport_setup.h"
#include "erpc_server_setup.h"
#include "erpc_mbf_setup.h"

#include <stdio.h>
#include <assert.h>

// intf1.erpc implementation
void f(void)
{
    printf("Called f()\n");
}

// intf2.erpc implementation
void g(void)
{
    printf("Called g()\n");
}

int main(int argc, char **argv)
{
    erpc_transport_t transport = erpc_transport_tcp_init("localhost", 12345, true);
    assert(transport);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_server_init(transport, message_buffer_factory);

    erpc_service_t one_service = create_One_service();
    erpc_add_service_to_server(one_service);
    erpc_service_t two_service = create_Two_service();
    erpc_add_service_to_server(two_service);

    erpc_server_run();
    return 0;
}
