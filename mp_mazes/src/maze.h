/* Your code here! */

#pragma once

#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"

using namespace cs225;

class SquareMaze{
    public:
        SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        PNG* drawMaze() const;
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
};