#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to execute a single command
void execute_command(char *command)
{
    pid_t pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execlp(command, command, NULL);
        fprintf(stderr, "Failed to execute command: %s\n", command);
        exit(1);
    } else {
        // Parent process
        wait(NULL);
    }
}

int main()
{
    char *commands[] = {"ls", "cat", "ls", NULL};
    int i = 0;
    int pipefd[2];
    pid_t pid;
    
    while (commands[i + 1] != NULL) {
        if (pipe(pipefd) < 0) {
            fprintf(stderr, "Pipe creation failed.\n");
            exit(1);
        }
        
        pid = fork();

if (pid == 0) {
            // Child process
            close(pipefd[0]); // Close unused read end
            
            if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
                fprintf(stderr, "Duplication of file descriptor failed.\n");
                exit(1);
            }
            
            execute_command(commands[i]);
            exit(0);
        } else {
            // Parent process
            close(pipefd[1]); // Close unused write end
            
            if (dup2(pipefd[0], STDIN_FILENO) < 0) {
                fprintf(stderr, "Duplication of file descriptor failed.\n");
                exit(1);
            }
            
            i++;
        }
    }
    
    // Execute the last command
    execute_command(commands[i]);
    
    return 0;
}