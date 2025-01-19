#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1)
	{
        perror("pipe");
        exit(1);
    }
    if (fork() == 0)
	{
        close(pipefd[0]); // Ferme l'extrémité lecture
        dup2(pipefd[1], STDOUT_FILENO); // Redirige stdout vers le pipe
        close(pipefd[1]); // Ferme l'extrémité inutilisée
        execlp("ls", "ls", NULL); // Exécute "ls"
        perror("execlp");
        exit(1);
    }
	else
	{ // Processus parent
        close(pipefd[1]); // Ferme l'extrémité écriture
        dup2(pipefd[0], STDIN_FILENO); // Redirige stdin vers le pipe
        close(pipefd[0]); // Ferme l'extrémité inutilisée
        execlp("grep", "grep", ".c", NULL); // Exécute "grep .c"
        perror("execlp");
        exit(1);
    }
}

