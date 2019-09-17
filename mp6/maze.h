/* Your code here! */
#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
using namespace cs225;
using namespace std;

class SquareMaze{
public:
  SquareMaze();
  void makeMaze(int width, int height);
  void setWall(int x, int y, int dir, bool exists);
  bool canTravel(int x, int y, int dir) const;
  vector<int> solveMaze();
  PNG* drawMaze() const;
  PNG* drawMazeWithSolution();

private:
  int _width;
  int _height;
  int size;
  DisjointSets cells;
  vector<bool> down;
  vector<bool> right;
};
