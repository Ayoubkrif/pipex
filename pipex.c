#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "libft/libft.h"

void    execute_cmd(char *cmd, char **envp)
{
	char **split = ft_split(cmd, ' ');
    execve(split[0], split, envp);      // exécute la commande avec l'environnement
    perror("execve");             // en cas d'erreur
    exit(EXIT_FAILURE);
}

void    pipex(char *file1, char *cmd1, char *cmd2, char *file2, char **envp)
{
    int fd[2];
    pid_t pid1, pid2;
    int in_fd, out_fd;

    // Ouvrir le fichier d'entrée
    in_fd = open(file1, O_RDONLY);
    if (in_fd == -1)
    {
        perror("open file1");
        exit(EXIT_FAILURE);
    }
    // Ouvrir le fichier de sortie
    out_fd = open(file2, O_WRONLY + O_CREAT + O_TRUNC, 03154);
    if (out_fd == -1)
    {
        perror("open file2");
        exit(EXIT_FAILURE);
    }

    // Créer un pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork le premier processus (cmd1)
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0)  // Processus fils 1
    {
        // Rediriger l'entrée de cmd1 depuis file1
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
        
        // Rediriger la sortie de cmd1 vers le pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        
        // Exécuter cmd1 avec l'environnement
        execute_cmd(cmd1, envp);
    }

    // Fork le deuxième processus (cmd2)
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)  // Processus fils 2
    {
        // Rediriger l'entrée de cmd2 depuis le pipe
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        
        // Rediriger la sortie de cmd2 vers file2
        dup2(out_fd, STDOUT_FILENO);
        close(fd[0]);
        close(out_fd);
        
        // Exécuter cmd2 avec l'environnement
        execute_cmd(cmd2, envp);
    }

    // Fermer les descripteurs de fichiers
    close(in_fd);
    close(out_fd);
    close(fd[0]);
    close(fd[1]);

    // Attendre les processus fils
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 36);
        return (1);
    }
    pipex(argv[1], argv[2], argv[3], argv[4], envp);
    return (0);
}
