#include <sched.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main (int argc, char **argv)
{ 
	int minp = sched_get_priority_min(SCHED_RR);
	int maxp = sched_get_priority_max(SCHED_RR);
	struct sched_param sp;

	sp.sched_priority = maxp;	

	if (argc == 2)
	{
		int argp = atoi(argv[1]);
		if(argp >= minp && argp <= maxp)
			sp.sched_priority = argp;
	}
	
	sched_setscheduler(0, SCHED_RR, &sp);

	execlp("bash", "bash", NULL);
}
