/* Your code here! */
<<<<<<< HEAD

#pragma once

#include <vector>
#include <iostream>

class DisjointSets {
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        std::vector<int> elems;
};

=======
#pragma once
#include <vector>

class DisjointSets {
    public:

        void addelements(int num);   

        int find(int elem);

        void setunion(int a, int b);

        int size(int elem);

    private:

        std::vector<int> _elems;
};

#include "dsets.cpp"
>>>>>>> ab56bd0 (something is wrong)
