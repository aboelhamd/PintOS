#include <syscall.h>

int main (int, char *[]);
void _start (int argc, char *argv[]);

void
_start (int argc, char *argv[]) 
{
	printf("ANA FE ENTRY\n");
  exit (main (argc, argv));
}
