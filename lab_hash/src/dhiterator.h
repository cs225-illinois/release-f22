/**
 * @file lpiterator.h
 * Definition of the DHHashTable iterator implementation.
 */

#pragma once

/**
 * A polymorphic iterator implementation class for DHHashTables.
 */
template <class K, class V>
class DHHashTable<K, V>::DHIteratorImpl : public HashTable<K, V>::HTIteratorImpl
{
public:
  /**
   * We friend the DHHashTable class so that it may construct
   * iterator implementations with our private constructor.
   */
  friend class DHHashTable<K, V>;

  // for simplicity
  typedef typename HashTable<K, V>::HTIteratorImpl HTIteratorImpl;

  // inherited functions
  virtual void operator++();
  virtual bool operator==(const HTIteratorImpl &other) const;
  virtual const std::pair<K, V> &operator*();
  virtual HTIteratorImpl *clone() const;

  /**
   * Equality operator that compares two DHIteratorImpl. Used by the
   * generic operator==() for HTIteratorImpl after a successful
   * dynamic_cast.
   *
   * @param other The DHIteratorImpl to compare against.
   * @return Whether the two implementations are the same.
   */
  virtual bool operator==(const DHIteratorImpl &other) const;

private:
  /**
   * The current bucket we are at in the DHHashTable's internal
   * array.
   */
  size_t bucket;

  /**
   * Reference to the DHHashTable we are iterating over.
   */
  const DHHashTable<K, V> &table;

  /**
   * Private constructor: takes a DHHashTable to iterate over and a
   * bucket index to start at.
   *
   * @param ht The DHHashTable this iterator is going to be for.
   * @param i The bucket to start at.
   */
  DHIteratorImpl(const DHHashTable &ht, size_t i);
};
/** @endcond */
#include "dhiterator.hpp"
