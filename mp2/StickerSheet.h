/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"


class StickerSheet{
public:
  StickerSheet(const Image & picture, unsigned max);
  ~StickerSheet();
  StickerSheet(const StickerSheet &other);
  const StickerSheet & operator= (const StickerSheet & other);
  void changeMaxStickers (unsigned max);
  int addSticker (Image &sticker, unsigned x, unsigned y);
  bool translate (unsigned index, unsigned x, unsigned y);
  void removeSticker (unsigned index);
  Image* getSticker (unsigned index) const;
  Image render() const;
  void Copy(const StickerSheet & other);
private:
  unsigned width_;
  unsigned height_;
  unsigned max_;
  unsigned count_;
  Image** stickers_;
  Image* base;
  unsigned *x_;
  unsigned *y_;

};
