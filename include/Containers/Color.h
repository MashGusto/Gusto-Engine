#pragma once

/**
 * A container to hold color values..
 */

class Color
{
private:
  float r, g, b, a;

public:
  Color() {}
  Color(float r, float g, float b);
  Color(float r, float g, float b, float a);

  float getRed();
  float getGreen();
  float getBlue();
  float getAlpha();

  void setRed(float r);
  void setGreen(float g);
  void setBlue(float b);
  void setAlpha(float a);

  float &operator[](int index);
};
