/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    map<Point<3>, size_t> point_to_index_map;
    vector<Point<3>> points;
    for(size_t i = 0; i < theTiles.size(); i++){
      LUVAPixel pixel = theTiles[i].getAverageColor();
      points.push_back(convertToXYZ(pixel));
      point_to_index_map.insert(pair<Point<3>, size_t>(convertToXYZ(pixel), i));
    }
    KDTree<3>* my_tree = new KDTree<3>(points);
    for(int row = 0; row < theSource.getRows(); row++){
      for(int col = 0; col < theSource.getColumns(); col++){
        LUVAPixel region_color = theSource.getRegionColor(row, col);
        Point<3> query = convertToXYZ(region_color);
        Point<3> nearest_neighbor = my_tree->findNearestNeighbor(query);
        size_t index = point_to_index_map[nearest_neighbor];
        mosaic->setTile(row, col, &theTiles[index]);
      }
    }
    my_tree->~KDTree();
    return mosaic;
}

