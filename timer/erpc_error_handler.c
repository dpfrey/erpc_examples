#include "erpc_error_handler.h"
#include <stdio.h>

void erpc_error_handler(erpc_status_t err, uint32_t function_id)
{
    if (err != kErpcStatus_Success) {
        printf("eRPC encountered an error (%d) in function (%u)\n", err, function_id);
    }
}
