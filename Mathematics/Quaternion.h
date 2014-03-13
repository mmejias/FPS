#include "Vector3.h"
#include "Vector4.h"


#ifndef QUATERNION_H
#define QUATERNION_H


class Quaternion
{
    public:
        Quaternion();
        Vector3 operator* (Vector3); 
        float x;
        float y;
        float z;
        float w;
};

#endif
