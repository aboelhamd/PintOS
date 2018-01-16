#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

struct child_process
  {
    tid_t tid;
    struct list_elem elem;
    bool parent_iswaiting;
    int exit_state;
    semaphore sema_child;
  }
  
tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (int);
void process_activate (void);

#endif /* userprog/process.h */
