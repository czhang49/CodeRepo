#include <algorithm>
#include <array>
#include "primes.h"

namespace cs225
{
uint64_t next_prime(uint64_t num)
{
    // list of primes for resizing. "borrowed" from boost::unordered.
    static uint64_t primes[] = {
        17ul,         29ul,         37ul,        53ul,        67ul,
        79ul,         97ul,         131ul,       193ul,       257ul,
        389ul,        521ul,        769ul,       1031ul,      1543ul,
        2053ul,       3079ul,       6151ul,      12289ul,     24593ul,
        49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
        1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
        50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
        1610612741ul, 3221225473ul, 4294967291ul};

    auto prime = std::upper_bound(std::begin(primes), std::end(primes), num);
    if (prime == std::end(primes))
        --prime;
    return *prime;
}
}
