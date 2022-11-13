/**
 * @file maptiles.h
 *
 * mapTiles() function.
 * Developed for CS225 PhotoMosaic MP
 *
 * @author Jack Toole
 * @date Fall 2011
 */

#pragma once

#include <map>
#include <vector>

#include "cs225/PNG.h"

#include "kdtree.h"
#include "mosaiccanvas.h"
#include "sourceimage.h"
#include "tileimage.h"

using namespace cs225;

/**
 * Map the image tiles into a mosaic canvas which closely
 * matches the input image.
 *
 * @todo This function is required for Part 2.
 * @param theSource The input image to construct a photomosaic of
 * @param theTiles The tiles image to use in the mosaic
 */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> & theTiles);

// TODO: move this comment back to inline above once someone figures out unidef-like real directive parsing
// SOLUTION
