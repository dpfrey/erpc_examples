# eRPC Examples

A collection of examples demonstrating key concepts of [eRPC](https://github.com/EmbeddedRPC/erpc)


## Examples

### counter
A simple counter API and a test client/server written using the C++ classes of eRPC.

### counter_c
The same as counter, except written in C instead of C++.

### timer
Demonstrates the use of callbacks.

### two_interfaces
Demonstrates that is is necessary to invoke erpcgen once for all `.erpc` IDL files so that a unique
service ID is generated for each service. See [EmbeddedRPC/erpc PR
#181](https://github.com/EmbeddedRPC/erpc/pull/181) for a proposal that allows erpcgen to receive
multiple files at once.
