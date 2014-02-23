//This class allows cross product, dot product and vector operations
#include <cmath>

#define SQR(x) (x*x)
#define NULL_VECTOR FPVector3(0.0, 0.0, 0.0)

class FPVector3
{
    //This is a 3D Vector class
    public:
        FPVector3();
        FPVector3(float, float, float);
        FPVector3 operator+ (const FPVector3& other);
        FPVector3 operator- (const FPVector3& other);
        float operator* (const FPVector3& other);
        FPVector3 operator* (float);
        
        FPVector3 normalize();
        FPVector3 crossProduct(const FPVector3 other);
        float GetVectorLength();

        float getX();
        float getY();
        float getZ();
        void setX(float);
        void setY(float);
        void setZ(float);
    private:
        float x, y, z;
};

FPVector3::FPVector3()
{
    x = y = z = 0.0;
}

FPVector3::FPVector3(float m_x, float m_y, float m_z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

float FPVector3::getX()
{
    return x;
}

float FPVector3::getY()
{
    return y;
}

float FPVector3::getZ()
{
    return z;
}

void FPVector3::setX(float m_x)
{
    x = m_x;
}

void FPVector3::setY(float m_y)
{
    y = m_y;
}

void FPVector3::setZ(float m_z)
{
    z = m_z;
}

FPVector3 FPVector3::operator+ (const FPVector3& other)
{
    x = x + other.x;
    y = y + other.y;
    z = z + other.z;
}

FPVector3 FPVector3::operator- (const FPVector3& other)
{
    x = x - other.x;
    y = y - other.y;
    z = z - other.z;
}

float FPVector3::operator* (const FPVector3& other)
{
    return x*other.x+y*other.y+z*other.z;
}

FPVector3 FPVector3::operator* (float scale)
{
    x = x*scale;
    y = y*scale;
    z = z*scale;
}

FPVector3 FPVector3::crossProduct(const FPVector3 other)
{
    FPVector3 res;
    float newx, newy, newz;
    
    newx =  y*other.z - z*other.y;
    newy =  z*other.x - x*other.z;
    newz =  x*other.y - y*other.x;
    res.setX(newx);
    res.setY(newy);
    res.setZ(newz);
    
    return res;
}

float FPVector3::GetVectorLength()
{
    return sqrt(SQR(x)+SQR(y)+SQR(z));
}

FPVector3 FPVector3::normalize()
{
    FPVector3 res;
    float l = GetVectorLength();
    if(l == 0.0) return NULL_VECTOR;
    
    res.setX(x/l);
    res.setY(y/l);
    res.setZ(z/l);
    
    return res;
}
