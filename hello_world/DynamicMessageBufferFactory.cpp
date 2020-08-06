#include "DynamicMessageBufferFactory.h"
#include <assert.h>

// It seems that eRPC offers an opaque version of this for C users in
// erpc_c/setup/erpc_setup_mbf_dynamic.cpp, but the underlying class isn't available through headers

erpc::MessageBuffer DynamicMessageBufferFactory::create()
{
    uint8_t *buf = new uint8_t[1024];
    return erpc::MessageBuffer(buf, 1024);
}

void DynamicMessageBufferFactory::dispose(erpc::MessageBuffer *buf)
{
    assert(buf);
    if (*buf)
    {
        delete[] buf->get();
    }
}
