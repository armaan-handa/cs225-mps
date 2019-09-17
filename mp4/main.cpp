
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG chicago, sunset, waves;
  chicago.readFromFile("chicago.png");
  sunset.readFromFile("sunset.png");
  waves.readFromFile("waves.png");

  FloodFilledImage image(chicago);
  BFS sunsetbfs(chicago, Point(0,0), 0.25);
  BFS sunsetbfs2(chicago, Point(1203, 0), 0.25);
  BFS sunsetbfs3(chicago, Point(1237, 0), 0.25);
  BFS wavesbfs(chicago, Point(1201, 300), 0.25);
  MyColorPicker sunsetfill(sunset);
  MyColorPicker wavefill(waves);

  image.addFloodFill(sunsetbfs, sunsetfill);
  image.addFloodFill(sunsetbfs2, sunsetfill);
  image.addFloodFill(sunsetbfs3, sunsetfill);
  image.addFloodFill(wavesbfs, wavefill);

  Animation animation = image.animate(100000);

  animation.write("myFloodFill.gif");
  animation.getFrame(animation.frameCount()-1).writeToFile("myFloodFill.png");
  return 0;
}
