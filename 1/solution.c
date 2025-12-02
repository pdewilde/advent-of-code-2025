#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BUF_LENGTH 64 // we are just expecting a letter and an integer

int main(int argc, char **argv) {
    char* filename = "input.txt";
    if (argc == 2) {
        filename = argv[1];
    }
    FILE *file = fopen(filename, "r'");
    if (file == NULL) {
        perror("Could not open file");
        return 1;
    }
    char buf[BUF_LENGTH];
    int64_t pos = 50;
    uint32_t timesZero = 0;
    while (fgets(buf, BUF_LENGTH, file) != NULL) {
       char dir = buf[0];
       char add;
       if (dir == 'R') {
        add = 1;
       } else if (dir == 'L') {
        add = 0;
       } else {
        perror("Invalid character");
        return 1;
       }
       char* numBuf = buf + 1;
       int num = atoi(numBuf);
       if (add == 0) {
        num = 0 - num;
       }
       pos = (pos + num) % 100;
       if (pos == 0) {
        timesZero++;
       }
    }

    printf("answer: %d\n", timesZero);
    
    fclose(file);
    return 0;
}