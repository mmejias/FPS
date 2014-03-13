#include "Vector3.h"

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2
{
    public:
        virtual Vector2 Cross(Vector2);
        virtual IVector Normalize();
        Vector2 operator* (int);
        Vector2 operator* (float);
        Vector2 operator* (const Vector2&);
        Vector2 operator+ (const Vector2&);
        Vector2 operator- (const Vector2&);
        int getSize();
        float x;
        float y;
    private:
        int size;
};

#endif 
