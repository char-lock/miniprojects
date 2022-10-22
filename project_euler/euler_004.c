/**
 * Largest Palindrome Product
 * Problem 4
 * 
 * A palindromic number reads the same both ways. The largest palindrome
 * made from the product of two 2-digit numbers is 9009 = 91 * 99.
 * 
 * Find the largest palindrome made from the product of two 3-digit numbers.
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/** Returns the digit of a given integer in a given position. */
int get_digit_by_position(int x, int pos) {
    int y = x;
    int p = 1;
    while (p <= pos) {
        y = y / 10;
        p++;
    }
    return (y % 10);
}


/** Returns the digit count of a given integer. */
int get_digits(int x) {
    int y = x;
    int c = 0;
    while (y > 0) {
        y = y / 10;
        c++;
    }
    return c;
}


bool is_palindrome(int x) {
    int d = get_digits(x);
    // printf("%i \n", d);
    int h = (d % 2 == 0) ? (floor(d / 2) + 2) : floor(d / 2) + 1;
    for (int i = 0; i < h; ++i) {
        int l = get_digit_by_position(x, i);
        int r = get_digit_by_position(x, d - i - 1);
        if (l != r) {
            return false;
        }
    }
    return true;
}


int find_largest_palindrome() {
    for (int x = 999; x > 899; --x) {
        for (int y = 999; y > 899; --y) {
            int v = x * y;
            if (is_palindrome(v)) {
                return v;
            }
        }
    }
    return 0;
}


int main() {
    printf("Project Euler\nProblem #4\n\nAnswer: %i \n", find_largest_palindrome());
    return 0;
}