#### This program is tested on ubuntu 14.04

- find the IP address in the machine which will run the server program.
- set the inet_addr() in the client.c to the IP address showing in 1 step (default is

127.0.0.1).

- using gcc to compile the two source code.
- first run the server in a machine, then run the client in another machine. This

step will print some connection information if success.

- type some chars in the client contain "C00L" to see changes in the secrets.out.
- type "ctrl+c" in the server to see the output information. You can also type

"exit" in the client to end the two process.