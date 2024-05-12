#include "vector2.h"

Vector2::Vector2(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2::operator +(const Vector2& other)
{
    double resultX = x + other.x;
    double resultY = y + other.y;
    return Vector2(resultX, resultY);
}

Vector2::operator -(const Vector2& other)
{
    double resultX = x - other.x;
    double resultY = y - other.y;
    return Vector2(resultX, resultY);
}
