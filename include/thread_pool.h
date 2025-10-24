#ifndef THREAD_POOL_H
#define THREAD_POOL_H

// Thread pool configuration constants
#define DEFAULT_NUM_THREADS 8
#define TOTAL_TASKS 100

typedef struct Task {
  int a, b;
} Task;

void executeTask(Task* task);
void Submit_Task(Task task);
void* start_thread();

#endif // THREAD_POOL_H


