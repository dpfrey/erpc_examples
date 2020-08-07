#ifndef DYNAMIC_MESSAGE_BUFFER_FACTORY_H
#define DYNAMIC_MESSAGE_BUFFER_FACTORY_H

#include "erpc_message_buffer.h"

class DynamicMessageBufferFactory : public erpc::MessageBufferFactory
{
public:
    virtual erpc::MessageBuffer create();
    virtual void dispose(erpc::MessageBuffer *buf);
};

#endif // DYNAMIC_MESSAGE_BUFFER_FACTORY_H
