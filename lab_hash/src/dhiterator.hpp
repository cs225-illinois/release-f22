/**
 * @file lpiterator.cpp
 * Implementation of the DHIteratorImpl implementation class.
 */

template <class K, class V>
DHHashTable<K, V>::DHIteratorImpl::DHIteratorImpl(const DHHashTable<K, V>& ht,
                                                  size_t j)
    : bucket(j), table(ht)
{
    if (bucket < table.size && table.table[bucket] == NULL)
        operator++();
}

template <class K, class V>
void DHHashTable<K, V>::DHIteratorImpl::operator++()
{
    while (++bucket < table.size && table.table[bucket] == NULL)
        ;
}

template <class K, class V>
bool DHHashTable<K, V>::DHIteratorImpl::
operator==(const HTIteratorImpl& rhs) const
{
    const HTIteratorImpl* tmp = &rhs;
    const DHIteratorImpl* other = dynamic_cast<const DHIteratorImpl*>(tmp);
    if (other == NULL)
        return false;
    else
        return *other == *this;
}

template <class K, class V>
bool DHHashTable<K, V>::DHIteratorImpl::
operator==(const DHIteratorImpl& rhs) const
{
    return &table == &rhs.table && bucket == rhs.bucket;
}

template <class K, class V>
std::pair<K, V> const& DHHashTable<K, V>::DHIteratorImpl::operator*()
{
    return *(table.table[bucket]);
}

template <class K, class V>
typename HashTable<K, V>::HTIteratorImpl*
DHHashTable<K, V>::DHIteratorImpl::clone() const
{
    return new DHIteratorImpl(table, bucket);
}
