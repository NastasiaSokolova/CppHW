#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

#include "numbers.dat"

const int N= 100000;

void
count_pref(int * pref, int size_pref, int * prime_nums)
{
    for (int i = 0; i < size_pref; ++i) {
        if (i == 0 && !prime_nums[Data[i]]) {
            pref[i] = 1;
        } else if (!prime_nums[Data[i]]) {
            pref[i] = pref[i - 1] + 1;
        } else {
            pref[i] = pref[i - 1];
        }
    }
}

void
count_primes(int * prime_nums, int size_prime_nums)
{
    prime_nums[1] = 1;
    prime_nums[0] = 1;
    for (int i = 2; i * i < size_prime_nums; ++i) {
        if (!prime_nums[i]) {
            for (int j = i * i; j < size_prime_nums; j += i) {
                prime_nums[j] = 1;
            }
        }
    }
}


int
counting_ans(int first_v, int second_v , int first_point, int sec_point, int * pref, int size_pref)
{
    if (first_point < 0 || sec_point < 0
        || first_point >= size_pref || sec_point >= size_pref) {
        return 0;
    }
    if (first_point <= sec_point
        && Data[first_point] == first_v && Data[sec_point] == second_v) {
        if (first_point > 0) {
            return pref[sec_point] - pref[first_point - 1];
        } else {
            return pref[sec_point];
        }
    } else {
        return 0;
    }
}

int main(int argc, const char * argv[]) {
    if (argc % 2 != 1 || argc == 1) {
        return -1;
    }
    
    
    int *prime_nums = new int[N]();
    count_primes(prime_nums, N);
    
    int *pref = new int[Size]();
    count_pref(pref, Size, prime_nums);
    
    for (int i = 1; i < argc; i += 2) {
        int first_v = std::atoi(argv[i]);
        int second_v = std::atoi(argv[i + 1]);
        
        int first_point = std::lower_bound(Data, Data + Size, first_v) - Data;
        int sec_point = std::upper_bound(Data, Data + Size, second_v) - Data - 1;
        int ans = counting_ans(first_point, sec_point, pref, Size, first_v, second_v);
        printf("%d\n", ans);
    }
    delete[] prime_nums;
    delete[] pref;
    return 0;
}
