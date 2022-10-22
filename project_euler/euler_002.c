/** 
 * Even Fibonacci Numbers
 * Problem 2
 * 
 * Each new term in the Fibonacci sequence is generated by adding the
 * previous two terms. By starting with 1 and 2, the first 10 terms
 * will be:
 * 
 * 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89
 * 
 * By considering the terms in the Fibonacci sequence whose values do
 * not exceed four million, find the sum of the even valued terms.
 * 
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Returns the nth value of the Fibonacci sequence.
int fibonacci(int n) {
    // A closed-form expression for finding Fibonacci numbers
    // and using phi is:
    // PHI^n - (1 - PHI)^n / sqrt(5)
    double PHI = (1 + sqrt(5)) / 2;
    double f = pow(PHI, n) - pow(1 - PHI, n);
    f = f / sqrt(5);
    return (int)round(f);
}

// Returns the closest Fibonacci position for a given integer.
int get_n(int f) {
    // If the formula for calculating Fibonacci numbers is:
    // F = PHI^n - (1 - PHI)^n / sqrt(5)
    // sqrt(5) * f = PHI^N - (1 - PHI)^n
    //
    // We can prove that (1 - PHI)^n will always equal (1 - PHI)
    // (1 - PHI) ^ 1 = 1 - PHI
    // (1 - PHI) ^ 2 = (1 - PHI) * (1 - PHI) = (1 - PHI - PHI + PHI) = 1 - PHI
    // (1 - PHI) ^ 3 = 1 - PHI * (1 - PHI) ^ 2 = 1 - PHI * 1 - PHI = 1 - PHI
    // And so on.
    //
    // sqrt(5) * f = PHI ^ n - (1 - PHI)
    // sqrt(5)f + (1 - PHI) = PHI ^ n
    // 
    // We know that logarithms can be used to find the value of exponents:
    // logb(a) = c for b^c = a
    // 
    // log PHI (sqrt(5)f + (1 - PHI)) = n
    //
    if (f < 3) { return f; }
    double PHI = (1 + sqrt(5)) / 2;
    double n = log((sqrt(5) * f) + (1 - PHI)) / log(PHI);
    return (int)round(n);
}


long f_sum(int max_val) {
    // Find the highest possible n we could use with the given maximum.
    int max_f = get_n(max_val) + 1;
    // Ensure that the max chosen doesn't exceed our limit.
    while (fibonacci(max_f - 1) > max_val) {
        max_f--;
    }
    // Setup where we'll store our sum.
    long s = 0;
    // Iterate up to our chosen n and add the even fibonacci numbers.
    for (int i = 0; i < max_f; ++i) {
        int f = fibonacci(i);
        if (f % 2 == 0) {
            s += f;
        }
    }
    return s;
}


int main() {
    long s = f_sum(3999999);
    printf("Project Euler\nProblem #2\n\nAnswer: %ld \n", s);
    return 0;
}