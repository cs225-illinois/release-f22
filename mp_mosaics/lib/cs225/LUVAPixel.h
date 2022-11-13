/**
 * @file LUVAPixel.h
 *
 * @author CS 225: Data Structures
 */

#pragma once

#include <iostream>
#include <sstream>
#include <cmath>

namespace cs225 {
  class LUVAPixel {
  public:
    double l;
    double u;
    double v;
    double a;

    LUVAPixel() : LUVAPixel(0.9642, 1.0000, 0.8249, 1) {}
    LUVAPixel(double l, double u, double v) : LUVAPixel(l, u, v, 1) {}
    LUVAPixel(double l, double u, double v, double a) : l(l), u(u), v(v), a(a) {}

    bool operator== (LUVAPixel const & other) const { 
      if (fabs(l - other.l) > 0.00001) { return false; }
      if (fabs(u - other.u) > 0.00001) { return false; }
      if (fabs(v - other.v) > 0.00001) { return false; }
      return true;
      //return (l == other.l && u == other.u && v == other.v); 
    }

    bool operator!= (LUVAPixel const & other) const { return !(*this == other); }
    bool operator<  (LUVAPixel const & other) const {
      if (l < other.l) { return true; }
      if (u < other.u) { return true; }
      if (v < other.v) { return true; }
      return false;
    }
  };

  std::ostream & operator<<(std::ostream & out, LUVAPixel const & pixel);
  std::stringstream & operator<<(std::stringstream & out, LUVAPixel const & pixel);
}
