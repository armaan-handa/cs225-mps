#include "cs225/PNG.h"
#include "Image.h"

Image::Image() : cs225::PNG (){
}

Image::Image(unsigned int width, unsigned int height) : cs225::PNG(width, height){}

Image::Image(Image const & other) : cs225::PNG(other){}

void Image::lighten(){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.l = pixel.l + 0.1;
            if (pixel.l > 1){
                pixel.l = 1;
            }
        }
    }
    return;
}
void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.l = pixel.l + amount;
            if (pixel.l > 1){
                pixel.l = 1;
            }
        }
    }
    return;
}
void Image::darken(){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.l = pixel.l - 0.1;
            if (pixel.l < 0){
                pixel.l = 0;
            }
        }
    }
    return;
}
void Image::darken(double amount){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.l = pixel.l - amount;
            if (pixel.l < 0){
                pixel.l = 0;
            }
        }
    }
    return;
}
void Image::saturate(){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.s = pixel.s + 0.1;
            if (pixel.s > 1){
                pixel.s = 1;
            }
        }
    }
    return;
}
void Image::saturate(double amount){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.s = pixel.s + amount;
            if (pixel.s > 1){
                pixel.s = 1;
            }
        }
    }
    return;
}
void Image::desaturate(){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.s = pixel.s - 0.1;
            if (pixel.s < 0){
                pixel.s = 0;
            }
        }
    }
    return;
}
void Image::desaturate(double amount){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.s = pixel.s - amount;
            if (pixel.s < 0){
                pixel.s = 0;
            }
        }
    }
    return;
}
void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
    return;
}
void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++){
        for (unsigned y = 0; y < height(); y++){
            cs225::HSLAPixel & pixel = getPixel(x,y);
            double finalDegree = pixel.h + degrees;
            if (finalDegree >= 360){
                finalDegree = finalDegree - 360;
            }
            if (finalDegree < 0){
                finalDegree = 360 + finalDegree;
            }
            pixel.h = finalDegree;
        }
    }
    return;
}
void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel & pixel = getPixel(x, y);
            if (pixel.h > 102.5 && pixel.h < 293.5){
                pixel.h = 216;
            }
            else {
                pixel.h = 11;

            }
        }
    }
    return;
}
void Image::scale (double factor){

    unsigned int scalew = width() * factor;
    unsigned int scaleh = height() * factor;
    Image Scaled = Image(scalew, scaleh);
    int countx;
    int county;
    for (unsigned x = 0; x < scalew; x++){
        countx = x/factor;
        for (unsigned y = 0; y < scaleh; y++){
            county = y/factor;
            cs225::HSLAPixel & pixel = getPixel(countx, county);
            cs225::HSLAPixel & scaledpixel = Scaled.getPixel(x, y);
            scaledpixel.h = pixel.h;
            scaledpixel.s = pixel.s;
            scaledpixel.l = pixel.l;
            scaledpixel.a = pixel.a;
        }
    }
    resize(scalew, scaleh);
    for (unsigned x = 0; x < scalew; x++){
        for (unsigned y = 0; y < scaleh; y++){
            cs225::HSLAPixel & pixel = getPixel(x, y);
            cs225::HSLAPixel & scaledpixel = Scaled.getPixel(x, y);
            pixel.h = scaledpixel.h;
            pixel.s = scaledpixel.s;
            pixel.l = scaledpixel.l;
            pixel.a = scaledpixel.a;
        }
    }
    return;
}
void Image::scale(unsigned w, unsigned h){
    double swidth = w;
    double sheight = h;
    double factor = swidth / width();
    if (h < factor * height()){
        factor = sheight/height();
        scale(factor);
    }
    else {
        scale(factor);
    }
    return;
}
