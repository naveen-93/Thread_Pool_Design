#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "thread_pool.h"

Task* Task_Queue;

int NUM_THREAD = DEFAULT_NUM_THREADS;
int Task_Count = 0;
int shutdown = 0;

pthread_mutex_t lockQ;
pthread_cond_t condQ;

void executeTask(Task* task) {
  int result = task->a + task->b;
  printf("The sum of %d and %d is %d\n", task->a, task->b, result);
}
void Submit_Task(Task task) {
  pthread_mutex_lock(&lockQ);
  Task_Queue[Task_Count] = task;
  Task_Count++;
  pthread_cond_signal(&condQ);
  pthread_mutex_unlock(&lockQ);
}

void* start_thread() {
  while (1) {
    pthread_mutex_lock(&lockQ);
    while (Task_Count == 0 && shutdown == 0) {
      pthread_cond_wait(&condQ, &lockQ);
    }

    if (shutdown == 1 && Task_Count == 0) {
      pthread_mutex_unlock(&lockQ);
      break;
    }

    Task T;

    T = Task_Queue[0];

    for (int i = 0; i < Task_Count - 1; i++) {
      Task_Queue[i] = Task_Queue[i + 1];
    }

    Task_Count--;

    pthread_mutex_unlock(&lockQ);
    executeTask(&T);
  }
  return NULL;
}
int main() {
  pthread_mutex_init(&lockQ, NULL);
  pthread_cond_init(&condQ, NULL);

  Task_Queue = (Task*)calloc(TOTAL_TASKS, sizeof(Task));
  pthread_t threads[NUM_THREAD];

  for (int i = 0; i < NUM_THREAD; ++i) {
    if (pthread_create(threads + i, NULL, start_thread, NULL) != 0) {
      perror("Failed to create the thread");
    }
  }

  for (int i = 0; i < TOTAL_TASKS; ++i) {
    Task t = {.a = rand() % 100, .b = rand() % 100};
    Submit_Task(t);
  }

  pthread_mutex_lock(&lockQ);
  shutdown = 1;
  pthread_cond_broadcast(&condQ);
  pthread_mutex_unlock(&lockQ);

  for (int i = 0; i < NUM_THREAD; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("Failed to join the thread");
    }
  }
  pthread_mutex_destroy(&lockQ);
  pthread_cond_destroy(&condQ);
  return 0;
}


