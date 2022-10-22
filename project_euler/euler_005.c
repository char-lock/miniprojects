/**
 * Smallest Multiple
 * Problem 5
 * 
 * 2520 is the smallest number that can be divided by each of the
 * numbers from 1 to 10 without any remainder.
 * 
 * What is the smallest positive number that is evenly divisible by
 * all of the numbers from 1 to 20?
 * 
 */

#include <stdio.h>
#include <stdlib.h>


int gcd(int a, int b) {
    if (!a) { return b; }
    if (!b) { return a; }
    int x = (a > b) ? a : b;
    int y = (a > b) ? b : a;
    int r = x % y;
    return gcd(y, r);
}


int lcm(int max_v) {
    int a = 1;
    for (int i = 1; i < (max_v + 1); ++i) {
        a = a * (i / gcd(i, a));
    }
    return a;
}


int main() {
    printf("Project Euler\nProblem #5\n\nAnswer: %i \n", lcm(20));
    return 0;
}
