//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#include "Vertex.hpp"
#include "Player.hpp"

Vertex::Vertex(int id) : id(id), owner(nullptr), building(None),istaken(false) {}
//return id of the vertex
int Vertex::getId() const {
    return id;
}
//return building of the vertex
Vertex::Building Vertex::getBuilding() const {
    return building;
}
//return owner of the vertex
Player* Vertex::getOwner()  {
    return owner;
}
//return if the vertex is taken
bool Vertex::getIsTaken() {
    return istaken;
}
//set building on the vertex
void Vertex::setBuilding(Building build, Player* player) {
    building = build;
    owner = player;
    istaken = true;
}
//get adjacent vertices of the vertex
const vector<Vertex*>& Vertex::getAdjacentVertices() const {
    return adjacentVertices;
}
//add a vertex to the adjacent vertices of the vertex
void Vertex::addAdjacentVertex(Vertex* vertex) {
    adjacentVertices.push_back(vertex);
}
//get edges of the vertex
const vector<Edge*>& Vertex::getEdges() const {
    return edgesOfVertex;
}
//add edge to the vertex
void Vertex::addEdge(Edge* edge) {
    edgesOfVertex.push_back(edge);
}
//function to check if a vertex is adjacent to this vertex
bool Vertex::checkAdjective(Vertex &vertex) {
    for (Vertex* ver : adjacentVertices) {
        //check if one of the adjectives vertices have the same id as the vertex we want to check if he is adjective
        if (vertex.getId() == ver->getId()) {
            return true;
        }
    }
    return false;
}
//return a string represent the building on this vertex
string Vertex::getBuildingString() {
    switch (building) {
        case None: return "None";
        case Settlement: return "Settlement";
        case City: return "City";
        default: return "None";
    }
}

//get adjacent hexagons of the vertex
const vector<Hexagon*>& Vertex::getAdjacentHexagons() const {
    return adjacentHexagons;
}
//add hexagon to the adjacent hexagons of the vertex
void Vertex::addAdjacentHexagon(Hexagon* hexagon) {
    adjacentHexagons.push_back(hexagon);
}


