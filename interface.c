#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    // create and open pipes
    mkfifo("pipe1", 0644);
	mkfifo("pipe2", 0644);
    int p1 = open("p1", O_WRONLY);
    int p2 = open("p2", O_RDONLY);

    char line[4096];
    // constantly prompts user for input
    while(1) {
        // send input to worker program
        printf("Input: ");
        fgets(line, sizeof(line), stdin);
		sscanf(line, "%s", line);
        write(p1, line, sizeof(line));
        // wait and receive response
        read(p2, line, sizeof(line));
        // displays the response to the user
        printf("Response: %s\n\n", line);
    }
    return 0;
}