#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "erpc_arbitrated_client_setup.h"
#include "erpc_error_handler.h"
#include "erpc_error_handler.h"
#include "erpc_mbf_setup.h"
#include "erpc_server_setup.h"
#include "erpc_transport_setup.h"
#include "timer_cb_server.h"
#include "timer_main.h"
#include "thread_helpers.h"

static TimerHandle_t timers[4];
static uint32_t cb_counts[4];

static pthread_t server_thread;
static sem_t server_ready_sem;

void timer_handler_a(TimerHandle_t t, void_star context)
{
    void *ctx = (void *)context;
    uint32_t *count = ctx;

    *count += 1;
    printf("In %s: timer is %u, count is %u\n", __func__, t, *count);

    if (*count >= 5) {
        timer_deregister(t);
    }
}

void timer_handler_b(TimerHandle_t t, void_star context)
{
    void *ctx = (void *)context;
    uint32_t *count = ctx;

    *count += 1;
    printf("In %s: timer is %u, count is %u\n", __func__, t, *count);

    if (*count >= 3) {
        timer_deregister(t);
    }
}

static void* run_server(void *thread_arg)
{
    // Required for nested calls
    erpc_arbitrated_client_set_server_thread_id(get_current_thread_id());

    if (sem_post(&server_ready_sem)) {
        fprintf(stderr, "failed to post to semaphore - %s\n", strerror(errno));
        exit(1);
    }
    erpc_status_t run_status = erpc_server_run();

    printf("erpc_server_run finished with status (%d)\n", run_status);

    return NULL;
}

int main(int argc, char **argv)
{
    /*
     * In this section, we set up the client side of the Timer interface client
     */
    erpc_transport_t tcp_transport = erpc_transport_tcp_init("localhost", 12345, false);
    assert(tcp_transport);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_transport_t arb_transport = erpc_arbitrated_client_init(tcp_transport, message_buffer_factory);
    erpc_arbitrated_client_set_error_handler(erpc_error_handler);

    /*
     * In this section, we set up the TimerCb interface server
     */
    erpc_server_t server = erpc_server_init(arb_transport, message_buffer_factory);
    erpc_service_t timer_cb_service = create_TimerCb_service();
    erpc_add_service_to_server(timer_cb_service);

    // This is required for nested call support
    erpc_arbitrated_client_set_server(server);

    // Make sure the server is up and running before calling any functions as a client
    sem_init(&server_ready_sem, 0, 0);
    pthread_create(&server_thread, NULL, run_server, NULL);
    sem_wait(&server_ready_sem);

    timers[0] = timer_register(5000, timer_handler_a, (void_star)&cb_counts[0]);
    timers[1] = timer_register(3000, timer_handler_b, (void_star)&cb_counts[1]);

    // This should wait forever because the server thread shouldn't exit
    pthread_join(server_thread, NULL);

    return 0;
}
