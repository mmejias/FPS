//Followed: www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

class Level
{
    public:
        Level(const char*);
        ~Level();
        //bool loadObj(const char*, std::vector< glm::vec3 >&, std::vector< glm::vec2 >&, std::vector< glm::vec3 >&); 
        bool loadObj(const char*); 
        void draw();
        void update();
    private:
//        float* vertices;
        std::vector < glm::vec3 > vertices;
        std::vector < glm::vec2 > uvs;
        std::vector < glm::vec3 > normals;
};

Level::Level(const char* path)
{
  //  vertices = new float[4];
  loadObj(path);
}

Level::~Level()
{
    //delete [] vertices;
}

void Level::draw()
{
    /*
     * 
    glClear( GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(0, 1, 0);
    glEnd();
    */
    /*
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lightpos[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    Sphere sphere;
    sphere.draw();

    
    glClear( GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(0, 1, 0);
    glEnd();
    */

   //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices, GL_STATIC_DRAW);
  
    //glClear( GL_COLOR_BUFFER_BIT );
    //glEnable(GL_DEPTH_TEST);
    //glDisable(GL_LIGHTING);
    //glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0, 1.0f);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, 100.0f);
        glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
 
}

/*
bool Level::loadObj(const char* path,
                    std::vector< glm::vec3 >& out_vertices,
                    std::vector< glm::vec2 >& out_uvs,
                    std::vector< glm::vec3 >& out_normals)
*/
bool Level::loadObj(const char* path)
{
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    FILE * file = fopen(path, "r");
    if(file == NULL ) 
    {
        printf("Could not open file. Error!\n");
        return false;    
    }
    while(1)
    {
        char lineHeader[128];

        //Read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if(strcmp( lineHeader, "v" ) == 0)
        {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }
        else if( strcmp( lineHeader, "vt" ) == 0)
        {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }
        else if( strcmp (lineHeader, "vn" ) == 0)
        {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if ( strcmp(lineHeader, "f" ) == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            
            if(matches != 9)
            {
                printf("File can't be ready by Level Loader: Try re-exporting Level Model\n");
                return false;
            }
        
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
        uvIndices    .push_back(uvIndex[0]);
        uvIndices    .push_back(uvIndex[1]);
        uvIndices    .push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
        }

        for(unsigned int i = 0; i < vertexIndices.size(); ++i)
        {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex-1];
            vertices.push_back(vertex);
        }
    }
} 
