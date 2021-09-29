#pragma once

/**
 * A container to hold position/size/vertex values.
 */

class Vector2f
{
  private:
    float m_x, m_y;
  public:
    Vector2f();
    Vector2f(float x, float y);

    float getX();
    float getY();

    void setX(float x);
    void setY(float y);

    float getLength();
    
    Vector2f operator - ();
    Vector2f operator + (const Vector2f& addend);
    Vector2f operator - (const Vector2f& subtrahend);
    Vector2f& operator += (const Vector2f& addend);
    float& operator [] (int index);
};
