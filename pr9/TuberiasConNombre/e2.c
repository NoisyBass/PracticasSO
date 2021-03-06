// Ficheros
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// Gestion de errores
#include <errno.h>
#include <stdio.h>
// strlen
#include <string.h>

int main (int argc, char **argv)
{
	if(argc != 2)
	{
		printf("¡! ERROR: número inválido de argumentos\n");
		return -1;
	}

	int tuberia = open("./tuberia", O_WRONLY);

	if(tuberia == -1)
	{
		perror("¡! Error open");
		return -1;
	}
	
	if(write(tuberia, strcat(argv[1], "\n"), strlen(argv[1]) + 1) == -1)
	{
		perror("¡! Error write");
		return -1;
	}

	close(tuberia);
	return 0;
}
