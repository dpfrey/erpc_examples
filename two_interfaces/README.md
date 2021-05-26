# Two Interfaces Example

This example uses two trivial interfaces in two different `.erpc` IDL files to demonstrate a
problem. The problem is that if `erpcgen` is invoked once for each IDL file, then the first service
of found in each invocation will be assigned the same service identifier. When the code is all
linked together and both services are registered on the server side, they will both have the same
ID.

This is the output of the program when built using an eRPC that has the patch of
https://github.com/EmbeddedRPC/erpc/pull/181 applied and both `.erpc` files are passed to `erpcgen`
at once:

```
$ ./working_client
About to call f()
Completed call to f()
About to call g()
Completed call to g()

$ ./working_server
Called f()
Called g()
```

And this is what happens if `erpcgen` is invoked separately for each `.erpc` file:

```
$ ./broken_client
About to call f()
Completed call to f()
About to call g()
Completed call to g()

$ ./broken_server
Called f()
Called f()
```

Notice that `f()` is called twice on the broken server even though `g()` was requested.
