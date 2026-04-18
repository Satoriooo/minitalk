This project has been created as part of the 42 curriculum by shirose.

# Minitalk

## Description
Minitalk is a small data exchange program using UNIX signals. The goal of this project is to create a client and a server. The client takes the server PID and a string to send as parameters. The client must send the specified string to the server. Communication between the client and server must exclusively use UNIX signals. You can only use these two signals: SIGUSR1 and SIGUSR2.

### Instructions
### Compilation
To compile the source files, simply run make at the root of the repository. This will compile the project and generate the two required executables: server and client.

```bash
make
```

**Execution**
1. First, launch the server. Upon launch, it prints out its PID.

```bash
./server
PID <SERVER PID>
```

2. Open a second terminal window and run the client. 

```bash
./client <SERVER_PID> "Your message here"
```


## Resources
### Documntations
- [sigaction(2) — Linux manual page](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [【C言語】signalとsigactionの使い方を分かりやすく解説（実装サンプルあり）](https://en-junior.com/sigaction-signal/#index_id9) (ENG: Easy explanation of signal and sigaction)
- [sig_atomic_t](https://www.cs.wm.edu/~smherwig/courses/csci415-common/signals/sig_atomic/index.html)

### AI usage
- Instruction of how to compile two programs with one Makefile
- 