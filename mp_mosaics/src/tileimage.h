/**
 * tileimage.h (v2)
 * Definition of the TileImage class.
 */

#pragma once

#include <math.h>
#include <stdint.h>

#include "cs225/PNG.h"
#include "cs225/LUVAPixel.h"

using namespace cs225;

/**
 * Represents a Tile in the Photomosaic.
 */
class TileImage {
  private:
    PNG image_;
    PNG resized_;
    LUVAPixel averageColor_;

  public:
    TileImage();
    explicit TileImage(const PNG& theImage);
    LUVAPixel getAverageColor() const { return averageColor_; }
    int getResolution() const { return image_.width(); }
    void paste(PNG& canvas, int startX, int startY, int resolution);

  private:
    void generateResizedImage(int startX, int startY, int resolution);      
    static PNG cropSourceImage(const PNG& source);
    LUVAPixel calculateAverageColor() const;
    LUVAPixel calculateAverageColor(unsigned x0, unsigned y0, unsigned x1, unsigned y1) const;

    LUVAPixel getScaledPixelDouble(double startX, double endX,
                                   double startY, double endY) const;
    LUVAPixel getScaledPixelInt(int startX, int endX,
                                int startY, int endY) const;
    static uint64_t divide(uint64_t a, uint64_t b) {
      return (a + b / 2) / b;
    }
    static int divide(int a, int b) {
        return divide(static_cast<uint64_t>(a), static_cast<uint64_t>(b));
    }
    static int fdivide(double a, double b) {
        return a / b + 0.5;
    }
    static double frac(double x) {
        return x - floor(x);
    }
};

