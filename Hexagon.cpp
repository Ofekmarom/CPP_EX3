//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#include <string>
#include "Hexagon.hpp"
using namespace std;

//creating heexagon with id,type,number
Hexagon::Hexagon(int id, HexagonType type, int number) : id(id),hexType(type), resourceType(typeToResource(type)), number(number) {}
//return the id of this hexagon
int Hexagon::getId() const {
    return id;
}

//return the resource type of this hexagon
Hexagon::ResourceType Hexagon::getResourceType() const {
    return resourceType;
}
//return the number of this hexagon
int Hexagon::getNumber() const {
    return number;
}
//return the vertices of this hexagon
const std::vector<Vertex*>& Hexagon::getVertices() const {
    return vertices;
}
//return the edges of this hexagon
const std::vector<Edge*>& Hexagon::getEdges() const {
    return edges;
}
//add vertex to the hexagon,its in the init of the board
void Hexagon::addVertex(Vertex* vertex) {
    vertices.push_back(vertex);
}
//add edge to the hexagon,its in the init of the board
void Hexagon::addEdge(Edge* edge) {
    edges.push_back(edge);
}
//function to get the resource type of this the type of hexagon
Hexagon::ResourceType Hexagon::typeToResource(HexagonType type) const {
    switch (type) {
        case Forest:
            return Wood;
        case Hills:
            return Brick;
        case PastureLand:
            return Wool;
        case AgriculturalLand:
            return Wheat;
        case Mountains:
            return Ore;
        case Desert:
        default:
            return None;
    }
}
//function to get the string representing the type of the hexagon
string Hexagon::getHexagonTypeString() {
    switch (hexType) {
        case Forest: return "Forest";
        case Hills: return "Hills";
        case PastureLand: return "Pasture Land";
        case AgriculturalLand: return "Agricultural Land";
        case Mountains: return "Mountains";
        case Desert: return "Desert";
        default: return "not in board";
    }
}
//function to get the string representing the resource type of the hexagon
string Hexagon::getResourceTypeString()  {
    switch (resourceType) {
        case Wood: return "Wood";
        case Brick: return "Brick";
        case Wool: return "Wool";
        case Wheat: return "Wheat";
        case Ore: return "Ore";
        case None: return "None";
        default: return "not in the game";
    }
}
//function to get the string representing the resource type of a type of hexagon without an hexagon instance
string Hexagon::getResourceTypeString(Hexagon::ResourceType type) {
        switch (type) {
            case Hexagon::Wood: return "Wood";
            case Hexagon::Brick: return "Brick";
            case Hexagon::Wool: return "Wool";
            case Hexagon::Wheat: return "Wheat";
            case Hexagon::Ore: return "Ore";
            case Hexagon::None: return "None";
            default: return "Unknown";
        }
}
