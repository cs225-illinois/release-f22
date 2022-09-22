#pragma once

#include "binarytree.h"

double pemdasToAST(const std::string& pemdas_str, typename BinaryTree<std::string>::Node*& t, std::vector<std::pair<typename BinaryTree<std::string>::Node*, double>>& subtrees)
{
    std::string spaceless = "";
    for (const char c : pemdas_str) {
        if (c != ' ') {
            spaceless += c;
        }
    }

    // Decent parsing time
    std::string tokenize = "";
    for (size_t i = 0; i < spaceless.length(); ++i)
    {
        if (spaceless[i] == '(')
        {
            int depth = 1;
            std::string tok = "";
            ++i;
            while (true)
            {
                if (spaceless[i] == '(')
                {
                    ++depth;
                } 
                else if (spaceless[i] == ')')
                {
                    --depth;
                    if (depth == 0)
                    {
                        ++i;
                        break;
                    }
                }
                tok += spaceless[i];
                ++i;
            }
            typename BinaryTree<std::string>::Node* temp_tree;
            double res = pemdasToAST(tok, temp_tree, subtrees);
            tokenize += "[" + std::to_string(subtrees.size()) + "]";
            subtrees.push_back({temp_tree, res});
        }
        tokenize += spaceless[i];
    }

    // Recursion Time
    for (size_t i = 0; i < tokenize.length(); ++i) 
    {
        if (tokenize[i] == '+') {
            t = new typename BinaryTree<std::string>::Node("+");
            return pemdasToAST(tokenize.substr(0, i), t->left, subtrees) + pemdasToAST(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
        else if (tokenize[i] == '-') {
            t = new typename BinaryTree<std::string>::Node("-");
            return pemdasToAST(tokenize.substr(0, i), t->left, subtrees) - pemdasToAST(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
    }

    for (size_t i = 0; i < tokenize.length(); ++i)
    {
        if (tokenize[i] == '*') {
            t = new typename BinaryTree<std::string>::Node("*");
            return pemdasToAST(tokenize.substr(0, i), t->left, subtrees) * pemdasToAST(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
        else if (tokenize[i] == '/') {
            t = new typename BinaryTree<std::string>::Node("/");
            return pemdasToAST(tokenize.substr(0, i), t->left, subtrees) / pemdasToAST(tokenize.substr(i+1, tokenize.length()-i-1), t->right, subtrees);
        }
    }

    if (tokenize[0] == '[')
    {
        int i = 1;
        std::string idx_str = "";
        while (tokenize[i] != ']')
        {
            idx_str += tokenize[i];
            ++i;
        }
        if (idx_str != "")
        {
            int idx = std::stoi(idx_str);
            t = subtrees[idx].first;
            return subtrees[idx].second;
        }
    }

    t = new typename BinaryTree<std::string>::Node(tokenize);
    return std::stod(tokenize);
}

double pemdasToAST(const std::string& pemdas_str, typename BinaryTree<std::string>::Node*& t) {
    std::vector<std::pair<typename BinaryTree<std::string>::Node*, double>> subtrees;
    return pemdasToAST(pemdas_str, t, subtrees);
}
