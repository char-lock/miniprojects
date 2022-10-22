/**
 * 10001st Prime
 * Problem 7
 * 
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we
 * can see that the 6th prime is 13.
 * 
 * What is the 10001st prime number?
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_prime(long* primes, int primes_sz, int value) {
    if (value < 2) { return false; }
    for (int i = 0; i < primes_sz; ++i) {
        if (value % primes[i] == 0) {
            return false;
        }
    }
    return true;
}


long next_prime(long* primes, int primes_sz) {
    int v = primes[primes_sz - 1] + 1;
    while (!is_prime(primes, primes_sz, v)) {
        v++;
    }
    return v;
}


long get_nth_prime(int n) {
    long* primes = malloc(10002 * sizeof(long));
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    primes[4] = 11;
    primes[5] = 13;
    int p_sz = 6;
    while (p_sz < n) {
        long p = next_prime(primes, p_sz);
        primes[p_sz] = p;
        p_sz++;
    }
    return primes[n - 1];
}


int main() {
    printf("Project Euler\nProblem #7\n\nAnswer: %ld \n", get_nth_prime(10001));
    return 0;
}