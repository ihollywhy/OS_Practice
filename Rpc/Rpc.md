#### This program is tested on ubuntu14.04

- make sure you have install rpcbind

using `sudo apt-get install rpcbind` to install it

- change to the root dir of this program
- type `make all` in the terminal
- type `./receiver` in terminal
- type `./processor` in another terminal
- input some strings contain `C00L`, they will appear in the `secretes.out`
- the default IP address is `127.0.0.1`

What the code does:
In this code, we use RPC for the connection between two process, use rpcgen and
name.x to create the connector. It has procedure number, program version number and
program number.
In `processor.c` we create the server process *getsecrets_1_svc* which is ready to be
used by receiver.c
In `receiver.c` we use the information above to create rpc connection and call for
server process.