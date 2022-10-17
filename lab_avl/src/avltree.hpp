/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int balance = (subtree == NULL)? 0 : (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left));
    int balance_right = (subtree->right == NULL)? 0 : (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left));
    int balance_left = (subtree->left == NULL)? 0 : (heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left));

    if (balance == 2) {
        if (balance_right == 1) {
            rotateLeft(subtree);
        } else if (balance_right == -1) {
            rotateRightLeft(subtree);
        }
    } else if (balance == -2) {
        if (balance_left == -1) {
            rotateRight(subtree);
        } else if (balance_left == 1) {
            rotateLeftRight(subtree);
        }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } else if (key >= subtree->key) {
        insert(subtree->right, key, value);
    } else {
        insert(subtree->left, key, value);
    }
    rebalance(subtree);
} 

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {

        remove(subtree->left, key);

    } else if (key > subtree->key) {

        remove(subtree->right, key);

    } else {

        if (subtree->left == NULL && subtree->right == NULL) {

           delete subtree;
           subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
            while(temp->right != NULL) {
                temp = temp->right;   
            }
            swap(temp, subtree);
            remove(subtree->left, key);
            rebalance(temp);
            
        } else {
            /* one-child remove */
            // your code here
            Node* temp;
            if (subtree->left != NULL) {
                temp = subtree->left;
            } else {
                temp = subtree->right;
            }
            delete subtree;
            subtree = temp;
        }
        // your code here
    }
    rebalance(subtree);
}
