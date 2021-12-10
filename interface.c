#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h> 
#include <sys/stat.h>

int main() {
	mkfifo("pipe1", 0644);
	mkfifo("pipe2", 0644);

	int p1 = open(pipe1, O_WRONGLY);


    int f = fork();
    if(f) { 
        // close pipes in parent
        // close( fds[READ] ); 
        // close( fds2[WRITE] );

        char line[4096];
        while(1) {
            printf("Input: ");
            fgets(line, sizeof(line), stdin);
            write(fds[WRITE], line, sizeof(line));
            read(fds2[READ], line, sizeof(line));
            printf("Response: ");
            printf("%s\n", line);
        }
    } else {
        // close pipes in child
        close(fds[WRITE]);
        close(fds2[READ]);

        char line[4096];
        while(1) {
            read(fds[READ], line, sizeof(line));
            // process input str into all caps
            for (int i = 0; i < strlen(line); i++) {
                line[i] = toupper(line[i]);
            }
            write(fds2[WRITE], line, strlen(line));
        }
    }
    return 0;
}