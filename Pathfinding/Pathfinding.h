#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <algorithm>
#include <vector>
#include <glm/glm.hpp>
#include "../Level.h"
#include "Node.h"

bool isGoal(Node current, Node goal)
{
    
}

bool isAdjacent(Node current, Node next)
{

}

float calculateHn(Node current, Node goal)
{
    
}

void addCloseList(std::vector<Node>& closelist, Node current)
{

}

void checkSuccessors(Node* successors, 
                     std::vector<Node>& openlist, 
                     std::vector<Node>& closelist,
                     Node current,
                     Node goal)
{


}

void generateSuccessors(bool& pathsGenerated,
                        Node current,
                        Node* successors,
                        Level level)
{


}

void findPath(std::vector<glm::vec3> &path, glm::vec3 start, glm::vec3 finish)
{
}

#endif
