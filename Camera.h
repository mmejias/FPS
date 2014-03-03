#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)
#define PI 3.14159265f 

//First Person Camera
class FPCamera
{
    public:
        FPCamera();
        void init(glm::vec3 playerPosition, glm::vec3 m_verticalOffset, glm::vec3 m_targetOffset);
        glm::vec3 getEye();
        glm::vec3 getLeft();
        glm::vec3 getTarget();
        glm::vec3 getUp();
        void look();
        void setTarget(glm::vec3 projectedTarget);
        void update(float yaw, float pitch, glm::vec3);
    protected:
        glm::vec3 eye;
        glm::vec3 left;
        glm::vec3 target;
        glm::vec3 verticalOffset;
        glm::vec3 targetOffset;
        glm::vec3 up;
        glm::mat4 cameraMatrix;
        float totalYaw, totalPitch;
};

FPCamera::FPCamera()
{
    totalYaw = totalPitch = 0.0f;
}

void FPCamera::init(glm::vec3 m_position, glm::vec3 m_verticalOffset, glm::vec3 m_targetOffset)
{
    verticalOffset = m_verticalOffset;
    targetOffset = m_targetOffset;

    totalYaw = 0.0f;
    totalPitch = 0.0f;

    eye = m_position + verticalOffset;
    target = eye + targetOffset;
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    gluLookAt(eye.x, eye.y, eye.z, 
              target.x, target.y, target.z, 
              up.x, up.y, up.z);
}

float clamp(float, float, float);

glm::vec3 FPCamera::getEye()
{
    return eye;
}

glm::vec3 FPCamera::getLeft()
{
    return left;
}

glm::vec3 FPCamera::getTarget()
{
    return target;
}

glm::vec3 FPCamera::getUp()
{
    return up;
}

void FPCamera::setTarget(glm::vec3 projectedTarget)
{
   target = projectedTarget;
}

void FPCamera::update(float yaw, float pitch, glm::vec3 position)
{
    
    totalYaw += yaw;
    totalPitch += pitch;
    
//    totalPitch = clamp(totalPitch, 90.0f, -90.0f);
    
    glm::vec3 actualOffset = targetOffset;
    //glm::quat quatYaw = glm::angleAxis((totalYaw), actualOffset); 
    glm::quat quatYaw = glm::angleAxis((totalYaw), Y_AXIS); 
    
    actualOffset = quatYaw * actualOffset;
    //actualOffset = Transform(actualOffset, quatYaw) is missing
    glm::vec3 forward = actualOffset;    
    forward = glm::normalize(forward);

    left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    left = glm::normalize(left);
    
    //glm::quat quatPitch = glm::angleAxis((totalPitch), actualOffset);
    glm::quat quatPitch = glm::angleAxis((totalPitch), X_AXIS);
    
    actualOffset = quatPitch * actualOffset;

    eye = position + verticalOffset;
   // actualOffset = quatYaw * quatPitch * actualOffset;

    target = eye + actualOffset;
    
    
}

void FPCamera::look()
{
    gluLookAt(eye.x, eye.y, eye.z, 
              target.x, target.y, target.z, 
              0, 1, 0);
}

float clamp(float totalPitch, float m_angle, float m_angle2)
{
    //while(toalPitch > m_angle && totalPitch < m_angle2)
    if(totalPitch > m_angle)
        return totalPitch - m_angle;
    if(totalPitch < m_angle2)
        return totalPitch - m_angle2;

        return totalPitch;
}


