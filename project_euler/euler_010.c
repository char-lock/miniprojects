/**
 * Summation of Primes
 * Problem 10
 * 
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 * 
 * Find the sum of all the primes below two million.
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


long get_prime_sum_under(int n) {
    long* primes = malloc(4000000 * sizeof(long));
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    primes[4] = 11;
    primes[5] = 13;
    int p_sz = 6;
    long s = 41;
    while (primes[p_sz - 1] < n) {
        long p = next_prime(primes, p_sz);
        if (p < n) {
            primes[p_sz] = p;
            s += p;
        } else {
            break;
        }
        p_sz++;
    }
    return s;
}


int main() {
    printf("Project Euler\nProblem #10\n\nAnswer: %ld \n", get_prime_sum_under(2000000));
    return 0;
}