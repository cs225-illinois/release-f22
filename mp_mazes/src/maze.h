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

#include <maze.h>
#include <cs225.h>
class SquareMaze {
>>>>>>> ab56bd0 (something is wrong)
    public:
        SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        PNG* drawMaze() const;
<<<<<<< HEAD
        PNG* drawMazeWithSolution();
        void makeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
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
};