.PHONY: all
all: hello_world_client_test hello_world_server_test

hello_world_client_test: hello_world_client_test.cpp DynamicMessageBufferFactory.cpp gen/hello_world_client.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $? -l erpc -l pthread

hello_world_server_test: hello_world_server_test.cpp DynamicMessageBufferFactory.cpp gen/hello_world_server.cpp
	g++ -I gen -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $? -l erpc -l pthread

gen/hello_world_%.cpp: hello_world.erpc
	$(ERPC_ROOT)/bin/erpcgen --output gen $<

clean:
	rm -f hello_world_client_test hello_world_server_test
