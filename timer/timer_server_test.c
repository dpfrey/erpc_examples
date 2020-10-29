#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include "erpc_arbitrated_client_setup.h"
#include "erpc_error_handler.h"
#include "erpc_mbf_setup.h"
#include "erpc_server_setup.h"
#include "erpc_transport_setup.h"
#include "timer_cb.h"
#include "timer_main_server.h"
#include "thread_helpers.h"

#define NUM_TIMERS_SUPPORTED 2
static struct {
    bool in_use;
    timer_t timer_id;
    TimerHandler_t handler;
    void_star context;
} s_timers[NUM_TIMERS_SUPPORTED];


void handle_timer_expiry(union sigval signal)
{
    int timer_index = signal.sival_int;
    printf("timer with index %d expired\n", timer_index);
    s_timers[timer_index].handler(timer_index, s_timers[timer_index].context);
}

TimerHandle_t timer_register(uint16_t period_ms, TimerHandler_t handler, void_star context)
{
    printf("Called %s\n", __func__);

    for (int i = 0; i < NUM_TIMERS_SUPPORTED; i++) {
        if (!s_timers[i].in_use) {
            struct sigevent sev = {
                .sigev_notify = SIGEV_THREAD,
                .sigev_notify_function = handle_timer_expiry,
                .sigev_value = { .sival_int = i, },
            };
            if (timer_create(CLOCK_MONOTONIC, &sev, &s_timers[i].timer_id)) {
                fprintf(stderr, "failed to create timer - %s\n", strerror(errno));
                exit(1);
            }

            s_timers[i].in_use = true;
            s_timers[i].handler = handler;
            s_timers[i].context = context;

            const long seconds = period_ms / 1000;
            const long nanoseconds = (period_ms % 1000) * 1000 * 1000;
            const struct itimerspec ts = {
                .it_value = { .tv_sec = seconds, .tv_nsec = nanoseconds, },
                .it_interval = { .tv_sec = seconds, .tv_nsec = nanoseconds, },
            };
            if (timer_settime(s_timers[i].timer_id, 0, &ts, NULL)) {
                fprintf(stderr, "failed to set timer - %s\n", strerror(errno));
                exit(1);
            }

            return (TimerHandle_t)i;
        }
    }

    fprintf(stderr, "Couldn't allocate a timer\n");
    exit(1);
}

void timer_deregister(TimerHandle_t timer)
{
    printf("Called %s\n", __func__);

    if (timer >= NUM_TIMERS_SUPPORTED) {
        return;
    }

    if (!s_timers[timer].in_use) {
        return;
    }

    if (timer_delete(s_timers[timer].timer_id)) {
        fprintf(stderr, "Couldn't delete the timer - %s\n", strerror(errno));
        exit(1);
    }

    s_timers[timer].in_use = false;
}

int main(int argc, char **argv)
{
    erpc_transport_t tcp_transport = erpc_transport_tcp_init("localhost", 12345, true);
    assert(tcp_transport);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_transport_t arb_transport = erpc_arbitrated_client_init(tcp_transport, message_buffer_factory);
    erpc_arbitrated_client_set_error_handler(erpc_error_handler);

    erpc_server_t server = erpc_server_init(arb_transport, message_buffer_factory);

    erpc_arbitrated_client_set_server_thread_id(get_current_thread_id());
    erpc_arbitrated_client_set_server(server);

    erpc_service_t timer_service = create_Timer_service();
    erpc_add_service_to_server(timer_service);

    // TODO: Do we need to run this in a separate thread?
    erpc_server_run();

    return 0;
}
