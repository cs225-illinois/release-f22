/**
 * @file dhhashtable.h
 * Definition of a Double Hashing Hash Table.
 */
#pragma once

#include "hashtable.h"

/**
 * A HashTable implementation that uses double hashing as a collision
 * resolution strategy.
 */

template <class K, class V>
class DHHashTable : public HashTable<K, V>
{
private:
  // so we can refer to hash, elems, and size directly, and use the
  // makeIterator function without having to scope it.
  using HashTable<K, V>::elems;
  using HashTable<K, V>::size;
  using HashTable<K, V>::makeIterator;
  using HashTable<K, V>::findPrime;
  using HashTable<K, V>::shouldResize;

  // implementation for our iterator, you don't need to worry about
  // this
  class DHIteratorImpl;

public:
  // we use HashTable's iterators here
  typedef typename HashTable<K, V>::iterator iterator;

  /**
   * Constructs a DHHashTable of the given size.
   *
   * @param tsize The desired number of starting cells in the
   *  DHHashTable.
   */
  DHHashTable(size_t tsize);

  /**
   * Destructor for the DHHashTable. We use dynamic memory, and thus
   * require the big three.
   */
  virtual ~DHHashTable();

  /**
   * Assignment operator.
   *
   * @param rhs The DHHashTable we want to assign into the current
   *  one.
   * @return A const reference to the current DHHashTable.
   */
  const DHHashTable<K, V> &operator=(const DHHashTable<K, V> &rhs);

  /**
   * Copy constructor.
   *
   * @param other The DHHashTable to be copied.
   */
  DHHashTable(const DHHashTable<K, V> &other);

  // functions inherited from HashTable
  virtual void insert(const K &key, const V &value);
  virtual void remove(const K &key);
  virtual V find(const K &key) const;
  virtual bool keyExists(const K &key) const;
  virtual void clear();
  virtual V &operator[](const K &key);

  iterator begin() const
  {
    return makeIterator(new DHIteratorImpl(*this, 0));
  }

  iterator end() const
  {
    return makeIterator(new DHIteratorImpl(*this, size));
  }

private:
  /**
   * Storage for our DHHashTable.
   *
   * With linear probing, we only need the array, not buckets for each
   * array index. Note that we use an array of pointers to pairs in this
   * case since the check for an "empty" slot is simply a check against
   * NULL in that cell.
   */
  std::pair<K, V> **table;

  /**
   * Flags for whether or not to probe forward when looking at a
   * particular cell in the table.
   *
   * This is a dynamic array of booleans that represents if a slot is
   * (or previously was) occupied. This allows us determine whether
   * or not we need to probe forward to look for our key.
   */
  bool *should_probe;

  /**
   * Helper function to determine the index where a given key lies in
   * the DHHashTable. If the key does not exist in the table, it will
   * return -1.
   *
   * @param key The key to look for.
   * @return The index of this key, or -1 if it was not found.
   */
  int findIndex(const K &key) const;

  // inherited from HashTable
  virtual void resizeTable();

  void destroy();

  void copy(const DHHashTable &other);
};

#include "dhiterator.h"
#include "dhhashtable.hpp"
