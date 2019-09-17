#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
* Initializes a breadth-first ImageTraversal on a given `png` image,
* starting at `start`, and with a given `tolerance`.
* @param png The image this BFS is going to traverse
* @param start The start point of this BFS
* @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
* it will not be included in this BFS
*/
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  visited = new bool*[png.width()];
  for (unsigned i = 0; i < png.width(); i++){
    visited[i] = new bool[png.height()]{false};
  }
  tolerance_ = tolerance;
  start_ = start;
  image = png;
  add(start);
  //current = peek();
}

BFS::~BFS(){
  for (unsigned i = 0; i < image.width(); i++){
    delete visited [i];
    visited[i] = NULL;
  }
  delete visited;
  visited = NULL;
}
/**
* Returns an iterator for the traversal starting at the first point.
*/
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  //BFS* bfs = new BFS(image, start_, tolerance_);
  return ImageTraversal::Iterator(*this, start_);
}

/**
* Returns an iterator for the traversal one past the end of the traversal.
*/
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  //BFS* bfs = new BFS(image, start_, tolerance_);
  return ImageTraversal::Iterator(*this, Point(image.width()+1, 0));
}

/**
* Adds a Point for the traversal to visit at some point in the future.
*/
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  if(!visited[point.x][point.y]){
    queue.push(point);
    visited[point.x][point.y] = true;
  }
}

/**
* Removes and returns the current Point in the traversal.
*/
Point BFS::pop() {
  /** @todo [Part 1] */
  Point temp = queue.front();
  queue.pop();
  visited[temp.x][temp.y] = true;
  return temp;
}

/**
* Returns the current Point in the traversal.
*/
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(!queue.empty()){
    return queue.front();
  }
  return Point(image.width()+1, 0);
}

/**
* Returns true if the traversal is empty.
*/
bool BFS::empty() const {
  /** @todo [Part 1] */
  return queue.empty();
}
