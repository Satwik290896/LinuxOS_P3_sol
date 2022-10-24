#ifndef _INCLUDE_PSTRACE_H
#define _INCLUDE_PSTRACE_H

#include <linux/atomic.h>

struct pstrace {
	char comm[16];
	long state;
	pid_t pid;
	pid_t tid;
};

#define PSTRACE_BUF_SIZE 500
#define PSTRACE_ADD_RUNNABLE 1

struct pstrace_kernel {
	struct pstrace entry[PSTRACE_BUF_SIZE];
	bool empty;
	int head, tail;
	spinlock_t pstrace_lock;
	atomic_t counter;
};

struct pstrace_traced {
	atomic_t pid;
};

struct pstrace_evt {
	long counter;
	struct pstrace buf[PSTRACE_BUF_SIZE];
	bool woken;
	bool copied;
	wait_queue_head_t evt_waitq; // WARNING: this lock is used for
						 // all data fields, not just waitq
	int nr_entries;
	struct list_head head;
};

void pstrace_add(struct task_struct *p, long state);
void wake_blocked_gets(void);

#endif
