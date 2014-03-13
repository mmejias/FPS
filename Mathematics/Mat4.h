#include "Vector3.h"
#include "Vector4.h"

#ifndef MAT4_H
#define MAT4_H

class Mat4
{
    public:
        Mat4();
        Mat4(Vector4, Vector4, Vector4);
    private:
        float elements[16];
};

#endif 
