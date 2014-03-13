#include "Vector3.h"

#ifndef VECTOR4_H
#define VECTOR4_H


class Vector4 : public IVector
{
    public:
        virtual Vector4 Cross(Vector4);
        virtual IVector Normalize();
        Vector4 operator* (int);
        Vector4 operator* (float);
        Vector4 operator* (const Vector4&);
        Vector4 operator+ (const Vector4&);
        Vector4 operator- (const Vector4&);
        float x;
        float y;
        float z;
        float w;
    private:
};

#endif
