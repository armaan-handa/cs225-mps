#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
* Calculates a metric for the difference between two pixels, used to
* calculate if a pixel is within a tolerance.
*
* @param p1 First pixel
* @param p2 Second pixel
* @return the difference between two HSLAPixels
*/
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
* Default iterator constructor.
*/
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal &traversal, Point point){
  current = point;
  traversal_ = &traversal;
  startPoint = traversal.start_;
}
/**
* Iterator increment opreator.
*
* Advances the traversal of the image.
*/
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(!traversal_->empty()){
    current = traversal_->pop();
    Point temp = current;
    if(current.x < (traversal_->image.width()-1)){
      temp = Point(current.x+1, current.y);
      if(isvalid(temp)){
        traversal_->add(temp);
      }
    }
    if(current.y < (traversal_->image.height()-1)){
      temp = Point(current.x, current.y+1);
      if(isvalid(temp)){
        traversal_->add(temp);
      }
    }
    if(current.x > 0){
      temp = Point(current.x-1, current.y);
      if(isvalid(temp)){
        traversal_->add(temp);
      }
    }
    if(current.y > 0){
      temp = Point(current.x, current.y-1);
      if(isvalid(temp)){
        traversal_->add(temp);
      }
    }
    current = traversal_->peek();
  }
  return *this;
}

bool ImageTraversal::Iterator::isvalid(Point point){
  HSLAPixel startpixel = traversal_->image.getPixel(startPoint.x, startPoint.y);
  HSLAPixel pixel = traversal_->image.getPixel(point.x, point.y);
  double delta = calculateDelta(startpixel, pixel);
  if(delta < traversal_->tolerance_){
    return true;
  }
  return false;

}

/**
* Iterator accessor opreator.
*
* Accesses the current Point in the ImageTraversal.
*/
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
* Iterator inequality operator.
*
* Determines if two iterators are not equal.
*/
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

  if (traversal_ == NULL){
    thisEmpty = true;
  }
  if (other.traversal_ == NULL){
    otherEmpty = true;
  }

  if (!thisEmpty) {
    thisEmpty = traversal_->empty();
  }
  if (!otherEmpty) {
    otherEmpty = other.traversal_->empty();
  }

  if (thisEmpty && otherEmpty){
    return false;
  }
  else if ((!thisEmpty)&&(!otherEmpty)) {
    return !(current == other.current);
  }
  else {
    return true;
  }

}

/*bool ImageTraversal::operator==(const ImageTraversal & other){
  return (image == other.image && start_ == other.start_ && tolerance_ == other.tolerance_);
}
*/
