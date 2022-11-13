/**
 * @file binarytree_given.hpp
 * Definitions of some standard binary tree functions.
 *
 * YOU WON'T NEED TO MODIFY THIS FILE.
 *
 * In fact, you shouldn't have to read below this line. To see what the given
 * functions do, read the header file.
 */

#include "binarytree/printtree.h"

template <typename T>
BinaryTree<T>::BinaryTree()
    : root(NULL)
{ /* nothing */
}

template <typename T>
BinaryTree<T>::BinaryTree(typename BinaryTree<T>::Node* heapNode)
    : root(heapNode)
{ /* nothing */
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other)
    : root(copy(other.root))
{ /* nothing */
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    clear(root);
}

template <typename T>
const BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& rhs)
{
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}

template <typename T>
void BinaryTree<T>::clear()
{
    clear(root);
    root = NULL;
}

/**
 * @return The root of the binary tree.
 */
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::getRoot() const
{
    return root;
}

// This is a template so we can declare it outside of the .h file - we don't
// need to actually see the BinaryTree<T>::Node class
template <typename Node>
class BinaryTreeNodeDescriptor
    : public GenericNodeDescriptor<BinaryTreeNodeDescriptor<Node> >
{
  public:
    BinaryTreeNodeDescriptor(const Node* node_ptr) : node(node_ptr)
    {
    }
    bool isNull() const
    {
        return node == NULL;
    }
    std::string key() const
    {
        std::stringstream ss;
        ss << node->elem;
        return ss.str();
    }
    BinaryTreeNodeDescriptor left() const
    {
        return BinaryTreeNodeDescriptor(node->left);
    }
    BinaryTreeNodeDescriptor right() const
    {
        return BinaryTreeNodeDescriptor(node->right);
    }

  private:
    const Node* node;
};

template <typename T>
void BinaryTree<T>::print() const
{
    printTree(BinaryTreeNodeDescriptor<Node>(root));
}

template <typename T>
void BinaryTree<T>::insert(const T& elem)
{
    insert(root, elem);
}


template <typename T>
void BinaryTree<T>::insert(Node*& node, const T& elem)
{
    // If we're at a NULL pointer, we can put our element here
    if (node == NULL) {
        node = new Node(elem);
    } else if (elem < node->elem) {
        insert(node->left, elem);
    } else {
        insert(node->right, elem);
    }
}

template <typename T>
void BinaryTree<T>::insertRandom(const T& elem, std::mt19937& rng)
{
    insertRandom(root, elem, rng);
}

template <typename T>
void BinaryTree<T>::insertRandom(Node*& node, const T& elem, std::mt19937& rng)
{
    if (node == NULL) {
        node = new Node(elem);
    } else if (rng() % 2 == 0) {
        insertRandom(node->left, elem, rng);
    } else {
        insertRandom(node->right, elem, rng);
    }
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copy(const Node* subRoot)
{
    if (subRoot == NULL)
        return NULL;

    // Copy this node and it's children
    Node* newNode = new Node(subRoot->elem);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}

template <typename T>
void BinaryTree<T>::clear(BinaryTree::Node* subRoot)
{
    if (subRoot == NULL)
        return;

    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}

template <typename T>
void BinaryTree<T>::inOrder(std::vector<T>& treeVector){
    inOrder(root, treeVector);
}

template <typename T>
void BinaryTree<T>::inOrder(BinaryTree::Node* subRoot, std::vector<T>& treeVector){
    if(subRoot != NULL){
      inOrder(subRoot->left, treeVector);
      treeVector.push_back(subRoot->elem);
      inOrder(subRoot->right, treeVector);
    }
}
