#include "erpc_setup_tcp_transport.h"
#include "erpc_manually_constructed.h"
#include "erpc_tcp_transport.h"
#include "erpc_transport_setup.h"

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

static ManuallyConstructed<TCPTransport> s_transport;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

erpc_transport_t erpc_transport_tcp_init(const char *host, uint16_t port, bool isServer)
{
    s_transport.construct(host, port, isServer);
    return (s_transport->open() == kErpcStatus_Success) ?
        reinterpret_cast<erpc_transport_t>(s_transport.get()) : NULL;
}
