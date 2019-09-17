#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>

#include <cstdlib>

#include <ctime>

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
    cs225 :: PNG input;
    input.readFromFile(inputFile);
    cs225::PNG output(input.width(), input.height());
    for (unsigned x = 0; x < input.width(); x++){
        for (unsigned y = 0; y < input.height(); y++){
            unsigned x1 = output.width() - x - 1;
            unsigned y1 = output.height() - y - 1;
            HSLAPixel & pixel = input.getPixel(x, y);
            HSLAPixel & rpixel = output.getPixel(x1, y1);
            rpixel.h = pixel.h;
            rpixel.s = pixel.s;
            rpixel.l = pixel.l;
            rpixel.a = pixel.a;
        }
    }
    output.writeToFile(outputFile);
    return;
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
    unsigned piano, body, pianoStart, pianoEnd;
    piano = height/2 + 99;
    body = height/2 - 101;
    pianoEnd = width/2 + 335;
    pianoStart = width/2 - 337;
    for (unsigned x = 0; x < width; x++){
        for (unsigned y = 0; y < height; y++){
            HSLAPixel & pixel = png.getPixel(x, y);
            pixel.s = 1;
            pixel.a = 1;
            if (y <= piano){
                srand(((x+20)/20)*((y+20)/20));
                pixel.h = rand()%360;
                pixel.l = 0.5;
            }
            else{
                pixel.h = 10;
                pixel.l = 0;
            }
        }
    }
    
    for (unsigned x = pianoStart; x < pianoEnd; x++){
        for (unsigned y = body; y < piano+1; y++){
            HSLAPixel & pixel = png.getPixel(x, y);
            pixel.l = 1;
        }
    }
    /*for (unsigned x = pianoStart; x < pianoEnd; x++){
        for (unsigned y = (height/2)-1; y < (height/2); y++){
            HSLAPixel & pixel = png.getPixel(x, y);
            pixel.l = 0;
        }
    }
    for (unsigned x = pianoStart; x < pianoEnd; x = x + 112){
        for (unsigned y = (height/2)-1; y < piano; y++){
            HSLAPixel & pixel = png.getPixel(x, y);
            pixel.l = 0;
        }
    }*/
    int count = 0;
    for (unsigned x = pianoStart; x < pianoEnd; x = x + 56){
        count = count + 1;
        for (unsigned z = x; z < x + 56; z++)
            for (unsigned y = body; y < (height/2); y++){
                HSLAPixel & pixel = png.getPixel(z, y);
                if (count == 1 || count == 3 || count == 5 || count == 6 || count == 8 || count == 10 || count == 12){
                    pixel.l = 1;
                }
                else {
                    pixel.l = 0;
                }
            }
    }
    int xline;
    xline = pianoStart + 85;
    for (unsigned y = body; y < piano+1; y++){
        HSLAPixel & pixel = png.getPixel(xline, y);
        pixel.l = 0;
    }
    xline = xline + 105;
    for (unsigned y = body; y < piano+1; y++){
        HSLAPixel & pixel = png.getPixel(xline, y);
        pixel.l = 0;
    }
    xline = xline + 85;
    for (unsigned y = body; y < piano+1; y++){
        HSLAPixel & pixel = png.getPixel(xline, y);
        pixel.l = 0;
    }
    xline = xline + 85;
    for (unsigned y = body; y < piano+1; y++){
        HSLAPixel & pixel = png.getPixel(xline, y);
        pixel.l = 0;
    }
    xline = xline + 105;
    for (unsigned y = body; y < piano+1; y++){
        HSLAPixel & pixel = png.getPixel(xline, y);
        pixel.l = 0;
    }
    xline = xline + 105;
    for (unsigned y = body; y < piano+1; y++){
        HSLAPixel & pixel = png.getPixel(xline, y);
        pixel.l = 0;
    }
    
  return png;
}
