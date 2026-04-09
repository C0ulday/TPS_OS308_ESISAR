# OS308 - Operating Systems Labs (ESISAR - Grenoble INP)
# (Ressources in French)

## Overview

A collection of systems programming labs focused on **UNIX signals**, **inter-process communication (IPC)**, and **process synchronization** in C. These exercises build foundational knowledge for real-time embedded systems and RTOS concepts such as task synchronization, signal handling, and resource sharing.

## Lab 5 - Signal Handling (Part 1)

### Exercise 1 - Ignoring Signals
- Program that attempts to ignore **all signals** using `signal(sig, SIG_IGN)`
- Identifies which signals cannot be ignored (e.g., `SIGKILL`, `SIGSTOP`)
- Uses `strsignal()` to display symbolic signal names

### Exercise 2 - SIGINT Between Parent and Child
- Parent process creates a child, waits 5 seconds, then sends `SIGINT` to terminate it
- Child catches `SIGINT`, waits 2 seconds, then exits gracefully
- Parent waits for child termination using `wait()`

### Exercise 3 - Custom Signal Handlers (SIGUSR1 / SIGUSR2)
- Program registers custom handlers for all signals
- `SIGUSR1` triggers `system("who")` to list logged-in users
- `SIGUSR2` triggers `system("df .")` to display disk usage
- All other signals are handled by a generic function that prints the signal number

## Lab 6 - Signal Handling (Part 2)

### Exercise 1 - Parent/Child Synchronization
- Parent prints **odd** numbers (1, 3, 5...), child prints **even** numbers (2, 4, 6...)
- Processes are synchronized using signals to produce sequential output: `1 2 3 ... 100`
- Demonstrates IPC-based task synchronization (similar to semaphore-based coordination in RTOS)

### Exercise 2 - Clock (H:M:S)
- Three processes `H`, `M`, `S` simulate clock hands
- `S` receives `SIGALRM` every second via `alarm(1)` and increments a counter
- When `S` rolls over (59 → 0), it signals `M`; when `M` rolls over, it signals `H`
- Demonstrates **periodic task scheduling** and **cascading event propagation**

### Exercise 3 - Russian Roulette
- Parent creates 6 child processes numbered 1-6
- Each child reads a "barrel" file, if the value matches their number, they terminate
- Surviving children signal the parent; if one dies, the parent notifies all others to stop
- Demonstrates **multi-process coordination**, **file-based shared state**, and **signal-driven control flow**

## Relevance to Embedded / RTOS Development

These labs directly map to real-time embedded concepts:

| Lab Concept | RTOS Equivalent |
|---|---|
| Signal handling (`SIGUSR1/2`) | Interrupt handlers, ISR callbacks |
| Parent/child synchronization | Task synchronization with semaphores |
| `alarm()` + `SIGALRM` | Timer interrupts, periodic tasks |
| Shared file (Russian Roulette) | Shared resource with mutual exclusion |
| Process priorities & scheduling | Task priorities, preemptive scheduling |

## Build & Run

```bash
gcc -o ex1 tp5_ex1.c
./ex1

# From another terminal, send signals:
kill -SIGUSR1 <pid>
kill -SIGUSR2 <pid>
kill -9 <pid>        # Only SIGKILL terminates the signal-ignoring program
```

## Tools & Environment
- **Language:** C (POSIX)
- **OS:** Linux (Ubuntu / Debian)
- **Compiler:** GCC
- **Concepts:** Signals, fork(), wait(), IPC, process synchronization

## Author
Sita Coulibaly - ESISAR, Grenoble INP (2024)
