#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <algorithm>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>
#include "../Level.h"
#include "Node.h"

bool isGoal(Node current, Node goal)
{
    if((current.getPosition().x - goal.getPosition().x) <= 5 &&
       (current.getPosition().x - goal.getPosition().x) >  0 &&
       (current.getPosition().y - goal.getPosition().y) <= 5 &&
       (current.getPosition().y - goal.getPosition().y) >  0 &&
       (current.getPosition().z - goal.getPosition().z) <= 5 &&
       (current.getPosition().z - goal.getPosition().z) >  0 )
        return true;
    else
        return false;    
}

bool isAdjacent(Node current, Node next)
{
    if(std::fabs(current.getPosition().x - next.getPosition().x) > 5 ||
       std::fabs(current.getPosition().x - next.getPosition().x) == 0)
        return false;
    if(std::fabs(current.getPosition().y - next.getPosition().y) > 5 ||
       std::fabs(current.getPosition().y - next.getPosition().y) == 0)
        return false;
    if(std::fabs(current.getPosition().z - next.getPosition().z) > 5 ||
       std::fabs(current.getPosition().z - next.getPosition().z) == 0)
        return false;

    return true;
}

float calculateHn(Node current, Node goal)
{
    float dx = fabs(current.getPosition().x - goal.getPosition().x);
    float dy = fabs(current.getPosition().y - goal.getPosition().y);
    float dz = fabs(current.getPosition().z - goal.getPosition().z);
    
    return 100.0f * sqrt(dx * dx + dy * dy + dz * dz);       
}

void addCloseList(std::vector<Node>& closelist, Node current)
{
    if(closelist.empty())
    {
        current.visit();
        closelist.push_back(current);
    }
    else
    {
        if(current > closelist.back())
        {
            closelist.pop_back();
            closelist.push_back(current);
        }
        if(closelist.back() > current && isAdjacent(closelist.back(), current))
        {
            closelist.push_back(current);
        }
    }
}

void checkSuccessors(Node* successors, 
                     std::vector<Node>& openlist, 
                     std::vector<Node>& closelist,
                     Node current,
                     Node goal)
{
    for(unsigned int i = 0; i < 8; ++i)
    {
        successors[i].setG(current.getF()+10);
        successors[i].setH(calculateHn(successors[i], goal));
        successors[i].calculateFn();

        for(unsigned int j = 0; j < openlist.size(); ++j)
        {
            if(successors[i] == openlist[j] && successors[i].isVisited())
                if(openlist[j] >= successors[i])
                    successors[i].unvisit();
        }

        for(unsigned int k = 0; k < closelist.size(); ++k)
        {
            if(successors[i] == closelist[k] && successors[i].isVisited())
                if(closelist[k] >= successors[i])
                    successors[i].unvisit();
        }

        for(unsigned int j = 0; j < openlist.size(); ++j)
        {
            if(successors[i] == openlist[j] && successors[i].isVisited())
            {
                openlist.erase(openlist.begin()+j, openlist.begin()+j+1);
            }

            make_heap(openlist.begin(), openlist.end());
        }

        make_heap(openlist.begin(), openlist.end());

        if(successors[i].isVisited())
        {
            openlist.push_back(successors[i]);
            push_heap(openlist.begin(), openlist.end());
        }

        successors[i].unvisit();
    }
}

void generateSuccessors(bool& pathsGenerated,
                        Node current,
                        Node* successors,
                        Level* level)
{
    float x = current.getPosition().x;
    float y = current.getPosition().y;
    float z = current.getPosition().z;
    
    successors[0].setPosition(glm::vec3(x-5.0f, y, z-5.0f));
    successors[1].setPosition(glm::vec3(x-5.0f, y, z));
    successors[2].setPosition(glm::vec3(x, y, z-5.0f));
    successors[3].setPosition(glm::vec3(x+5.0f, y, z+5.0f));
    successors[4].setPosition(glm::vec3(x+5.0f, y, z));
    successors[5].setPosition(glm::vec3(x, y, z+5.0f));
    successors[6].setPosition(glm::vec3(x-5.0f, y, z+5.0f));
    successors[7].setPosition(glm::vec3(x+5.0f, y, z-5.0f));        
    
    for(unsigned int i = 0; i < 8; ++i)
        successors[i].visit();

    pathsGenerated = true;
}

void sendPath(std::vector<glm::vec3>& path, std::vector<Node>& closelist)
{
    for(unsigned int i = 0; i < closelist.size(); ++i)
        path.push_back(closelist[i].getPosition());
}

void findPath(std::vector<glm::vec3> &path, glm::vec3 m_start, glm::vec3 m_end, Level* level)
{
    bool pathsGenerated = false;

    Node start(m_start);
    Node goal(m_end);
    Node current;
    Node successors[8];
    Node next_state;
    std::vector<Node> openlist, closelist;

    //Push start on the openlist
    path.clear();
    openlist.push_back(start);
    std::make_heap(openlist.begin(), openlist.end());

    //While the openlist contains nodes to search
    //Perform A* Search algorithm
    
    while(!openlist.empty())
    {
        current = openlist.front();
        pop_heap(openlist.begin(), openlist.end());
        openlist.pop_back();

        //If current equals goal, then print the path and exit the search
        if(isGoal(current, goal))
        {
            closelist.push_back(goal);
            sendPath(path, closelist);
            closelist.clear();
            openlist.clear();
            return;
        }

        generateSuccessors(pathsGenerated, current, successors, level);
        checkSuccessors(successors, openlist, closelist, current, goal);

        //Add node current to close list
        addCloseList(closelist, current);

        //Reset condition if successors are found
        pathsGenerated = false;
    }

    openlist.clear();
    closelist.clear();
    return;
}


void constructPatrol(std::vector<glm::vec3>& patrol, glm::vec3 start)
{
    patrol.push_back(start);
    for(float i = 1; i <= 10; ++i)
    {
        start.x += 1;
        patrol.push_back(start);
    }
    for(float i = 1; i <= 10; ++i)
    {
        start.z += 1;
        patrol.push_back(start);
    }
    for(float i = 1; i <= 10; ++i)
    {
        start.x -= 1;
        patrol.push_back(start);
    }
    for(float i = 1; i <= 10; ++i)
    {
        start.z -= 1;
        patrol.push_back(start);
    }
}

#endif
