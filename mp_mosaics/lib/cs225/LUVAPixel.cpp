#include <iostream>
#include "LUVAPixel.h"

namespace cs225 {
  std::ostream & operator<<(std::ostream & out, LUVAPixel const & pixel) {
    out << "(" << pixel.l << ", " << pixel.u << ", " << pixel.v << (pixel.a != 1 ? ", " + std::to_string(pixel.a) : "") << ")";

    return out;
  }
}
