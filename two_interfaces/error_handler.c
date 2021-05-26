#include "error_handler.h"

#include <stdio.h>

void erpc_error_handler(erpc_status_t err, uint32_t function_id)
{
    if (err != kErpcStatus_Success)
    {
        fprintf(stderr, "eRPC Error: (%d) in function (%u)", err, function_id);
    }
}
