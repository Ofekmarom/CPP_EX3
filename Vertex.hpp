//ID : 208336701
//MAIL : ofekmarom9@gmail.com


#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include "Hexagon.hpp"


class Player;

using namespace std;
class Vertex {
public:
    enum Building { None, Settlement, City };

    Vertex(int id);
            //all the explaining of this methods are in vertex.cpp
    int getId() const;
    Building getBuilding() const;
    Player* getOwner();
    void setBuilding(Building bldg, Player* player);
    bool getIsTaken();
    string getBuildingString();
    const vector<Vertex*>& getAdjacentVertices() const;
    void addAdjacentVertex(Vertex* vertex);
    const vector<Edge*>& getEdges() const;
    void addEdge(Edge* edge);
    bool checkAdjective(Vertex& vertex);
    const std::vector<Hexagon*>& getAdjacentHexagons() const;
    void addAdjacentHexagon(Hexagon* hexagon);


private:
    //vertex have: id,owner,building,istaken,adjacentVertices,edgesOfVertex,adjacentHexagons
    int id;
    Player* owner;
    Building building;
    bool istaken;
    vector<Vertex*> adjacentVertices;
    vector<Edge*> edgesOfVertex;
    vector<Hexagon*> adjacentHexagons;


};

#endif // VERTEX_HPP
