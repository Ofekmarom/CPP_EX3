//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#ifndef EDGE_HPP
#define EDGE_HPP

#include <vector>
#include "Vertex.hpp"

class Player;

class Edge {
public:
    Edge(int id, Vertex* vertex1, Vertex* vertex2);

    int getId() const;
    Player* getOwner() const;
    void setOwner(Player* player);
    bool getIsTaken();
     Vertex* getVertex1() ;
     Vertex* getVertex2() ;
    bool isAdjacent(Edge* other);//function to check if this edge is adjecancy to other edge


private:
    //edge have: id,owner,istaken,vertex1,vertex2.
    int id;
    Player* owner;
    bool istaken;
    Vertex* vertex1;
    Vertex* vertex2;
   ;
};

#endif // EDGE_HPP
