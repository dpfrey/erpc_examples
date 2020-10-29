#include "erpc_transport_setup.h"
#include "erpc_client_setup.h"
#include "erpc_mbf_setup.h"
#include "counter.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv)
{
    erpc_transport_t transport = erpc_transport_tcp_init("localhost", 12345, false);
    assert(transport);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_client_init(transport, message_buffer_factory);

    printf("counter_set(15)\n");
    counter_set(15);
    printf("counter_get() -> %d\n", counter_get());
    printf("counter_increment() -> %d\n", counter_increment());
    printf("counter_decrement() -> %d\n", counter_decrement());
    printf("counter_decrement_by(20) -> %d\n", counter_decrement_by(20));
    printf("counter_increment_by(30) -> %d\n", counter_increment_by(30));

    return 0;
}
