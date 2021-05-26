#include "intf1.h"
#include "intf2.h"
#include "error_handler.h"

#include "erpc_client_setup.h"
#include "erpc_mbf_setup.h"
#include "erpc_transport_setup.h"

#include <assert.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    erpc_transport_t transport = erpc_transport_tcp_init("localhost", 12345, false);
    assert(transport);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_client_set_error_handler(erpc_error_handler);
    erpc_client_init(transport, message_buffer_factory);

    printf("About to call f()\n");
    f();
    printf("Completed call to f()\n");

    printf("About to call g()\n");
    g();
    printf("Completed call to g()\n");

    return 0;
}
