.PHONY: all
all: timer_client_test timer_server_test

erpc_error_handler.o: erpc_error_handler.c erpc_error_handler.h
	gcc -I $(ERPC_ROOT)/include/erpc -c $<

thread_helpers.o: thread_helpers.cpp thread_helpers.h
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -c $<

timer_main_client.o: gen/timer_main_client.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -c $<

timer_main_server.o: gen/timer_main_server.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -c $<

timer_cb_client.o: gen/timer_cb_client.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -c $<

timer_cb_server.o: gen/timer_cb_server.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -c $<

timer_client_test.o: timer_client_test.c gen/timer_main.h gen/timer_cb_server.h
	gcc -I gen -I $(ERPC_ROOT)/include/erpc -c $<

timer_server_test.o: timer_server_test.c gen/timer_main_server.h gen/timer_cb.h
	gcc -I gen -I $(ERPC_ROOT)/include/erpc -c $<

timer_client_test: timer_client_test.o erpc_error_handler.o timer_main_client.o timer_cb_server.o thread_helpers.o
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread

timer_server_test: timer_server_test.o erpc_error_handler.o timer_main_server.o timer_cb_client.o thread_helpers.o
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread -l rt

gen/timer_%.cpp gen/%.h: timer.erpc
	$(ERPC_ROOT)/bin/erpcgen --output gen $<

clean:
	rm -f timer_client_test timer_server_test *.o
	rm -rf gen
