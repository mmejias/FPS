#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>

class Node
{
    public:
        Node();
        Node(glm::vec3);
        bool operator< (const Node&);
        bool operator> (const Node&);
        bool operator== (const Node&);
        bool operator>= (const Node&);
        bool operator<= (const Node&);
        bool operator!= (const Node&);
        Node& operator= (const Node&);
        bool isVisited();
        float getF();
        float getG();
        float getH();
        glm::vec3 getPosition();
        void calculateFn();
        void setF(float);
        void setG(float);
        void setH(float);
        void setPosition(glm::vec3);
        void unvisit();
        void visit();
    private:
        bool visited;
        float f;
        float g;
        float h;
        glm::vec3 position;
};

Node::Node()
{
    visited = false;
    f = 0.0f;
    g = 0.0f;
    h = 0.0f;
}

Node::Node(glm::vec3 m_position)
{
    visited = false;
    f = 0.0f;
    g = 0.0f;
    h = 0.0f;
    position = m_position;
}

bool Node::isVisited()
{
    return visited;
}

bool Node::operator< (const Node& that)
{
    return this->f > that.f;
}

bool Node::operator> (const Node& that)
{
    return this->f < that.f;
}

bool Node::operator== (const Node& that)
{
    return (this->position.x == that.position.x &&
            this->position.y == that.position.y &&
            this->position.z == that.position.z);
}

bool Node::operator>= (const Node& that)
{
    if(this->f < that.f)
        return true;
    else if(this->f == that.f)
        return true;
    else
        return false;
}

bool Node::operator<= (const Node& that)
{
    if(this->f > that.f)
        return true;
    else if (this->f == that.f)
        return true;
    else
        return false;
}

bool Node::operator!= (const Node& that)
{
    return !(this->position.x == that.position.x &&
             this->position.y == that.position.y &&
             this->position.z == that.position.z);
}

float Node::getF()
{
    return f;   //Cost to reach current
}

float Node::getG()
{
    return g;   //cost to next place
}

float Node::getH()
{
    return h;   //heuristic cost
}

glm::vec3 Node::getPosition()
{
    return position;
}

Node& Node::operator= (const Node& that)
{
    f = that.f;
    g = that.g;
    h = that.h;
    position = that.position;
    visited = that.visited;

    return *this;
}

void Node::setF(float m_f)
{
    f = m_f;
}

void Node::setG(float m_g)
{
    g = m_g;
}

void Node::setH(float m_h)
{
    h = m_h;
}

void Node::setPosition(glm::vec3 m_position)
{
    position = m_position;
}

void Node::calculateFn()
{
    f = g+h;
}

void Node::visit()
{
    visited = true;
}

void Node::unvisit()
{
    visited = false;
}

#endif
