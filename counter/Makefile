.PHONY: all
all: counter_client_test counter_server_test

counter_client_test: counter_client_test.cpp DynamicMessageBufferFactory.cpp gen/counter_client.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $? -l erpc -l pthread

counter_server_test: counter_server_test.cpp DynamicMessageBufferFactory.cpp gen/counter_server.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $? -l erpc -l pthread

gen/counter_%.cpp: counter.erpc
	$(ERPC_ROOT)/bin/erpcgen --output gen $<

clean:
	rm -f counter_client_test counter_server_test
