#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
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
  currentPoint_ = Point(-1, -1);
}
/*
* Overloaded constructor with traversal and start point
*/
ImageTraversal::Iterator::Iterator(ImageTraversal* it, Point point) {
  currentPoint_ = point;
  it_ = it;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  currentPoint_ = it_->pop();
  HSLAPixel start_pixel= it_->png_.getPixel(it_->start_.x, it_->start_.y);
  //right x+1
  if (currentPoint_.x + 1 < it_->png_.width()) {
    Point right(currentPoint_.x + 1, currentPoint_.y);
    HSLAPixel pixel_r = it_->png_.getPixel(right.x, right.y);
    if (calculateDelta(start_pixel, pixel_r) <= it_->tolerance_) {
      if (it_->visited_[right.x][right.y] == false) {
        it_->add(right);
      }
    }
  }
  //bottom y-1
  if (currentPoint_.y + 1 < it_->png_.height()) {
    Point bottom(currentPoint_.x, currentPoint_.y + 1);
    HSLAPixel pixel_b = it_->png_.getPixel(bottom.x, bottom.y);
    if (calculateDelta(start_pixel, pixel_b) <= it_->tolerance_) {
      if (it_->visited_[bottom.x][bottom.y] == false) {
        it_->add(bottom);
      }
    }
  }
  //left x-1
  if (currentPoint_.x > 0) {
    Point left(currentPoint_.x - 1, currentPoint_.y);
    HSLAPixel pixel_l = it_->png_.getPixel(left.x, left.y);
    if (calculateDelta(start_pixel, pixel_l) <= it_->tolerance_) {
      if (it_->visited_[left.x][left.y] == false) {
        it_->add(left);
      }
    }
  }
  //top y-1
  if (currentPoint_.y > 0) {
    Point above(currentPoint_.x, currentPoint_.y - 1);
    HSLAPixel pixel_a = it_->png_.getPixel(above.x, above.y);
    if (calculateDelta(start_pixel, pixel_a) <= it_->tolerance_) {
      if (it_->visited_[above.x][above.y] == false) {
        it_->add(above);
      }
    }
  }
  it_->visited_[currentPoint_.x][currentPoint_.y] = true;
  currentPoint_ = it_->peek();
  while (!it_->point_list_.empty()) {
    if (it_->visited_[currentPoint_.x][currentPoint_.y] == true) {
      currentPoint_ = it_->pop();
      currentPoint_ = it_->peek();
    } else {
      break;
    }
  }
  
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return this->currentPoint_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(this->currentPoint_ == other.currentPoint_);
}

