/**
 * Largest Product in a Series
 * Problem 8
 * 
 * The four adjacent digits in the 1000-digit number that have the
 * greatest product are 9 x 9 x 8 x 9 = 5832.
 * 
 * Find the thirteen adjacent digits in the 1000-digit number that
 * have the greatest product. What is the value of this product? 
 * 
 */

#include <stdio.h>
#include <stdlib.h>


long greatest_product(int length, int* number, int digits) {
    long c = 0;
    for (int i = 0; i < digits - length; ++i) {
        long s = 1;
        for (int x = 0; x < length; ++x) {
            s = s * (long)number[i + x];
        }
        if (s > c) { 
            c = s; 
        }
    }
    return c;
}


int main() {
    int* number = malloc(1025 * sizeof(int));
    int d = 0;
    FILE* fptr;
    fptr = fopen("euler_008.txt", "r");
    if (fptr == NULL) {
        printf("Unable to open file. Exiting ...\n");
        exit(1);
    }
    char fc = fgetc(fptr);
    while (fc != EOF) {
        if (fc - '0' <= 9 && fc - '0' >= 0) {
            number[d] = (int)(fc - '0');
            d++;
        }
        fc = fgetc(fptr);
    }
    // printf("\n");
    fclose(fptr);
    printf("Project Euler\nProblem #8\n\nAnswer: %ld \n", greatest_product(13, number, d));
    free(number);
    return(0);
}