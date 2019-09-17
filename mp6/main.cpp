#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    PNG arthur;
    arthur.readFromFile("arthur.png");
    SquareMaze m;
    m.makeMaze(arthur.width(), arthur.height());
    std::vector<int> sol = m.solveMaze();
    PNG* out = m.drawMazeWithSolution();
    for (unsigned x = 0; x < arthur.width()*10; x++){
      for(unsigned y = 0; y < arthur.height()*10; y++){
        if (out->getPixel(x, y).h == 0 &&
         out->getPixel(x, y).s == 0 &&
         out->getPixel(x, y).l == 0 &&
         out->getPixel(x, y).a == 1){
           out->getPixel(x, y) = arthur.getPixel(x/10, y/10);
         }
         else{
           out->getPixel(x, y) = arthur.getPixel(x/10, y/10);
           out->getPixel(x, y).l = 0;
         }
      }
    }
    out->writeToFile("myMaze.png");
}
