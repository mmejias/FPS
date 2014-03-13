#ifndef VECTOR3_H
#define VECTOR3_H

class IVector
{
    public:
        virtual IVector Cross(IVector);
        virtual IVector Normalize();
};

class Vector3 : public IVector
{
    public:
        virtual Vector3 Cross(Vector3);
        virtual IVector Normalize();
        Vector3 operator* (int);
        Vector3 operator* (float);
        Vector3 operator* (const Vector3&);
        Vector3 operator+ (const Vector3&);
        Vector3 operator- (const Vector3&);
        int getSize();
        float x;
        float y;
        float z;
   private:
        int size;
};


#endif
