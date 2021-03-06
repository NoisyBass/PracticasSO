// Ficheros
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// Gestion de errores
#include <errno.h>
#include <stdio.h>

#define SIZE 256
int main (int argc, char **argv)
{
	char buffer[SIZE];	
	fd_set conjunto;
	struct timeval timeout;
	
	int tuberia = open("./tuberia", O_RDONLY | O_NONBLOCK);
	int tuberia2 = open("./tuberia2", O_RDONLY | O_NONBLOCK);

	if(tuberia == -1 || tuberia2 == -1)
	{
		perror("¡! Error open");
		return -1;
	}

	timeout.tv_sec = 2;
	timeout.tv_usec = 0;

	while(1)
	{
		FD_ZERO(&conjunto);
		FD_SET(tuberia, &conjunto);
		FD_SET(tuberia2, &conjunto);

		select((tuberia < tuberia2) ? tuberia2 + 1 : tuberia + 1, &conjunto, NULL, NULL, &timeout);

		if(FD_ISSET(tuberia, &conjunto))
		{
			int bytes = read(tuberia, buffer, SIZE);
			if(bytes < 0)
			{
				perror("¡! Error read");
				return -1;
			}
			buffer[bytes] = '\0';
			printf("Se ha escrito en la tubería 1: %s\n", buffer);
			close(tuberia);
			tuberia = open("./tuberia", O_RDONLY | O_NONBLOCK);
			if(tuberia == -1)
			{
				perror("¡! Error open");
				return -1;
			}
		}
		if(FD_ISSET(tuberia2, &conjunto))
		{
			int bytes = read(tuberia2, buffer, SIZE);
			if(bytes < 0)
			{
				perror("¡! Error read");
				return -1;
			}
			buffer[bytes] = '\0';
			printf("Se ha escrito en la tubería 2: %s\n", buffer);
			close(tuberia2);
			tuberia2 = open("./tuberia2", O_RDONLY | O_NONBLOCK);
			if(tuberia2 == -1)
			{
				perror("¡! Error open");
				return -1;
			}
		}
	}

	close(tuberia);
	close(tuberia2);
	return 0;
}
