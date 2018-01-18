#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "userprog/process.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#define LOWER_LIMITS ((void *) 0x08048000)
#define STDOUT_FILENO 1
#define STDIN_FILENO 0

static void syscall_handler (struct intr_frame *);
static void check_valid_ptr (void *vaddr);
static void* check_addr (void *addr, unsigned size);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

/* System Call: void exit (int status) */
static void 
exit (int status)
{
	//printf("STATUS %d\n", status);
	thread_current ()->child_process->exit_status = status;
	sema_up (&thread_current ()->child_process->sema_child);
	thread_exit ();
}

/* System Call: void halt (void) */
static void 
halt (void *esp)
{

}

/* System Call: void exit (int status) */
static void 
sys_exit (void *esp)
{
	int status = *((int *)esp + 1);
	exit (status);
}

/* System Call: pid_t exec (const char *cmd_line) */
static pid_t 
exec (void *esp)
{
	char *cmd_line = (char*)((int*)esp +1);
}

/* System Call: int wait (pid_t pid) */
static int 
wait (void *esp)
{
	pid_t pid = (pid_t)*((int*)esp+1);
	return process_wait (pid);
}

/* System Call: bool create (const char *file, unsigned initial_size) */
static bool
create (void *esp)
{
	char* file = (char *)((int*)esp + 4);
	unsigned initial_size = *((unsigned*)esp + 5);
	//printf("file name in create %s initial_size %d\n", file,initial_size);
	return filesys_create (file,initial_size);
}

/* System Call: bool remove (const char *file) */
static bool 
remove (void *esp)
{
	char *file = (char*)((int*)esp +1);
}

/* System Call: int open (const char *file) */
static int 
open (void *esp)
{
	char *file_name = (char *)((int*)esp + 1);
	struct file *new_file = filesys_open (file_name);
	new_file->fd = 13;
    //printf("file fd = %d\n",new_file->fd );
    list_push_back (&thread_current ()->fd_table,&new_file->elem);
	return new_file->fd;
}

/* System Call: int filesize (int fd) */
static int 
filesize (void *esp)
{
	int fd = *((int *)esp+1);
}

/* System Call: int read (int fd, void *buffer, unsigned size) */
static int 
read (void *esp)
{
	int fd = *((int*)esp + 5);
	void* buffer = (void*)*((int*)esp + 6);
	unsigned size = (unsigned)*((int*)esp + 7);
}

static struct file*
get_file (int _fd)
{
	struct list_elem *e;
	struct list *list = &thread_current ()->fd_table;
  	for (e = list_begin (list); e != list_end (list); e = list_next (e))
  	{
  		struct file *f = list_entry (e, struct file, elem);
  		if (f->fd == _fd)
  		{
  			return f;
  		}
  	}
  	return NULL;
}
/* System Call: int write (int fd, const void *buffer, unsigned size) */
static int 
write (void *esp)
{
	int fd = *((int*)esp + 1);
	void* buffer = (void*)*((int*)esp + 2);
	unsigned size = (unsigned)*((int*)esp + 3);
	// //printf("before >> fd %d buffer address %p , %d\n",fd,buffer,size);
	buffer = check_addr (buffer,size);
	// //printf("after >> fd %p buffer address %p data %s , %d\n",&fd,buffer,buffer ,size);
	  // hex_dump((uintptr_t)esp, esp, 256, true);

	if (fd == STDOUT_FILENO)
	{
		putbuf(buffer,size);
		return size;
	}
	else
	{
		struct file *file = get_file (fd);
		if (!file)
			return -1;
		//printf("FILE FD = %d\n",file->fd);
		return file_write (file,buffer,size);
	}
}

/* System Call: void seek (int fd, unsigned position) */
static void 
seek (void *esp)
{
	int fd = *((int*)esp + 4);
	unsigned position = (unsigned)*((int*)esp + 5);
}

/* System Call: unsigned tell (int fd) */
static unsigned 
tell (void *esp)
{
	int fd = *((int*)esp + 1);
}

/* System Call: void close (int fd) */
static void 
close (void *esp)
{
	int fd = *((int*)esp + 1);
}

static void
syscall_handler (struct intr_frame *f) 
{
  // //printf ("system call! %p %d\n", f->esp,*(int*)f->esp);
  switch (*(int*)f->esp)
  {
  	case SYS_HALT:				/* Halt the operating system. */
  	{
  		//printf("SYS_ Halt %d\n", SYS_HALT);
  		break;
  	}
  	  	case SYS_EXIT:			/* Terminate this process. */
  	{
  		//printf("SYS_ EXIT %d\n", SYS_EXIT);
  		sys_exit (f->esp);
  		break;
  	}
  	  	case SYS_EXEC:			/* Start another process. */
  	{
  		//printf("SYS_EXEC %d\n", SYS_EXEC);
  		break;
  	}
  	  	case SYS_WAIT:			/* Wait for a child process to die. */
  	{
  		//printf("SYS_WAIT %d\n", SYS_WAIT);
  		break;
  	}
  	  	case SYS_CREATE:		/* Create a file. */
  	{
  		//printf("SYS_CREATE %d\n", SYS_CREATE);
  		f->eax = create (f->esp);
  		break;
  	}
  	  	case SYS_REMOVE:		/* Delete a file. */
  	{
  		//printf("SYS_REMOVE %d\n", SYS_REMOVE);
  		break;
  	}
  	  	case SYS_OPEN:			/* Open a file. */
  	{
  		//printf("SYS_OPEN %d\n", SYS_OPEN);
  		break;
  	}
  	  	case SYS_FILESIZE:		/* Obtain a file's size. */
  	{
  		//printf("SYS_FILESIZE %d\n", SYS_FILESIZE);
  		break;
  	}
  	  	case SYS_READ:			/* Read from a file. */
  	{
  		//printf("SYS_READ %d\n", SYS_READ);
  		break;
  	}
  	  	case SYS_WRITE:			/* Write to a file. */
  	{
  		//printf("SYS_WRITE %d\n", SYS_WRITE);
  		// //printf("%d\n", *(int*)(f->esp));
  		f->eax = write (f->esp);
  		break;
  	}
  	  	case SYS_SEEK:			/* Change position in a file. */
  	{
  		//printf("SYS_SEEK %d\n", SYS_SEEK);
  		break;
  	}
  	  	case SYS_TELL:			/* Report current position in a file. */
  	{
  		//printf("SYS_TELL %d\n", SYS_TELL);
  		break;
  	}
  	  	case SYS_CLOSE:			/* Close a file. */
  	{
  		//printf("SYS_CLOSE %d\n", SYS_CLOSE);
  		break;
  	}
  }
}

static void 
check_valid_ptr (void *vaddr)
{
  if (!is_user_vaddr(vaddr) || vaddr < LOWER_LIMITS)
    exit(-1);
}
/* checking the validation of the address */
static void*
check_addr (void *addr, unsigned size)
{
	char* local_buffer = (char *) addr;
  	for (int i = 0; i < size; i++)
    {
      check_valid_ptr((void*) local_buffer);
      local_buffer++;
    }
	void *address = pagedir_get_page (thread_current ()->pagedir , addr);
	if (address != NULL)
	  return address;
	exit(-1);
}