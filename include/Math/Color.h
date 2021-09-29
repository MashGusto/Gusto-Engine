#pragma once

/**
 * A container to hold color values..
 */

class Color
{
  private:
    float m_r, m_g, m_b, m_a;
  public:
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    float getRed();
    float getGreen();
    float getBlue();
    float getAlpha();
    float& operator[](int index);
};
