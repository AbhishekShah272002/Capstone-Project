#include "system_monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
void handle_child_process(int child_index, int pipe_fd) {
 // Redirect standard output to the pipe
 close(pipe_fd);
 dup2(pipe_fd, STDOUT_FILENO);
 close(pipe_fd);
 // Perform the task; replace with your specific task
 execlp("ls", "ls", NULL);
 
 // If execlp fails
 perror("execlp");
 exit(EXIT_FAILURE);
}
