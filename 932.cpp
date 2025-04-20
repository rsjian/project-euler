// runtime: ~0.28s on Apple M3 Pro (16-inch Nov 2023) when compiling with -O3
#include <algorithm>
#include <cstdint>
#include <cstdio>

// "extremely fast, branchless, all-integer solution" for finding the number of digits in a 64 bit integer from:
// https://www.reddit.com/r/algorithms/comments/gybkk9/comment/ftba2zh/
static constexpr const int MAX_POW10 = 19;
const uint64_t pow10[MAX_POW10] = {
    10ull, 100ull, 1000ull, 10000ull, 100000ull, 1000000ull, 10000000ull,
    100000000ull, 1000000000ull, 10000000000ull, 100000000000ull,
    1000000000000ull, 10000000000000ull, 100000000000000ull,
    1000000000000000ull, 10000000000000000ull, 100000000000000000ull,
    1000000000000000000ull, 10000000000000000000ull
};
unsigned int uint64_base10_digits(const uint64_t n)
{ 
    unsigned int b = -(n > 0) & (63 - __builtin_clzll(n));
    unsigned int a = (b * 77) / 256;
    return 1 + a + (n >= pow10[a]);
}

uint64_t solve()
{
    uint64_t ans = 0;
    // skip n = 1 
    uint64_t n2 = 4; // n squared
    for (uint64_t n = 2; n < 100000000ull; ++n) { 
        int num_digits_n2 = uint64_base10_digits(n2);
        int mid = num_digits_n2 / 2; // a + b should be around 1e(num_digits_n2 / 2) in order for it to square to n2
        static constexpr const int range = 1; // around meaning +-1 factor of 10
        for (int i = std::max(mid - range, 0); i < std::min(mid + range, MAX_POW10); ++i) {
            // hope that the compiler optimizes to something like std::lldiv
            uint64_t a = n2 / pow10[i];
            uint64_t b = n2 % pow10[i];
            int num_digits_b = i + 1;
            // for some reason the following logically equivalent branch is ~50 ms slower
            // if (n == a + b && 10*b >= pow10[i]) {
            if (n == a + b && 100*b >= pow10[num_digits_b]) { // second condition handles candidates that don't work because of leading zeros
                printf("\t found %lld==(%lld+%lld)**2\n", n2, a, b);
                ans += n2;
                break;
            }
        }
        n2 += 2*n + 1; // manual strength reduction
    }
    return ans;
}

int main()
{
    printf("ans: %lld\n", solve());
    return 0;
}
