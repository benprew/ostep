#include <stdio.h>
#include "common.h"
#include "common_threads.h"
// This is question 3
//
// 3. Next, build a version of the sloppy counter. Once again, measure its
// performance as the number of threads varies, as well as the threshold. Do the
// numbers match what you see in the chapter?

#include <pthread.h>
#include <stdlib.h>

// My laptop has 4 cores, single CPU
#define NUMCPUS 4

typedef struct __counter_t {
  int global; // global count
  pthread_mutex_t glock; // global lock
  int local[NUMCPUS]; // per-CPU count
  pthread_mutex_t llock[NUMCPUS]; // ... and locks
  int threshold; // update frequency
} counter_t;

// init: record threshold, init locks, init values
// of all local counts and global count
void init(counter_t *c, int threshold) {
  c->threshold = threshold;
  c->global = 0;
  pthread_mutex_init(&c->glock, NULL);
  int i;
  for (i = 0; i < NUMCPUS; i++) {
    c->local[i] = 0;
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void update(counter_t *c, int threadID, int amt) {
  int cpu = threadID % NUMCPUS;
  pthread_mutex_lock(&c->llock[cpu]);
  c->local[cpu] += amt;
  if (c->local[cpu] >= c->threshold) {
    // transfer to global (assumes amt>0)
    pthread_mutex_lock(&c->glock);
    c->global += c->local[cpu];
    pthread_mutex_unlock(&c->glock);
    c->local[cpu] = 0;
  }
  pthread_mutex_unlock(&c->llock[cpu]);
}

// get: just return global amount (approximate)
int get(counter_t *c) {
  pthread_mutex_lock(&c->glock);
  int val = c->global;
  pthread_mutex_unlock(&c->glock);
  return val; // only approximate!
}

typedef struct { counter_t *c; int tid; } myarg_t;


void *add_ten_million(void *arg) {
  myarg_t *args = (myarg_t *) arg;
  counter_t *c = args->c;
  int tid = args->tid;
  for (int i = 0; i < 1e7; i++) {
    update(c, tid, 1);
  }
  return (void *) EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  int num_threads = 5;
  int threshold = 256;
  int start;
  counter_t c;
  if (argc >= 2) {
    num_threads = atoi(argv[1]);
  }

  if (argc == 3) {
    threshold = atoi(argv[2]);
  }
  pthread_t threads[num_threads];

  start = Time_GetSeconds();
  init(&c, threshold);
  for(int i = 0; i < num_threads; i++) {
    myarg_t args = { &c, i };
    Pthread_create(&threads[i], NULL, add_ten_million, &args);
  }
  for (int i = 0; i < num_threads; i++) {
    Pthread_join(threads[i], NULL);
  }
  int dur = Time_GetSeconds() - start;
  printf("Time taken: %d sec [threads=%d,threshold=%d,total=%d]\n", dur, num_threads, threshold, get(&c));

  return EXIT_SUCCESS;
}
