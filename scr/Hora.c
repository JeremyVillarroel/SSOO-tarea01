#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void trataSenhal (int);

int Hora() {
	
	pid_t idProceso;
	idProceso = fork();
	
	if (idProceso == -1) {
		perror ("No se puede lanzar proceso");
		return(-1);
	}
    
	if (idProceso == 0) {
		printf ("Listo para recibir la señal SIGUSR1.\n");
		while (1) {
			//pause ();
		}
	}
	
	if (idProceso > 0) {
		signal (SIGUSR1, trataSenhal);
		while (1) {
			sleep (1);
			kill (idProceso, SIGUSR1);
		}
	}
}

void trataSenhal (int numeroSenhal) {
	
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char output[128];
	strftime(output,128,"%a %b  %d %H:%M:%S %Z %Y",tlocal);		
	printf ("Señal SIGUSR1 recibida: %s\n", output);
	exit(-1);
}
