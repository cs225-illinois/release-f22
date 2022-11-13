/* Your code here! */
<<<<<<< HEAD

#pragma once

#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"

using namespace cs225;

class SquareMaze{
=======
#pragma once


#include <vector>
#include "cs225/PNG.h"

using namespace cs225;

class SquareMaze {
>>>>>>> ab56bd0 (something is wrong)
    public:
        SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        PNG* drawMaze() const;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 3faf106 (pulling lab_dit)
        PNG* drawMazeWithSolution();
        void makeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
<<<<<<< HEAD
        PNG* drawSolnLineSeg(PNG* maze, int *x, int *y, int dir);

        int width_;
        int height_;
        int destination_;
        DisjointSets mazeSets;
        std::vector<bool> rightWalls;
        std::vector<bool> downWalls;
=======
    private:
>>>>>>> ab56bd0 (something is wrong)
=======
    private:
        std::vector<int> _sol;
        PNG* _maze;
>>>>>>> 3faf106 (pulling lab_dit)
};