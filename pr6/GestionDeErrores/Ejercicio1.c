// Para la gestion de errores
#include <errno.h>
#include <stdio.h>
// Para setuid
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char **argv )
{
	// int setuid(uid_t uid)
	int result = setuid(0);
	if (result == -1)
	{
		printf("error");
		return -1;
	}
	return 0;
}