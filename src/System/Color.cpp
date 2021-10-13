#include "System/Color.h"

// Constructor for rgb values.
Color::Color(float R, float G, float B) : r(R), g(G), b(B), a(1.f) {}

// Constructor for rgba values.
Color::Color(float R, float G, float B, float A) : r(R), g(G), b(B), a(A) {}

// Get the r value of the color.
float Color::getRed() { return r; }

// Get the g value of the color.
float Color::getGreen() { return g; }

// Get the b value of the color.
float Color::getBlue() { return b; }

// Get the a value of the color.
float Color::getAlpha() { return a; }

// Set the r value of the color.
void Color::setRed(float R) { r = R; }

// Set the g value of the color.
void Color::setGreen(float G) { g = G; }

// Set the b value of the color.
void Color::setBlue(float B) { b = B; }

// Set the a value of the color.
void Color::setAlpha(float A) { a = A; }

// Overloads the subscript([]) operator to return the color values according to index.
float &Color::operator[](int index)
{
  if (index == 1)
    return r;
  else if (index == 2)
    return g;
  else if (index == 3)
    return b;
  else
    return a;
}
