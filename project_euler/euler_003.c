/**
 * Largest Prime Factor
 * Problem 3
 * 
 * The prime factors of 13195 are 5, 7, 13, and 29.
 * 
 * What is the largest prime factor of the number 600851475143?
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>


int smallest_prime_factor(long n) {
    if (n <= 2) { return n; }
    for (int i = 2; i < sqrt(n); ++i) {
        if (n % i == 0) {
            return i;
        }
    }
    return n;
}



int main() {
    long n = 600851475143;
    while (1) {
        int p = smallest_prime_factor(n);
        if (p < n) {
            n /= p; 
        } else {
            break;
        }
    }
    printf("Project Euler\nProblem #3\n\nAnswer: %ld \n", n);
    return 0;
}