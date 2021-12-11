#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <sys/stat.h>

int main() {
    mkfifo("pipe1", 0644);
    mkfifo("pipe2", 0644);

    int p1 = open("p1", O_RDONLY); 
    int p2 = open("p2", O_WRONLY);

    while(1) {
        char line[4096];
        printf("Input from user interface: ");
        fgets(line, 1024, stdin);
        int i = 0;
        // process input str into all caps
        for (i = 0; i < strlen(line); i++) {
            line[i] = toupper(line[i]);
        }
        write(p1, line, sizeof(line));
        read(p2, line, 1024);

        printf("Result after processing: %s\n", line);
    }
    return 0;
}