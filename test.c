#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int filedesc = open("output.txt", O_WRONLY | O_CREAT, 0644);
    if (filedesc < 0) return -1;

    int newfd = dup(filedesc); // Duplicate file descriptor

    if (newfd < 0) return -1;

    close(STDOUT_FILENO);      // Close standard output
    dup2(newfd, STDOUT_FILENO); // Redirect standard output to newfd

    printf("This will be written to output.txt\n");

    close(filedesc);

    return 0;
}
