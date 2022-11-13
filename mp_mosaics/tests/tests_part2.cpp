#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/LUVAPixel.h"
#include "cs225/RGB_LUV.h"

#include "maptiles.h"
#include "mosaiccanvas.h"


using namespace cs225;

LUVAPixel redLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 255; rgb.g = 0; rgb.b = 0; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

LUVAPixel greenLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 0; rgb.g = 255; rgb.b = 0; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

LUVAPixel blueLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 0; rgb.g = 0; rgb.b = 255; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

LUVAPixel grayLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 32; rgb.g = 32; rgb.b = 32; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

LUVAPixel whiteLUVAPixel() {
  rgbaColor rgb;
  rgb.r = 255; rgb.g = 255; rgb.b = 255; rgb.a = 255;
  luvaColor luv = rgb2luv(rgb);
  return LUVAPixel(luv.l, luv.u, luv.v, luv.a);
}

TEST_CASE("Creates a basic MosaicCanvas (gridtest)", "[weight=5][part=2]") {
  // Read `tests/gridtest.png` from disk
  PNG sourcePNG;
  sourcePNG.readFromFile("../tests/gridtest.png");
  SourceImage source(sourcePNG, 8);

  // Create a list of images to choose from to make our mosaic.  As a basic
  // test, we'll use images of one pixel colored either red, green, or blue.
  vector<TileImage> tileList;

  PNG a(1, 1);  a.getPixel(0, 0) = redLUVAPixel();  // red
  PNG b(1, 1);  b.getPixel(0, 0) = greenLUVAPixel(); // green
  PNG c(1, 1);  c.getPixel(0, 0) = blueLUVAPixel(); // blue

  tileList.push_back(TileImage(a));
  tileList.push_back(TileImage(b));
  tileList.push_back(TileImage(c));

  // Draw the mosaic!
  MosaicCanvas* canvas = mapTiles(source, tileList);
  REQUIRE( canvas != NULL );

  PNG actual = canvas->drawMosaic(10);
  PNG expected;  expected.readFromFile("../tests/gridtest-expected.png");

  // Save and check for correctness
  actual.writeToFile("gridtest-actual.png");
  INFO("Saved `actual` as gridtest-actual.png.");

  REQUIRE( actual == expected );
  delete canvas; canvas = NULL;
}

TEST_CASE("Creates a basic MosaicCanvas with pitch black (uofi-bw)", "[weight=5][part=2]") {
  // Read `tests/gridtest.png` from disk
  PNG sourcePNG;
  sourcePNG.readFromFile("../tests/uofi-bw.png");
  SourceImage source(sourcePNG, 128);

  // Create a list of images to choose from to make our mosaic.  As a basic
  // test, we'll use images of one pixel colored either red, green, or blue.
  vector<TileImage> tileList;

  PNG a(1, 1);  a.getPixel(0, 0) = redLUVAPixel();  // red
  PNG b(1, 1);  b.getPixel(0, 0) = greenLUVAPixel(); // green
  PNG c(1, 1);  c.getPixel(0, 0) = blueLUVAPixel(); // blue
  PNG d(1, 1);  d.getPixel(0, 0) = grayLUVAPixel(); // gray
  PNG e(1, 1);  e.getPixel(0, 0) = whiteLUVAPixel(); // gray

  tileList.push_back(TileImage(a));
  tileList.push_back(TileImage(b));
  tileList.push_back(TileImage(c));
  tileList.push_back(TileImage(d));
  tileList.push_back(TileImage(e));

  // Draw the mosaic!
  MosaicCanvas* canvas = mapTiles(source, tileList);
  REQUIRE( canvas != NULL );

  PNG actual = canvas->drawMosaic(10);
  PNG expected;  expected.readFromFile("../tests/uofi-bw-expected.png");

  // Save and check for correctness
  actual.writeToFile("uofi-bw-actual.png");
  INFO("Saved `actual` as uofi-bw-actual.png.");

  REQUIRE( actual == expected );
  delete canvas; canvas = NULL;
}
