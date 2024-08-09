#ifndef system_monitor_h
#define system_monitor_h
#include <sys/types.h>
// Define constants
#define NUM_CHILD_PROCESSES 3
#define BUFFER_SIZE 256
// Function prototypes
void start_monitoring();
void handle_child_process(int child_index, int pipe_fd);
#endif // SYSTEM_MONITOR_H
