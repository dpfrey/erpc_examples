.PHONY: all
all: working_client working_server broken_client broken_server


# object files of erpcgen generated code for single invocation of erpcgen version
one_call_intf1_client.o: gen_one_call/intf1_client.cpp gen_one_call/intf1.h
	g++ -I gen_one_call -I $(ERPC_ROOT)/include/erpc -o $@ -c $<

one_call_intf2_client.o: gen_one_call/intf2_client.cpp gen_one_call/intf2.h
	g++ -I gen_one_call -I $(ERPC_ROOT)/include/erpc -o $@ -c $<

one_call_intf1_server.o: gen_one_call/intf1_server.cpp gen_one_call/intf1.h gen_one_call/intf1_server.h
	g++ -I gen_one_call -I $(ERPC_ROOT)/include/erpc -o $@ -c $<

one_call_intf2_server.o: gen_one_call/intf2_server.cpp gen_one_call/intf2.h gen_one_call/intf2_server.h
	g++ -I gen_one_call -I $(ERPC_ROOT)/include/erpc -o $@ -c $<


# object files of erpcgen generated code for multiple invocation of erpcgen version
two_calls_intf1_client.o: gen_two_calls/intf1_client.cpp gen_two_calls/intf1.h
	g++ -I gen_two_calls -I $(ERPC_ROOT)/include/erpc -o $@ -c $<

two_calls_intf2_client.o: gen_two_calls/intf2_client.cpp gen_two_calls/intf2.h
	g++ -I gen_two_calls -I $(ERPC_ROOT)/include/erpc -o $@ -c $<

two_calls_intf1_server.o: gen_two_calls/intf1_server.cpp gen_two_calls/intf1.h gen_two_calls/intf1_server.h
	g++ -I gen_two_calls -I $(ERPC_ROOT)/include/erpc -o $@ -c $<

two_calls_intf2_server.o: gen_two_calls/intf2_server.cpp gen_two_calls/intf2.h gen_two_calls/intf2_server.h
	g++ -I gen_two_calls -I $(ERPC_ROOT)/include/erpc -o $@ -c $<

error_handler.o: error_handler.c
	gcc -I $(ERPC_ROOT)/include/erpc -c $<

# working binaries
working_client: multiple_interfaces_client.c error_handler.o one_call_intf1_client.o one_call_intf2_client.o
	g++ -I gen_one_call -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread

working_server: multiple_interfaces_server.c one_call_intf1_server.o one_call_intf2_server.o
	g++ -I gen_one_call -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread


# broken binaries
broken_client: multiple_interfaces_client.c error_handler.o two_calls_intf1_client.o two_calls_intf2_client.o
	g++ -I gen_two_calls -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread

broken_server: multiple_interfaces_server.c two_calls_intf1_server.o two_calls_intf2_server.o
	g++ -I gen_two_calls -I $(ERPC_ROOT)/include/erpc -L $(ERPC_ROOT)/lib -o $@ $^ -l erpc -l pthread


# erpcgen calls
gen_one_call/intf%.cpp gen_one_call/intf%.h: intf1.erpc intf2.erpc
	$(ERPC_ROOT)/bin/erpcgen --output gen_one_call $^

gen_two_calls/intf1%.cpp gen_two_calls/intf1%.h: intf1.erpc
	$(ERPC_ROOT)/bin/erpcgen --output gen_two_calls $^

gen_two_calls/intf2%.cpp gen_two_calls/intf2%.h: intf2.erpc
	$(ERPC_ROOT)/bin/erpcgen --output gen_two_calls $^


.PHONY: clean
clean:
	rm -rf gen_one_call gen_two_calls *.o working_client working_server broken_client broken_server
