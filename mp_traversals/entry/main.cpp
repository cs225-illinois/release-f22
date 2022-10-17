
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
  PNG luffy;
  luffy.readFromFile("../tests/i.png");
  FloodFilledImage myImage(luffy);
  std::cout<<"height x width = "<<luffy.height()<<" : "<<luffy.width()<<std::endl;
  DFS dfs(luffy, Point(163, 30), 0.4);
  BFS bfs(luffy, Point(0,0), 0.4);
  HSLAPixel c1(25, 1, 0.5);
  HSLAPixel c2(180, 1, 0.5);
  GradientColorPicker gp(c1, c2, Point(163, 30), 10);
  myImage.addFloodFill(dfs, gp);
  myImage.addFloodFill(bfs, gp);

  Animation animation = myImage.animate(1000);
  std::cout<<"line 33"<<std::endl;
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  std::cout<<"line 35"<<std::endl;
  lastFrame.writeToFile("myFloodFill.png");
  std::cout<<"line 37"<<std::endl;
  animation.write("myFloodFill.gif");
  std::cout<<"line 39"<<std::endl;


  return 0;
}
