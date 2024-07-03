//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#include "Edge.hpp"

//to create edge we need its id and its 2 vertices
Edge::Edge(int id, Vertex* vertex1, Vertex* vertex2) : id(id), owner(nullptr), istaken(false), vertex1(vertex1), vertex2(vertex2) {}

//return id of the edge
int Edge::getId() const {
    return id;
}
//get and set owner of the edge
Player* Edge::getOwner() const {
    return owner;
}
void Edge::setOwner(Player* player) {
    owner = player;
    istaken = true;
}

bool Edge::getIsTaken() {
    return istaken;
}//check if the edgge already taken
//return the verticees of the edge
 Vertex* Edge::getVertex1()  {
    return vertex1;
}
 Vertex* Edge::getVertex2()  {
    return vertex2;
}

//function to check if this edge is adjecancy to other edge
bool Edge::isAdjacent(Edge* other)  {
    if (this == other) {
        return false; // same edge, not adjacent
    }
    //if they have 1 matual vertex they are adjecancy
    return (vertex1 == other->vertex1 || vertex1 == other->vertex2 ||
            vertex2 == other->vertex1 || vertex2 == other->vertex2);
}
