#include <unistd.h>
#include <stdio.h>

int main( int argc, char **argv )
{
	printf("-> Número máximo de enlaces: %ld\n", pathconf("/", _PC_LINK_MAX));

	printf("-> Tamaño máximo de una ruta: %ld\n", pathconf("/", _PC_PATH_MAX));

	printf("-> Tamaño máximo del nombre de un fichero: %ld\n", pathconf("/", _PC_NAME_MAX));

	return 0;
}
