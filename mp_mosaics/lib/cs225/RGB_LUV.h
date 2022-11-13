#pragma once

#include <cmath>

//#include "ColorSpace/Conversion.h"
#include "ColorSpace/ColorSpace.h"
//#include "Comparison.h"
//#include "Utils.h"

#include <iostream>

namespace cs225 {
  typedef struct {
    double r, g, b, a; // [0, 255]
  } rgbaColor;

  typedef struct {
    double l;  // [0, 1]
    double u;  // [0, 1]
    double v;  // [0, 1]
    double a;  // [0, 1]
  } luvaColor;

  static luvaColor rgb2luv(rgbaColor rgb) {
    ColorSpace::Rgb cs_rgb(rgb.r, rgb.g, rgb.b);

    //std::cout << "cs_rgb: " << cs_rgb.r << " " << cs_rgb.g << " " << cs_rgb.b << std::endl;

    ColorSpace::Luv cs_luv;
    cs_rgb.To<ColorSpace::Luv>(&cs_luv);

    //std::cout << "cs_luv: " << cs_luv.l << " " << cs_luv.u << " " << cs_luv.v << std::endl;

    luvaColor luv;
    luv.l = cs_luv.l;
    luv.u = cs_luv.u;
    luv.v = cs_luv.v;
    luv.a = rgb.a / 255.0;

    //std::cout << luv.x << " " << luv.y << " " << luv.z << std::endl;

    return luv;
    

    /*
    double r, g, b, min, max, chroma;

    // Change rgb into [0, 1]
    r = rgb.r / 255.0;
    g = rgb.g / 255.0;
    b = rgb.b / 255.0;

    // Source: https://www.cs.rit.edu/~ncs/color/t_convert.html
    double x, y, z;
    x = 0.412453 * r  + 0.357580 * g + 0.180423 * b;
    y = 0.212671 * r  + 0.715160 * g + 0.072169 * b;
    z = 0.019334 * r  + 0.119193 * g + 0.950227 * b;


    double X = x, Y = y, Z = z;
    
    
    double Yn = 1;
    double u_ = 4*X / (X + 15*Y + 3*Z);
    double v_ = 9*Y / (X + 15*Y + 3*Z);
    double un_ = 0.2009;
    double vn_ = 0.461;

    double L_ =  116 * pow(Y/Yn, 1.0/3.0) - 16;
    double u_ =  13*L_ * ( u_ - un_ );
    double v_ =  13*L_ * ( v_ - vn_ );

    xyzaColor xyz;
    xyz.x = L_;
    xyz.y = u_;
    xyz.z = v_;


    // LAB
    double Xn = 0.9642, Yn = 1, Zn = 0.8249;

    double L_, a_, b_;

    if (Y/Yn > 0.008856) { L_ = 116 * pow(Y/Yn, 1.0/3.0) - 16; }
    else                 { L_ = 903.3 * Y/Yn; }
    a_ = 500 * ( f(X/Xn) - f(Y/Yn) );
    b_ = 200 * ( f(Y/Yn) - f(Z/Zn) );

    xyzaColor xyz;
    xyz.x = L_;
    xyz.y = a_;
    xyz.z = b_;
    xyz.a = rgb.a / 255.0;
    return xyz;
    */



  }

  static rgbaColor luv2rgb(luvaColor luv) {
    ColorSpace::Luv cs_luv(luv.l, luv.u, luv.v);
    ColorSpace::Rgb cs_rgb;
    cs_luv.To<ColorSpace::Rgb>(&cs_rgb);

    rgbaColor rgb;
    rgb.r = round(cs_rgb.r);
    rgb.g = round(cs_rgb.g);
    rgb.b = round(cs_rgb.b);
    rgb.a = round(luv.a * 255);
    return rgb;

    //double L_ = xyz.x, u = xyz.y, v = xyz.z;

    /*
    double L_ = xyz.x, a_ = xyz.y, b_ = xyz.z;
    double X, Y, Z;
    double Xn = 0.9642, Yn = 1, Zn = 0.8249;

    double P = (L_ + 16.0) / 116.0;
    X = Xn * pow(P + a_ / 500.0, 3);
    Y = Yn * pow(P, 3);
    Z = Zn * pow(P - b_ / 200.0, 3);
    */
    /*
    xyz.x = X;
    xyz.y = Y;
    xyz.z = Z;

    double r, g, b;
    r = 3.240479 * xyz.x + -1.537150 * xyz.y + -0.498535 * xyz.z;
    g = -0.969256 * xyz.x + 1.875992 * xyz.y + 0.041556 * xyz.z;
    b = 0.055648 * xyz.x + -0.204043 * xyz.y + 1.057311 * xyz.z;

    if      (r < 0) { r = 0; }
    else if (r > 1) { r = 1; }

    if      (g < 0) { g = 0; }
    else if (g > 1) { g = 1; }

    if      (b < 0) { b = 0; }
    else if (b > 1) { b = 1; }

    rgbaColor rgb;

    rgb.r = round(r * 255);
    rgb.g = round(g * 255);
    rgb.b = round(b * 255);
    rgb.a = round(xyz.a * 255);

    return rgb;
    */
  }
}