#ifndef ERPC_ERROR_HANDLER_H
#define ERPC_ERROR_HANDLER_H

#include <stdint.h>
#include "erpc_common.h"

void erpc_error_handler(erpc_status_t err, uint32_t function_id);

#endif /* ERPC_ERROR_HANDLER_H */
