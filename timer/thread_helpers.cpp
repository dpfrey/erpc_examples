#include "erpc_threading.h"
#include "thread_helpers.h"

void* get_current_thread_id(void)
{
    return erpc::Thread::getCurrentThreadId();
}
