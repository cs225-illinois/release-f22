/**
 * tileimage.cpp (v2)
 * Impl of the TileImage class.
 *
 * @author Wade Fagen-Ulmschneider (http://waf.cs.illinois.edu/)
 * @date Fall 2017
 */

#include <algorithm>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/LUVAPixel.h"

#include "tileimage.h"

using namespace std;
using namespace cs225;

TileImage::TileImage() : image_(1, 1) {
    averageColor_ = image_.getPixel(0, 0);
}

TileImage::TileImage(const PNG& source) : image_(cropSourceImage(source)) {
    averageColor_ = calculateAverageColor();
}

PNG TileImage::cropSourceImage(const PNG& source) {
    int height = source.height();
    int width = source.width();
    int resolution = min(width, height);

    int startX = 0;
    int startY = 0;

    if (width != height) {
        if (height > width)
            startY = (height - width) / 2;
        else
            startX = (width - width) / 2;
    }

    PNG cropped(resolution, resolution);

    for (int y = 0; y < resolution; y++)
        for (int x = 0; x < resolution; x++)
            cropped.getPixel(x, y) = source.getPixel(startX + x, startY + y);

    return cropped;
}

LUVAPixel TileImage::calculateAverageColor(unsigned x0, unsigned x1, unsigned y0, unsigned y1) const {
    double sumX = 0, sumY = 0, sumZ = 0;

    for (unsigned y = y0; y < y1; y++) {
        for (unsigned x = x0; x < x1; x++) {
            const LUVAPixel & pixel = image_.getPixel(x, y);

            sumX += image_.getPixel(x, y).l;
            sumY += image_.getPixel(x, y).u;
            sumZ += image_.getPixel(x, y).v;
        }
    }

    double numPixels = (x1 - x0) * (y1 - y0);
    return LUVAPixel( sumX / numPixels, sumY / numPixels, sumZ / numPixels );
}

LUVAPixel TileImage::calculateAverageColor() const {
    return calculateAverageColor(0, image_.width(), 0, image_.height());
}

void TileImage::generateResizedImage(int startX, int startY, int resolution) {

    // set the resized_ image to size: resolution x resolution
    resized_.resize(resolution, resolution);

    // If possible, avoid floating point comparisons. This helps ensure that
    // students' photomosaic's are diff-able with solutions
    if (getResolution() % resolution == 0) {
        int scalingRatio = getResolution() / resolution;

        for (int x = 0; x < resolution; x++) {
            for (int y = 0; y < resolution; y++) {
                int pixelStartX = (x)     * scalingRatio;
                int pixelEndX   = (x + 1) * scalingRatio;
                int pixelStartY = (y)     * scalingRatio;
                int pixelEndY   = (y + 1) * scalingRatio;

                resized_.getPixel(x, y) = getScaledPixelInt(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
            }
        }
    } else { // scaling is necessary
        double scalingRatio = static_cast<double>(getResolution()) / resolution;

        for (int x = 0; x < resolution; x++) {
            for (int y = 0; y < resolution; y++) {
                double pixelStartX = (double)(x)     * scalingRatio;
                double pixelEndX   = (double)(x + 1) * scalingRatio;
                double pixelStartY = (double)(y)     * scalingRatio;
                double pixelEndY   = (double)(y + 1) * scalingRatio;

                resized_.getPixel(x, y) = getScaledPixelDouble(pixelStartX, pixelEndX, pixelStartY, pixelEndY);
            }
        }
    }
    
}    

void TileImage::paste(PNG& canvas, int startX, int startY, int resolution) {
    // check if not resized
    if (resized_.width() == 0) {
        generateResizedImage(startX, startY, resolution);
    }

    for (int x = 0; x < resolution; x++) {
        for (int y = 0; y < resolution; y++) {
            canvas.getPixel(startX + x, startY + y) = resized_.getPixel(x, y);
        }
    }
}



LUVAPixel TileImage::getScaledPixelDouble(double startX, double endX,
        double startY, double endY) const
{
    double leftFrac = 1.0 - frac(startX);
    double rightFrac = frac(endX);
    double topFrac = 1.0 - frac(startX);
    double bottomFrac = frac(endX);

    unsigned int startXint = static_cast<int>(startX);
    unsigned int endXint = static_cast<int>(ceil(endX));
    unsigned int startYint = static_cast<int>(startY);
    unsigned int endYint = static_cast<int>(ceil(endY));

    if (endXint > image_.width()) { endXint = image_.width() - 1; }
    if (endYint > image_.height()) { endYint = image_.height() - 1; }

    double sumX = 0, sumY = 0, sumZ = 0;
    double numPixels = 0;

    for (unsigned int x = startXint; x < endXint; x++) {
        for (unsigned int y = startYint; y < endYint; y++) {
            double weight = 1.0;
            if (x == startXint) weight *= leftFrac;
            if (x == endXint)   weight *= rightFrac;
            if (y == startYint) weight *= topFrac;
            if (y == endYint)   weight *= bottomFrac;

            const LUVAPixel & pixel = image_.getPixel(x, y);

            sumX += image_.getPixel(x, y).l * weight;
            sumY += image_.getPixel(x, y).u * weight;
            sumZ += image_.getPixel(x, y).v * weight;
            numPixels += weight;
        }
    }

    return LUVAPixel( sumX / numPixels, sumY / numPixels, sumZ / numPixels );
}

LUVAPixel TileImage::getScaledPixelInt(int startXint, int endXint, int startYint, int endYint) const {
    return calculateAverageColor(startXint, endXint, startYint, endYint);
}
