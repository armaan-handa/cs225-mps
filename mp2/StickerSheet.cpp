#include "StickerSheet.h"
#include "Image.h"


StickerSheet::StickerSheet(const Image & picture, unsigned max){
    width_ = picture.width();
    height_ = picture.height();
    max_ = max;
    stickers_ = new Image*[max_];
    count_ = 0;
    base = new Image (picture);
    x_ = new unsigned[max];
    y_ = new unsigned[max];
    for (unsigned i = 0; i < max; i++){
        stickers_[i] = NULL;
        x_[i] = 0;
        y_[i] = 0;
    }
}

StickerSheet::~StickerSheet(){
    for (unsigned i = 0; i < max_; i++){
        delete stickers_[i];
        stickers_[i] = NULL;
    }
    delete[] stickers_;
    stickers_ = NULL;
    delete[] x_;
    delete[] y_;
    delete base;
}

StickerSheet::StickerSheet(const StickerSheet & other){
    Copy(other);
}

const StickerSheet & StickerSheet::operator=(const StickerSheet & other){
    if (this!= &other) {
        Copy(other);
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if (max == max_){
        return;
    }
    unsigned int small;
    if (max < max_){
        small = max;
    }
    else{
        small = max_;
    }
    Image** temp = new Image*[max];
    unsigned* tempx = new unsigned[max];
    unsigned* tempy = new unsigned[max];
    for (unsigned i = 0; i < max; i++){
        temp[i] = NULL;
        tempx[i] = 0;
        tempy[i] = 0;
    }
    for (unsigned i = 0; i < small; i++){
        if(stickers_[i] != NULL){
            temp[i] = new Image(*stickers_[i]);
            tempx[i] = x_[i];
            tempy[i] = y_[i];
        }
    }

    for (unsigned i = 0; i < max_; i++){
        delete stickers_[i];
        stickers_[i] = NULL;
    }
    delete[] stickers_;
    stickers_ = NULL;
    delete[] x_;
    delete[] y_;

    stickers_ = temp;
    x_ = tempx;
    y_ = tempy;
    max_ = max;
}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    if (count_ >= max_){
        return -1;
    }
    else {
        for (unsigned i = 0; i <= count_; i++){
            if (stickers_[i] == NULL){
                stickers_[i] = new Image (sticker);
                x_[i] = x;
                y_[i] = y;
                count_ = count_ + 1;
                return i;
            }
        }
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (stickers_[index] == NULL || index >= max_){
        return false;
    }
    x_[index] = x;
    y_[index] = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index){
    if (index >= max_ || stickers_[index] == NULL){
        return;
    }
    else {
        delete stickers_[index];
        stickers_[index] = NULL;
        count_ = count_ - 1;
    }
    return;
}

Image* StickerSheet::getSticker(unsigned index) const{
    return stickers_[index];
}

Image StickerSheet::render() const{
    unsigned int maxx, maxy;
    maxx = width_;
    maxy = height_;
    for (unsigned i = 0; i < max_; i++){
        if (stickers_[i] != NULL){
            if ((stickers_[i]->width() + x_[i]) > maxx){
                maxx = stickers_[i]->width() + x_[i];
            }
            if ((stickers_[i]->height() + y_[i]) > maxy){
                maxy = stickers_[i]->height() + y_[i];
            }
        }

    }
    Image output = Image(maxx, maxy);
    for (unsigned x = 0; x < base->width(); x++){
        for(unsigned y = 0; y < base->height(); y++){
            cs225::HSLAPixel & pixel = output.getPixel(x,y);
            cs225::HSLAPixel & basepixel = base->getPixel(x,y);
            pixel.h = basepixel.h;
            pixel.s = basepixel.s;
            pixel.l = basepixel.l;
            pixel.a = basepixel.a;
        }
    }
    if (count_ == 0){
      return output;
    }
    for (unsigned i = 0; i < max_; i++){
        if (stickers_[i] != NULL){
            for (unsigned x = 0; x < stickers_[i]->width(); x++){
                for(unsigned y = 0; y < stickers_[i]->height(); y++){
                    unsigned cordx = x_[i] + x;
                    unsigned cordy = y_[i] + y;
                    cs225::HSLAPixel & pixel = output.getPixel(cordx, cordy);
                    cs225::HSLAPixel & basepixel = stickers_[i]->getPixel(x,y);
                    if (basepixel.a != 0){
                        pixel.h = basepixel.h;
                        pixel.s = basepixel.s;
                        pixel.l = basepixel.l;
                        pixel.a = basepixel.a;
                    }
                }
            }
        }
    }
    return output;
}
void StickerSheet::Copy(const StickerSheet & other){
    std::cout<<"deleting"<<std::endl;
    for (unsigned i = 0; i < max_; i++){
        std::cout<<"if statement"<<std::endl;
       if (stickers_[i] != NULL){
           std::cout<<"deleting sticker_[i]"<<std::endl;
           delete stickers_[i];
           stickers_[i] = NULL;
        }
    }
    std::cout<<"deleting arrays"<<std::endl;
    delete[] stickers_;
    stickers_ = NULL;
    delete[] x_;
    delete[] y_;
    delete base;
    std::cout<<"deleted"<<std::endl;
    width_ = other.width_;
    height_ = other.height_;
    max_ = other.max_;
    count_ = other.count_;
    base = other.base;
    std::cout<<"variables"<<std::endl;
    stickers_ = new Image*[max_];
    x_ = new unsigned[max_];
    y_ = new unsigned[max_];
    for (unsigned i = 0; i < max_; i++){
        *(stickers_ + i) = NULL;
        x_[i] = 0;
        y_[i] = 0;
    }
    for (unsigned i = 0; i < max_; i++){
        if (other.stickers_[i] != NULL){
            stickers_[i] = new Image;
            *stickers_[i] = *(other.stickers_[i]);
            x_[i] = other.x_[i];
            y_[i] = other.y_[i];

        }
    }
    std::cout<<"copy is fine yo"<<std::endl;
}
