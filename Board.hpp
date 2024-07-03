//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Hexagon.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"

class Board {
public:
    Board();

    std::vector<Hexagon>& getHexagons();
     std::vector<Vertex>& getVertices() ;
     std::vector<Edge>& getEdges() ;

    void printBoard() const;

private:
    std::vector<Hexagon> hexagons;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    //init hexagons, vertices, edges
    void initializeHexagons();
    void initializeVertices();
    void initializeEdges();
    //add the edges to each vertex
    void addEdgesToVertices();
    //add vertices and edges to hexagons
    void addVerticesAndEdgesToHexagons();
    //init board
    void initializeBoard();

};

#endif // BOARD_HPP
