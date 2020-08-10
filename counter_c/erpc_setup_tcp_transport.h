#ifndef ERPC_SETUP_TCP_TRANSPORT_H
#define ERPC_SETUP_TCP_TRANSPORT_H

#include "erpc_transport_setup.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

erpc_transport_t erpc_transport_tcp_init(const char *host, uint16_t port, bool isServer);

#ifdef __cplusplus
}
#endif

#endif // ERPC_SETUP_TCP_TRANSPORT_H
