#include "Image.h"

Image::Image() {
    cs225::PNG();
}
void Image::lighten() {}
void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            getPixel(x, y).l += amount;
        }
    }

}

void Image::darken(){}
void Image::darken(double amount){}

void Image::saturate(){}
void Image::saturate(double amount){}

void Image::desaturate(){}
void Image::desaturate(double amount){}

void Image::grayscale(){}

void Image::rotateColor(double degrees){}

void Image::illinify(){}

void Image::scale(double factor){}
void Image::scale(unsigned w, unsigned h){}
