/* Your code here! */
#include "maze.h"
#include <map>
#include <queue>
SquareMaze::SquareMaze(){

}
void SquareMaze::makeMaze (int width, int height){
  _width = width;
  _height = height;
  size = width * height;
  cells.addelements(size);
  for(int i = 0; i < size; i++){
    right.push_back(true);
    down.push_back(true);
  }
  int numofwalls = size/2;
  int i = 0;
  int _right = 0;
  srand (time(NULL));
  while(i < numofwalls){
    int row = rand() % (height-1);
    int col = rand() % (width-1);
    int _right = rand() % 2;
    if(_right){
      if(right[row*width + col] == true && cells.find(row*width + col) != cells.find(row*width + col+1)){
        right[row*width + col] = false;
        cells.setunion (row*width + col, row*width + col+1);
        _right = 0;
        i++;
      }
    }
    else{
      if(down[row*width + col] == true && cells.find(row*width + col) != cells.find((row+1)*width + col)){
        down[row*width + col] = false;
        cells.setunion (row*width + col, (row+1)*width + col);
        _right = 1;
        i++;
      }
    }
  }
  int row = 0;
  for(; row < height-1; row++){
    int column = 0;
    for(; column < width-1; column++){
      if(_right){
        if(right[row*width + column] == true && cells.find(row*width + column) != cells.find(row*width + column+1)){
          right[row*width + column] = false;
          cells.setunion (row*width + column, row*width + column+1);
        }
        if(down[row*width + column] == true && cells.find(row*width + column) != cells.find((row+1)*width + column)){
          down[row*width + column] = false;
          cells.setunion (row*width + column, (row+1)*width + column);
        }
        _right = 0;
      }
      else{
        if(down[row*width + column] == true && cells.find(row*width + column) != cells.find((row+1)*width + column)){
          down[row*width + column] = false;
          cells.setunion (row*width + column, (row+1)*width + column);
        }
        if(right[row*width + column] == true && cells.find(row*width + column) != cells.find(row*width + column+1)){
          right[row*width + column] = false;
          cells.setunion (row*width + column, row*width + column+1);
        }
        _right = 1;
      }
    }
    if(down[row*width + column] == true && cells.find(row*width + column) != cells.find((row+1)*width +column)){
      down[row*width + column] = false;
      cells.setunion (row*width + column, (row+1)*width + column);
    }
  }
  for(int column = 0; column < width-1; column++){
    if(right[row*width + column] == true && cells.find(row*width + column) != cells.find(row*width + column+1)){
      right[row*width + column] = false;
      cells.setunion (row*width + column, row*width + column+1);
    }
  }
}

bool SquareMaze::canTravel (int x, int y, int dir) const{
  if(dir == 0 && x < _width-1){
    return !(right[y*_width + x]);
  }
  if(dir == 1 && y < _height-1){
    return !(down[y*_width + x]);
  }
  if(dir == 2 && x > 0){
    return !(right[y*_width + x-1]);
  }
  if(dir == 3 && y > 0){
    return !(down[(y-1)*_width + x]);
  }
  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
  int index = y*_width + x;
  if(dir == 0 && x < _width-1){
    right[index] = exists? true : false;
  }
  if(dir == 1 && y < _height-1){
    down[index] = exists? true : false;
  }
  return;
}

vector< int > SquareMaze::solveMaze ()
{
  vector<int> bottom;
  map<int, int> moves;
  vector<bool> visited;
  for(int i = 0; i < size; i++) visited.push_back(false);

  queue<int> q;
  q.push(0);
  visited[0] = true;

  while(!q.empty()) {
    int val = q.front();
    q.pop();
    int x = val % _width;
    int y = val / _width;
    if (y == _height - 1) {
      bottom.push_back(val);
    }
    //check for right cell
    if (canTravel(x, y, 0) && !visited[val + 1]) {
      moves.insert(pair<int, int> (val + 1, val));
      visited[val + 1] = true;
      q.push(val + 1);
    }
    //check for down cell
    if (canTravel(x, y, 1) && !visited[val + _width]) {
      moves.insert(pair<int, int> (val + _width, val));
      visited[val + _width] = true;
      q.push(val + _width);
    }
    //check for left cell
    if (canTravel(x, y, 2) && !visited[val - 1]) {
      moves.insert(pair<int, int> (val - 1, val));
      visited[val - 1] = true;
      q.push(val - 1);
    }
    //check for up cell
    if (canTravel(x, y, 3) && !visited[val - _width]) {
      moves.insert(pair<int, int> (val - _width, val));
      visited[val - _width] = true;
      q.push(val - _width);
    }
  }
  vector<int> solution;
  int final = _width - 1;
  while(bottom[final] == bottom[final - 1]){
    final -= 1;
  }
  int start = bottom[final];
  while (start != 0) {
    int prev = moves[start];
    if (start == prev + 1){
      solution.push_back(0);
    }
    else if (start == prev - 1) {
      solution.push_back(2);
    }
    else if (start == prev + _width){
      solution.push_back(1);
    }
    else if (start == prev - _width){solution.push_back(3);
    }
    start = prev;
  }
  reverse(solution.begin(),solution.end());
  return solution;
}

PNG* SquareMaze::drawMaze() const{
  PNG* output = new PNG(_width*10 + 1, _height*10 + 1);
  for(int i = 0; i < _height*10; i++){
    output->getPixel(0, i).l = 0;
  }
  output->getPixel(0,0).l = 0;
  for(int i = 10; i < _width*10; i++){
    output->getPixel(i, 0).l = 0;
  }
  for(int i = 0; i < size; i++){
    int x = i%_width;
    int y = i/_width;
    if(right[i]){
      for (int k = 0; k <= 10; k++){
        output->getPixel((x+1)*10,y*10+k).l = 0;
      }
    }
    if(down[i]){
      for (int k = 0; k <= 10; k++){
        output->getPixel(x*10+k, (y+1)*10).l = 0;
      }
    }
  }
  return output;
}
PNG * SquareMaze::drawMazeWithSolution ()
{
  PNG * output = drawMaze();
  vector<int> solution = solveMaze();
  int x = 5;
  int y = 5;
  for(size_t i = 0; i < solution.size(); i++){
    if(solution[i] == 0){
      for(int j = 0; j < 11; j++){
        output->getPixel(x + j, y).h = 0;
        output->getPixel(x + j, y).s = 1;
        output->getPixel(x + j, y).l = 0.5;
        output->getPixel(x + j, y).a = 1;
      }
      x += 10;
    }
    else if(solution[i] == 1){
      for(int j = 0; j < 11; j++){
        output->getPixel(x, y + j).h = 0;
        output->getPixel(x, y + j).s = 1;
        output->getPixel(x, y + j).l = 0.5;
        output->getPixel(x, y + j).a = 1;
      }
      y += 10;
    }
    else if(solution[i] == 2){
      for(int j = 0; j < 11; j++){
        output->getPixel(x - j, y).h = 0;
        output->getPixel(x - j, y).s = 1;
        output->getPixel(x - j, y).l = 0.5;
        output->getPixel(x - j, y).a = 1;
      }
      x -= 10;
    }
    else{
      for(int j = 0; j < 11; j++){
        output->getPixel(x, y - j).h = 0;
        output->getPixel(x, y - j).s = 1;
        output->getPixel(x, y - j).l = 0.5;
        output->getPixel(x, y - j).a = 1;
      }
      y -= 10;
    }
  }
  int mazex = x /10;
  int mazey = _height;
  for(int k = 1; k < 10; k++){
    output->getPixel(mazex * 10 + k, mazey * 10).l = 1;
  }
  return output;
}
