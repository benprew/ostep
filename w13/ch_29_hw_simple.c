#include <stdio.h>
#include "common.h"
#include "common_threads.h"

// This is question #2
//
// 2. Now, build a simple concurrent counter and measure how long it takes to
// increment the counter many times as the number of threads increases. How many
// CPUs are available on the system you are using? Does this number impact your
// measurements at all?

typedef struct __counter_t {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
  c->value = 0;
  Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  c->value++;
  Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  c->value--;
  Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  int rc = c->value;
  Pthread_mutex_unlock(&c->lock);
  return rc;
}

void *add_ten_million(void *arg) {
  counter_t *c = (counter_t *) arg;
  for (int i = 0; i < 1e7; i++) {
    increment(c);
  }
  return (void *) EXIT_SUCCESS;
}

int main_no_threads(int argc, char* argv[]) {
  int num_threads = 5;
  int start;
  counter_t c;
  if (argc >= 2) {
    num_threads = atoi(argv[1]);
  }

  start = Time_GetSeconds();
  init(&c);
  for(int i = 0; i < num_threads; i++) {
    add_ten_million(&c);
  }
  int dur = Time_GetSeconds() - start;

  printf("Time taken: %d sec [threads=0,total=%d]\n", dur, get(&c));

  return EXIT_SUCCESS;
}


int main_threads(int argc, char* argv[]) {
  int num_threads = 5;
  int start;
  counter_t c;
  if (argc >= 2) {
    num_threads = atoi(argv[1]);
  }
  pthread_t threads[num_threads];

  start = Time_GetSeconds();
  init(&c);
  for(int i = 0; i < num_threads; i++) {
    Pthread_create(&threads[i], NULL, add_ten_million, &c);
  }
  for (int i = 0; i < num_threads; i++) {
    Pthread_join(threads[i], NULL);
  }
  int dur = Time_GetSeconds() - start;

  printf("Time taken: %d sec [threads=%d,total=%d]\n", dur, num_threads, get(&c));

  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  if (argc == 3) {
    return main_no_threads(argc, argv);
  }
  return main_threads(argc, argv);
}
