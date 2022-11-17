/**
 * @file hashes.h
 * Definition of a namespace containing a templatized hash function.
 */

#pragma once

#include <string>

/**
 * A collection of templated hash functions.
 */
namespace hashes
{
    /**
     * Computes the hash code of a given key (templated), and returns it modulo
     * size for use in HashTable applications. This function **must** be
     * specialized in order for one of SCHashTable, LPHashTable, or DHHashTable
     * to contain keys of the specialized type.
     *
     * @param key The key to be hashed.
     * @param size What to modulo the hashcode by.
     * @return The hashcode, modulo size for use as a HashTable index.
     */
    template <class K>
    unsigned int hash(const K &key, int size);

    /**
     * Computes the secondary hash code of a given key (templated), and returns
     * it modulo size for use in HashTable applications. This function **must**
     * be specialized in order for DHHashTable to contain keys of the
     * specialized type.
     *
     * This function will never return 0.
     *
     * @param key The key to be hashed.
     * @param size What to modulo the hashcode by.
     * @return The hashcode, modulo size for use as a HashTable index.
     */
    template <class K>
    unsigned int secondary_hash(const K &key, int size);
}
