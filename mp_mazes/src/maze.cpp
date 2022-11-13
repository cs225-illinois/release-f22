/* Your code here! */

#include "maze.h"

#include <vector>
#include <queue>
#include <iostream>
#include <random>
#include <sys/time.h>

using namespace cs225;

SquareMaze::SquareMaze() {
    //creates empty maze
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    int index = x + (y*width_);
    if (dir == 0) {
        return rightWalls[index] == false;
    } else if (dir == 1) {
        return downWalls[index] == false;
    } else if (dir == 2) {
        return  (x != 0) && (downWalls[index - 1] == false);
    } else if (dir == 3) {
        return (y != 0) && (downWalls[index - width_] == false);
    }
    return false;
}
PNG* SquareMaze::drawMaze() const {
    int maze_height = 10*height_ + 1;
    int maze_width = 10*width_ + 1;
    PNG* maze = new PNG(maze_width, maze_height);

    for (int y = 0; y < maze_height; y++) {
        HSLAPixel& p = maze->getPixel(0,y);
        p.l = 0;
    }
    for (int x = 10; x < maze_width; x++) {
         HSLAPixel& p = maze->getPixel(x, 0);
        p.l = 0;
    }

    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            int index = x + (y*width_);
            if (rightWalls[index]) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel &p = maze->getPixel((x+1)*10, y*10 + k);
                    p.l = 0;
                }
            }
            if (downWalls[index]) {
                for (int k = 0; k <= 10; k++) {
                    HSLAPixel &p = maze->getPixel(x*10 + k, (y+1) * 10);
                    p.l = 0;
                }
            }
        }
    }
    return maze;
}
PNG* SquareMaze::drawMazeWithSolution() {
    HSLAPixel Red(0,1,0.5,1);
    const int& start = 5;
    int x = start;
    int y = start;
    int dest_x = destination_ % width_;
    int dest_y = destination_ / height_;
    PNG* maze = drawMaze();
    std::vector<int> soln = solveMaze();

    for (int i = 1; i <= 9; i++) {
        HSLAPixel& p = maze->getPixel(dest_x*10 + i, (dest_y + 1)*10);
        p.l = 1;
    }

    for (size_t i = 0; i < soln.size(); i++) {
        maze = drawSolnLineSeg(maze, &x, &y , soln[i]);
    }
    return maze;
}
void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    int mazeSize = width_*height_;
    int x, y;
    struct timeval seed;
    gettimeofday(&seed, NULL);
    srand(seed.tv_usec);
    mazeSets.addelements(mazeSize);
    for (int i = 0; i < mazeSize; i++) {
        rightWalls.push_back(true);
        downWalls.push_back(true);
    }
    while (mazeSets.size(0) < mazeSize) {
        x = rand() % width_;
        y = rand() % height_;
        int index = x + (y*width_);
        if (rand() % 2 == 1) {
            if (x != width_ - 1) {
                if (mazeSets.find(index) != mazeSets.find(index+1)) {
                    setWall(x, y, 0, false);
                    mazeSets.setunion(index, index+1);
                }
            }
        } else {
            if (y != height_ - 1) {
                if (mazeSets.find(index) != mazeSets.find(index + width_)) {
                    setWall(x, y, 1, false);
                    mazeSets.setunion(index, index + width_);
                }
            }
        }
    }
}
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    int index = x + (y*width_);
    if (dir == 0) {
        rightWalls[index] = exists;
    } else if (dir == 1) {
        downWalls[index] = exists;
    }
    
}
std::vector<int> SquareMaze::solveMaze() {
    std::vector<int> solution;
    int x, y, current;
    std::vector<int> bfs_path;
    std::vector<int> distance;
    distance.push_back(0);
    bfs_path.push_back(0);
    for (int i = 1; i < width_ * height_; i++) {
      bfs_path.push_back(-1);
      distance.push_back(0);
    }
    std::queue<int> bfs;
    bfs.push(0);
    while (!bfs.empty()) {
        current = bfs.front();
        x = current % width_;
        y = current / width_;
        bfs.pop();
        if (canTravel(x, y, 0)) { //+1
            if (bfs_path[current + 1] == -1) {
                bfs.push(current + 1);
                bfs_path[current + 1] = current;
                distance[current + 1] = distance[current] + 1;
            }
        }
        if (canTravel(x, y, 1)) { //+width_
            if (bfs_path[current + width_] == -1) {
                bfs.push(current + width_);
                bfs_path[current + width_] = current;
                distance[current + width_] = distance[current] + 1;
            }
        }
        if (canTravel(x, y, 2)) { // -1
            if (bfs_path[current - 1] == -1) {
                bfs.push(current - 1);
                bfs_path[current - 1] = current;
                distance[current - 1] = distance[current] + 1;
            }
        }
        if (canTravel(x, y, 3)) { //- width_
            if (bfs_path[current - width_] == -1) {
                bfs.push(current - width_);
                bfs_path[current - width_] = current;
                distance[current - width_] = distance[current] + 1;
            }
        }
    }
    int furthest_destination = width_ * (height_ - 1);
    for (int i = 0; i < width_; i++) {
        if (distance[width_ * (height_ - 1) + i] > distance[furthest_destination]) {
            furthest_destination = width_ * (height_ - 1) + i;
        }
    }
    destination_ = furthest_destination;
    int curr_idx = destination_;
    while(curr_idx != 0){
      if(bfs_path[curr_idx] == curr_idx - 1){
        solution.push_back(0);
      }
      if(bfs_path[curr_idx] == curr_idx - width_){
        solution.push_back(1);
      }
      if(bfs_path[curr_idx] == curr_idx + 1){
        solution.push_back(2);
      }
      if(bfs_path[curr_idx] == curr_idx + width_){
        solution.push_back(3);
      }
      curr_idx = bfs_path[curr_idx];
    }
    std::vector<int> rev_soln;
    for (auto it = solution.rbegin(); it != solution.rend(); ++it) {
        rev_soln.push_back(*it);
    }
    return rev_soln;
}

PNG* SquareMaze::drawSolnLineSeg(PNG* maze, int* x, int* y, int dir) {
    HSLAPixel Red(0,1,0.5,1);
    switch(dir) {
        case 0:
            for (int i = 0; i <= 10; i++) {
                HSLAPixel& p = maze->getPixel(*x + i, *y);
                p.h = Red.h;
                p.s = Red.s;
                p.l = Red.l;
                p.a = Red.a;
            }
            *x += 10;
            break;
        case 1:
            for (int i = 0; i <= 10; i++) {
                HSLAPixel& p = maze->getPixel(*x, *y + i);
                p.h = Red.h;
                p.s = Red.s;
                p.l = Red.l;
                p.a = Red.a;
            }
            *y += 10;
            break;
        case 2:
            for (int i = 0; i <= 10; i++) {
                HSLAPixel& p = maze->getPixel(*x - i, *y);
                p.h = Red.h;
                p.s = Red.s;
                p.l = Red.l;
                p.a = Red.a;
            }
            *x -= 10;
            break;
        case 3:
            for (int i = 0; i <= 10; i++) {
                HSLAPixel& p = maze->getPixel(*x, *y - 1);
                p.h = Red.h;
                p.s = Red.s;
                p.l = Red.l;
                p.a = Red.a;
            }
            *y -= 10;
            break;
    }
    return maze;

}