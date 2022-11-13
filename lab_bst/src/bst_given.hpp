/**
 * @file bst_given.cpp
 * Definitions of some standard binary tree functions.
 *
 * YOU WON'T NEED TO MODIFY THIS FILE.
 *
 * In fact, you shouldn't have to read below this line. To see what the given
 * functions do, read the header file.
 */

#include "binarytree/printtree.h"

template <class K, class V>
BST<K, V>::BST()
    : root(NULL), _out(&std::cout)
{
    
}

template <class K, class V>
BST<K, V>::BST(const BST& other)
    : root(copy(other.root)), _out(&std::cout)
{

}

template <class K, class V>
BST<K, V>::~BST()
{
    clear(root);
}

template <class K, class V>
std::vector<K> BST<K,V>::getInorderTraversal() const
{
    std::vector<K> traversal;
    getInorderTraversal(root, traversal);
    return traversal;
}

template <class K, class V>
void BST<K,V>::getInorderTraversal(const Node* subRoot, std::vector<K>& traversal) const
{
    if (subRoot == NULL) {
        return;
    }
    getInorderTraversal(subRoot->left, traversal);
    traversal.push_back(subRoot->key);
    getInorderTraversal(subRoot->right, traversal);
}

template <class K, class V>
std::vector<K> BST<K,V>::getPreorderTraversal() const
{
    std::vector<K> traversal;
    getPreorderTraversal(root, traversal);
    return traversal;
}

template <class K, class V>
void BST<K,V>::getPreorderTraversal(const Node* subRoot, std::vector<K>& traversal) const
{
    if (subRoot == NULL) {
        return;
    }
    traversal.push_back(subRoot->key);
    getPreorderTraversal(subRoot->left, traversal);
    getPreorderTraversal(subRoot->right, traversal);
}

template <class K, class V>
std::vector<std::string> BST<K,V>::getFunctionOrder() const {
    return functionCalls;
}

template <class K, class V>
const BST<K, V>& BST<K, V>::operator=(const BST& rhs)
{
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}

template <class K, class V>
void BST<K, V>::clear()
{
    clear(root);
    root = NULL;
    functionCalls.clear();
}

template <class K, class V>
typename BST<K, V>::Node* BST<K, V>::copy(const Node* subRoot)
{
    if (subRoot == NULL)
        return NULL;

    // Copy this node and its children
    Node* newNode = new Node(subRoot->key, subRoot->value);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}

template <class K, class V>
void BST<K, V>::clear(Node* subRoot)
{
    if (subRoot == NULL)
        return;

    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}

// class for generic printing

template <typename Node>
class BSTNodeDescriptor
    : public GenericNodeDescriptor<BSTNodeDescriptor<Node>>
{
  public:
    BSTNodeDescriptor(const Node* root) : subRoot(root)
    {
    }
    bool isNull() const
    {
        return subRoot == NULL;
    }

    std::string key() const
    {
        std::stringstream ss;
        ss << subRoot->key;
        return ss.str();
    }

    BSTNodeDescriptor left() const
    {
        return BSTNodeDescriptor(subRoot->left);
    }
    BSTNodeDescriptor right() const
    {
        return BSTNodeDescriptor(subRoot->right);
    }

  private:
    const Node* subRoot;
};

template <class K, class V>
void BST<K, V>::printFunctionOrder(std::ostream& out) const
{
    for (int i = 0; i < (int)functionCalls.size(); i++) {
        out << functionCalls[i] << std::endl;
    }
}

template <class K, class V>
void BST<K, V>::print(std::ostream& out, bool order) const
{
    if(order)
        printFunctionOrder(out);
    printTree(BSTNodeDescriptor<Node>(root), out);
}

template <class K, class V>
int BST<K, V>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <class K, class V>
int BST<K, V>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

template <class K, class V>
void BST<K, V>::setOutput(std::ostream& newOut)
{
    _out = &newOut;
}
