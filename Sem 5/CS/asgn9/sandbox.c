#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <seccomp.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

// Define the folder where file operations are allowed
#define ALLOWED_FOLDER "/home/vbuntu/Desktop/Vatsal/college/Sem 5/CS/asgn9/sandbox/"
// Set a timeout for program execution in seconds
#define TIMEOUT_SECONDS 5
// Maximum heap size allowed (10 MB)
#define MAX_HEAP_SIZE (10 * 1024 * 1024) // 10 MB
// Maximum length for file paths
#define PATH_MAX 100000

// Signal handler for timeout
void timeout_handler(int signum) {
    printf("Execution Timeout. Terminating sandbox.\n");
    exit(1);
}

// Function to restrict heap size
void restrict_heap_size() {
    struct rlimit limit;
    // Set soft and hard limits for heap allocation to 10 MB
    limit.rlim_cur = MAX_HEAP_SIZE; // Soft limit
    limit.rlim_max = MAX_HEAP_SIZE; // Hard limit

    // Apply the limit using setrlimit system call
    if (setrlimit(RLIMIT_AS, &limit) != 0) {
        perror("Failed to restrict heap size");
        exit(1);
    }
}

// Function to check if the file path is inside the allowed folder
int is_path_allowed(const char *path) {
    char real_path[PATH_MAX];
    // Resolve the real absolute path of the file, handling any symbolic links
    realpath(path, real_path);

    // Compare the beginning of the resolved path with the allowed folder path
    if (strncmp(real_path, ALLOWED_FOLDER, strlen(ALLOWED_FOLDER)) == 0) {
        return 1;
    }
    return 0; 
}

void write_to_file(const char *folder, const char *filename, const char *data) {
    char filepath[PATH_MAX];
    // Construct the full file path by combining folder and filename
    snprintf(filepath, sizeof(filepath), "%s/%s", folder, filename);

    // Check if the constructed file path is allowed
    if (!is_path_allowed(filepath)) {
        fprintf(stderr, "Permission Denied: Write operation outside of sandbox folder!\n");
        exit(1);
    }

    // Open the file for writing
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        // If opening the file fails, print an error message and exit
        perror("Failed to open file");
        exit(1);
    }
    
    fprintf(file, "%s", data);
    fclose(file);
    printf("File written successfully to %s\n", filepath);
}

int main() {
    // Set up the timeout by associating SIGALRM with the timeout handler function
    signal(SIGALRM, timeout_handler);
    // Start the countdown for the timeout (5 seconds)
    alarm(TIMEOUT_SECONDS);

    restrict_heap_size();

    // Sandbox task: Write to a file in the allowed folder
    write_to_file(ALLOWED_FOLDER, "sandboxed_file.txt", "Data inside the sandbox");

    // Simulate a long-running task that exceeds the timeout
    sleep(10); // This will be interrupted by the timeout after 5 seconds

    return 0;
}
