#include "system_monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
void start_monitoring() {
 int pipe_fd[NUM_CHILD_PROCESSES][2];
 pid_t child_pid;
 // Create pipes for IPC
 for (int i = 0; i < NUM_CHILD_PROCESSES; i++) {
 if (pipe(pipe_fd[i]) == -1) {
 perror("pipe");
 exit(EXIT_FAILURE);
 }
 }
 // Create child processes
 for (int i = 0; i < NUM_CHILD_PROCESSES; i++) {
 if ((child_pid = fork()) == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 } else if (child_pid == 0) {
 // Child process
 close(pipe_fd[i][0]); // Close read end of the pipe
 handle_child_process(i, pipe_fd[i][1]);
 exit(EXIT_SUCCESS);
 } else {
 // Parent process
 close(pipe_fd[i][1]); // Close write end of the pipe
 }
 }
 // Parent process: read from pipes
 char buffer[BUFFER_SIZE];
 for (int i = 0; i < NUM_CHILD_PROCESSES; i++) {
 ssize_t bytes_read;
 printf("Output from child process %d:\n", i);
 while ((bytes_read = read(pipe_fd[i][0], buffer, sizeof(buffer) - 1)) 
 > 0) {
 buffer[bytes_read] = '\0'; // Null-terminate string
 printf("%s", buffer);
 }
 close(pipe_fd[i][0]);
 }
 // Wait for all child processes to complete
 for (int i = 0; i < NUM_CHILD_PROCESSES; i++) {
 wait(NULL);
 }
}
