# Thread Pool Implementation in C

A simple thread pool implementation in C using POSIX threads (pthreads) that demonstrates producer-consumer pattern with proper synchronization.

## Features

- **Fixed-size thread pool** with 8 worker threads
- **Thread-safe task queue** using mutex locks
- **Efficient waiting** using condition variables (no busy-waiting)
- **Graceful shutdown** mechanism to cleanly terminate all threads
- **Producer-consumer pattern** for task distribution

## Concepts Demonstrated

- **Mutex locks** (`pthread_mutex_t`) for protecting shared resources
- **Condition variables** (`pthread_cond_t`) for thread synchronization
- **Thread creation and joining** (`pthread_create`, `pthread_join`)
- **Critical sections** and race condition prevention
- **Graceful thread termination** with shutdown signaling

## How It Works

1. **Initialization**: Creates 8 worker threads that wait for tasks
2. **Task Submission**: Main thread submits 100 tasks to the shared queue
3. **Task Processing**: Worker threads dequeue and execute tasks concurrently
4. **Shutdown**: After all tasks are submitted, signals shutdown and waits for threads to finish remaining work
5. **Cleanup**: Destroys synchronization primitives and exits cleanly

## Compilation
```bash
gcc -pthread threadpool.c -o threadpool
```

## Running
```bash
./threadpool
```

## Output

The program outputs the sum of randomly generated numbers processed by different threads:
```
The sum of 42 and 67 is 109
The sum of 23 and 89 is 112
...
```

## Code Structure

- `Task`: Structure holding task data (two integers to add)
- `Submit_Task()`: Thread-safe task submission to queue
- `start_thread()`: Worker thread function that processes tasks
- `executeTask()`: Executes the actual task (addition operation)

## Synchronization Flow
```
Producer (Main Thread)          Workers (8 Threads)
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

## Key Synchronization Points

1. **Queue access protected by mutex** - Prevents race conditions when adding/removing tasks
2. **Condition variable for waiting** - Threads sleep efficiently until work is available
3. **Shutdown flag + broadcast** - Cleanly signals all threads to finish and exit

## Learning Outcomes

This project demonstrates:
- How to avoid race conditions in multithreaded programs
- Proper use of mutex locks and condition variables
- The producer-consumer design pattern
- How to implement graceful shutdown in threaded applications

## License

MIT License - Feel free to use and modify!