# Protocol Example
## C++ Protocol Implementation 
### To build, use:
```
bash build.sh
```
Binaries are in ```Bin``` folder

### Usage:
```
./Server <port> <code> <userId> <command>
./Client <server port> <userId> <command>
```

### How it works: 
At first, Server sends payload to client, then recieve payload from client
Server:
```
-----------SERVER-----------
Server listening...
In char array: 
d
In protocol type: 
Response code: 12
UserId: 13
Command: d

```
Client:
```
-----------CLIENT-----------
In char array: 

c
In protocol type: 
Response code: 10
UserId: 11
Command: c

```
