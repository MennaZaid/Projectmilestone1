#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
public:
    Vector2(double, double);

    Vector2 operator+(const Vector2& other);
    Vector2 operator-(const Vector2& other);

    double x;
    double y;
};

#endif // VECTOR2_H
