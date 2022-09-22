/**
 * @file binarytree.h
 * Declaraction of the BinaryTree class. You will probably need to modify this
 *  file to add helper functions.
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <random>

/**
 * The BinaryTree class represents a templated linked-memory tree data
 * structure.
 */
template <typename T>
class BinaryTree
{
    public:
        /**
         * Represents a tree node; that is, an element in a BinaryTree.
         * It has a data element and pointers to its left and right children.
         */
        struct Node {
            T elem;
            Node* left;
            Node* right;

            /**
             * Node element constructor; sets children to point to NULL.
             * @param element The templated data element that the constructed
             *  node will hold.
             */
            Node(const T& element) : elem(element), left(NULL), right(NULL)
            { /* nothing */
            }
        };

        /**
         * Constructor to create an empty tree.
         */
        BinaryTree();

        /**
         * Constructor that wraps raw nodes as a BinaryTree class.
         */
        BinaryTree(Node* heapNode);

        /**
         * Copy constructor.
         */
        BinaryTree(const BinaryTree& other);

        /**
         * Destructor; frees all nodes associated by this tree.
         */
        virtual ~BinaryTree();

        /**
         * Assignment operator.
         * @param rhs The tree to make a copy of
         * @return A reference to the current tree
         */
        const BinaryTree& operator=(const BinaryTree& rhs);

        /**
         * Frees all nodes associated with this tree and sets it to be empty.
         */
        void clear();

        /**
         * Inserts into the BinaryTree in BST order.
         * @param elem The element to insert
         */
        void insert(const T& elem);

        /**
         * Inserts the given value into the BinaryTree, taking a random path
         * to the leaf where it is inserted.
         *
         * @param elem The element to insert
         * @param rng  The random number generator used to compute the path
         */
        void insertRandom(const T& elem, std::mt19937& rng);

        /**
         * Prints the contents of the tree to stdout.
         */
        void print() const;

        /**
         * @return The root of the binary tree
         */
        Node* getRoot() const;

        /**
         * This lab deals with the following six helper functions:
         */

        /**
         * @return The height of the binary tree. Recall that the height of a binary
         *  tree is just the length of the longest path from the root to a leaf, and
         *  that the height of an empty tree is -1.
         */
        int height() const;

        /**
         * Prints out the values of the nodes of a binary tree in order.
         * That is, everything to the left of a node will be printed out before that
         * node itself, and everything to the right of a node will be printed out
         * after that node.
         */
        void printLeftToRight() const;

        /**
         * Flips the tree over a vertical axis, modifying the tree itself
         *  (not creating a flipped copy).
         */
        void mirror();

        /**
         * isOrdered() function iterative version
         * @return True if an in-order traversal of the tree would produce a
         *  nondecreasing list output values, and false otherwise. This is also the
         *  criterion for a binary tree to be a binary search tree.
         */
        bool isOrderedIterative() const;

        /**
         * isOrdered() function recursive version
         * @return True if an in-order traversal of the tree would produce a
         *  nondecreasing list output values, and false otherwise. This is also the
         *  criterion for a binary tree to be a binary search tree.
         */
        bool isOrderedRecursive() const;

        /**
         *  Uses vector to store values of the nodes of a binary tree in order.
         * That is, everything to the left of a node will be pushed before that
         * node itself, and everything to the right of a node will be pushed
         * after that node.
         * @param treeVector stores nodes in order
         */
        void inOrder(std::vector<T>& treeVector);

    protected:
        Node* root;

    private:

        /**
         * Put your own private helper functions here.
         * Look at the private helpers for height and printLeftToRight
         *  as examples.
         */

        /**
         * Private helper function for the public height function.
         * @param subRoot The current node in the recursion
         * @return The height of the subtree
         */
        int height(const Node* subRoot) const;

        /**
         * Private helper function for the public printLeftToRight function.
         * @param subRoot The current node in the recursion
         */
        void printLeftToRight(const Node* subRoot) const;




        /**
         * Private helper function for the sorted public insert function.
         * @param node The current node in the recursion
         * @param elem The element to insert
         */
        void insert(Node*& node, const T& elem);

        /**
         * Private helper function for the random public insert function.
         * @param node The current node in the recursion
         * @param elem The element to insert
         * @param rng  The random number generator used to compute the path
         */
        void insertRandom(Node*& node, const T& elem, std::mt19937& rng);

        /**
         * Helper function for operator= and cctor.
         * @param subRoot The current node in the recursion
         */
        Node* copy(const Node* subRoot);

        /**
         * Private helper function for clear that clears beneath the parameter node.
         * @param subRoot The current node in the recursion
         */
        void clear(Node* subRoot);

        /**
         * Private helper function for the public inOrder function.
         * @param subRoot The current node in the recursion
         * @param treeVector stores nodes in order
         */
        void inOrder(Node *subRoot, std::vector<T>& treeVector);
};

#include "binarytree_given.hpp"