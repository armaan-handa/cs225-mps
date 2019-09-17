#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image drake;
  Image wade;
  Image mallocimg;
  Image newimg;
  Image myImage;

  drake.readFromFile("drake.png");
  wade.readFromFile("wade.png");
  mallocimg.readFromFile("malloc.png");
  newimg.readFromFile("new.png");
  myImage = Image();

  //StickerSheet mysheet = StickerSheet(drake, 4);
  StickerSheet mysheet(drake, 4);
  mallocimg.scale(420, 220);
  newimg.scale(420, 220);
  wade.scale(100,120);

  mysheet.addSticker(wade, 15, 15);
  mysheet.addSticker(wade, 115, 230);
  mysheet.addSticker(mallocimg, 240, 1);
  mysheet.addSticker(newimg, 240, 240);

  myImage = mysheet.render();
  myImage.writeToFile("myImage.png");


  return 0;
}
