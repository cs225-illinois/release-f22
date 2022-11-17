/**
 * @file hashes.cpp
 * Implementation of specialized hash functions for different key types.
 */

#include "hashes.h"

namespace hashes
{
    /**
     * Specialized hash() function for character keys.
     */
    template <>
    unsigned int hash(const char &key, int size)
    {
        // simple hash, probably could be better
        return static_cast<unsigned char>(key) % size;
    }

    /**
     * Specialized hash() function for std::string keys.
     */
    template <>
    unsigned int hash(const std::string &key, int size)
    {
        // Bernstein Hash
        unsigned int h = 0;
        for (size_t i = 0; i < key.length(); ++i)
            h = 33 * h + key[i];
        return h % size;
    }

    /**
     * Specialized hash function for character keys.
     */
    template <>
    unsigned int secondary_hash(const char &key, int size)
    {
        // another simple hash that is not too similar to the primary hash
        return static_cast<unsigned char>((key ^ 0x31) % (size - 1)) + 1;
    }

    /**
     * Specialized hash function for std::string keys.
     */
    template <>
    unsigned int secondary_hash(const std::string &key, int size)
    {
        // a different hash than above
        unsigned int h = 5381;
        for (size_t i = 0; i < key.length(); ++i)
            h = 31 * h + key[i];
        // +1 because we don't want our secondary hash to ever be 0
        return (h % (size - 1)) + 1;
    }
}
