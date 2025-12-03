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
        printf("R");
        add = 1;
       } else if (dir == 'L') {
        add = 0;
        printf("L");
       } else {
        perror("Invalid character");
        return 1;
       }
       char* numBuf = buf + 1;
       int num = atoi(numBuf);
       printf("%d", num);
       if (add == 0) {
        num = 0 - num;
       }

       uint32_t old_zero = timesZero;
       int64_t rawPos = pos + num;
       if (rawPos >= 100)
         timesZero += rawPos / 100;
       if (rawPos <= 0) {
        timesZero += 1 - (rawPos / 100);
        if (pos == 0) {
            timesZero -= 1;
        }
       }
       pos = (rawPos % 100 + 100) % 100; // force positive (mathematical) moduolo
       printf(" pos: %d ", pos);
       printf(" delta: %d\n", timesZero - old_zero);

    }

    printf("answer: %d\n", timesZero);
    
    fclose(file);
    return 0;
}