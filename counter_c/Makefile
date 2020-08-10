.PHONY: all
all: counter_client_test counter_server_test

erpc_setup_tcp_transport.o: erpc_setup_tcp_transport.cpp erpc_setup_tcp_transport.h
	g++ -I $(ERPC_ROOT)/include/erpc -c $<

counter_client.o: gen/counter_client.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -c $<

counter_server.o: gen/counter_server.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -c $<

counter_client_test.o: counter_client_test.c gen/counter.h
	gcc -I gen -I $(ERPC_ROOT)/include/erpc -c $<

counter_server_test.o: counter_server_test.c gen/counter_server.h
	gcc -I gen -I $(ERPC_ROOT)/include/erpc -c $<

counter_client_test: counter_client_test.o erpc_setup_tcp_transport.o counter_client.o
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread

counter_server_test: counter_server_test.o erpc_setup_tcp_transport.o counter_server.o
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread

gen/counter_%.cpp gen/%.h: counter.erpc
	$(ERPC_ROOT)/bin/erpcgen --output gen $<

clean:
	rm -f counter_client_test counter_server_test *.o
