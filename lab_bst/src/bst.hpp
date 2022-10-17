/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
  return find(root, key)->value;
}
template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == NULL || subtree->key == key) {
        return subtree;
    }
    if (subtree->key < key) {
        return find(subtree->right, key);
    }
    return find(subtree->left, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    BST<K, V>::insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    BST<K,V>::Node* insertionNode = find(subtree, key);
    Node* toInsert = new Node();
    if (insertionNode->key > key) {
        insertionNode->left = toInsert;
    } else {
        insertionNode->right = toInsert;
    }
    

}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    V temp;
    temp = first->value;
    first->value = second->value;
    second->value = temp;
    
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    BST<K,V>::remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    BST<K, V>::Node* toRemove = find(subtree, key);
    delete toRemove;
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K,V>* tree= new BST<K, V>();
    for (size_t i = 0; i < inList.size(); i++) {
        tree->insert(inList.at(i).first, inList.at(i).second);
    }
    return *tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> mine;
    return mine;
}
