#ifndef THREAD_HELPERS_H
#define THREAD_HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * erpc doesn't seem to provide a way to get the current thread ID from C code, so we build our own
 * wrapper.
 */
void* get_current_thread_id(void);

#ifdef __cplusplus
}
#endif

#endif /* THREAD_HELPERS_H */
