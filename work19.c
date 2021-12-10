#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define READ 0
#define WRITE 1

int main() {
    int fds[2];
    int fds2[2];
    pipe(fds);
    pipe(fds2);

    int f = fork();
    if(f) { 
        // close pipes in parent
        close( fds[READ] ); 
        close( fds2[WRITE] );

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