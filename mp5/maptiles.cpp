/**
* @file maptiles.cpp
* Code for the maptiles function.
*/

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

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
    int rows = theSource.getRows();
    int cols = theSource.getColumns();
    MosaicCanvas* output = new MosaicCanvas(rows, cols);
    std::vector<Point<3>> pixels;
    std::map<Point<3>, int> index;
    for (size_t i = 0; i < theTiles.size(); i++){
      pixels.push_back(convertToXYZ(theTiles[i].getAverageColor()));
    }
    KDTree<3> tree(pixels);
    for (size_t i = 0; i < theTiles.size(); i++){
      index[pixels[i]] = i;
    }
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        Point<3> temp = convertToXYZ(theSource.getRegionColor(i, j));
        Point<3> tile = tree.findNearestNeighbor(temp);
        int idx = index[tile];
        //TileImage* image = new TileImage(theTiles[idx]);
        output->setTile(i, j, &theTiles[idx]);
      }
    }
    return output;
  }
