#include <unistd.h>
#include <sys/auxv.h>

int main(int argc, char **argv) {
      syscall(543);
      syscall(666, getauxval(AT_SYSINFO_EHDR) - sysconf(_SC_PAGESIZE));
      syscall(777);
 
 	char *args[] = {"./main", NULL};	
	execvp(args[0], args);
}
