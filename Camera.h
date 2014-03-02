#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

//First Person Camera
class FPCamera
{
    public:
        FPCamera();
        void init(glm::vec3 playerPosition, glm::vec3 m_verticalOffset, glm::vec3 m_targetOffset);
        void update(float yaw, float pitch, glm::vec3);
    protected:
        glm::vec3 eye;
        glm::vec3 target;
        glm::vec3 verticalOffset;
        glm::vec3 targetOffset;
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
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    gluLookAt(eye.x, eye.y, eye.z, 
              target.x, target.y, target.z, 
              up.x, up.y, up.z);
}
float clamp(float, float, float);

void FPCamera::update(float yaw, float pitch, glm::vec3 position)
{
    
    totalYaw += yaw;
    totalPitch += pitch;

    //totalPitch = clamp(totalPitch, 0.78f, -0.78f);
    
    glm::vec3 actualOffset = targetOffset;
    glm::quat quatYaw = glm::angleAxis(glm::radians(totalYaw), actualOffset); 
    
    //actualOffset = Transform(actualOffset, quatYaw) is missing
    glm::vec3 forward = actualOffset;    
    forward = glm::normalize(forward);

    glm::vec3 left = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward);
    left = glm::normalize(left);

    glm::quat quatPitch = glm::angleAxis(glm::radians(totalPitch), actualOffset);
    
   

    eye = position + verticalOffset;
    target = eye + actualOffset;
    
    //New Code
    //eye = glm::cross(quatPitch, eye);
    //eye = quatPitch * eye;
    //target = quatYaw * target;
    //target = quatYaw * quatPitch * target;

    gluLookAt(eye.x, eye.y, eye.z, 
              target.x, target.y, target.z, 
              0, 1, 0);
    
}

float clamp(float totalPitch, float m_angle, float m_angle2)
{
    //while(toalPitch > m_angle && totalPitch < m_angle2)
    if(totalPitch > m_angle)
        return sin(totalPitch*m_angle);
    if(totalPitch < m_angle2)
        return -sin(totalPitch*m_angle2);

        return totalPitch;
}


