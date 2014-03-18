#ifndef LEVEL_H
#define LEVEL_H

//Followed: www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

#include "Ground.h"

class Level
{
    public:
        Level(const char*);
        ~Level();
        bool loadObj(const char*); 
        void draw();
        void update();
    protected:
        Ground* ground;
    private:
        std::vector < glm::vec3 > vertices;
        std::vector < glm::vec2 > uvs;
        std::vector < glm::vec3 > normals;
};

Level::Level(const char* path)
{
    ground = new Ground();
}

Level::~Level()
{
    vertices.clear();
    uvs.clear();
    normals.clear();

}

void Level::draw()
{
    ground->draw();
}

bool Level::loadObj(const char* path)
{
    printf("Load Obj model file\n");
    return true;
}

#endif 
