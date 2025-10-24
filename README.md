# Thread Pool Implementation in C

A simple thread pool implementation in C using POSIX threads (pthreads) that demonstrates the producer-consumer pattern with proper synchronization.

## Project Structure

```
.
├── include/
│   └── thread_pool.h        # Public header: constants, Task type, API
├── src/
│   └── threadpool.c         # Implementation and demo main()
└── README.md
```

## Features

- **Fixed-size thread pool** with `DEFAULT_NUM_THREADS` worker threads (default: 8)
- **Thread-safe task queue** using mutex locks
- **Efficient waiting** using condition variables (no busy-waiting)
- **Graceful shutdown** to cleanly terminate all threads
- **Producer-consumer pattern** for task distribution

## Build

### Using gcc directly
```bash
gcc -pthread -Iinclude src/threadpool.c -o threadpool
```

### Using the included Makefile
```bash
make        # build
make run    # build and run
make clean  # remove binary
```

## Run
```bash
./threadpool
```

## Output

The program outputs the sum of randomly generated numbers processed by different threads, for example:
```
The sum of 42 and 67 is 109
The sum of 23 and 89 is 112
...
```

## Key Types and API

- `Task` (from `include/thread_pool.h`): holds two integers to add
- `executeTask(Task*)`: executes the task
- `Submit_Task(Task)`: thread-safe task submission to the queue
- `start_thread(void*)`: worker thread entry function

Constants defined in `include/thread_pool.h`:
- `DEFAULT_NUM_THREADS` (default: 8)
- `TOTAL_TASKS` (default: 100)

## Synchronization Flow
```
Producer (Main Thread)          Workers (N Threads)
        |                              |
        |--[Submit tasks]-->  [Wait on condition]
        |                              |
        |                     [Wake up & process]
        |                              |
        |--[Set shutdown]-->  [Check shutdown flag]
        |                              |
        |--[Broadcast]------>  [Finish & exit]
        |                              |
   [Join threads]              [Thread exits]
```

