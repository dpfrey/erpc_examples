#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif // cplusplus

#include "erpc_common.h"
#include <stdint.h>

void erpc_error_handler(erpc_status_t err, uint32_t function_id);

#ifdef __cplusplus
}
#endif // cplusplus

#endif // ERROR_HANDLER_H
