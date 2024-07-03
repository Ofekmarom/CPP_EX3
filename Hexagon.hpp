//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#ifndef HEXAGON_HPP
#define HEXAGON_HPP
#include <string>
#include <vector>

class Vertex;
class Edge;

using namespace std;

class Hexagon {
public:
    //enums for type and resource type of hexagons
    enum HexagonType { Forest, Hills, PastureLand, AgriculturalLand, Mountains, Desert };
    enum ResourceType { Wood, Brick, Wool, Wheat, Ore, None };

    Hexagon(int id, HexagonType type, int number);

    int getId() const;
    ResourceType getResourceType() const;
    int getNumber() const;
    string getHexagonTypeString() ;
    string getResourceTypeString() ;
    static string getResourceTypeString(ResourceType type);

    const vector<Vertex*>& getVertices() const;
    const vector<Edge*>& getEdges() const;

    void addVertex(Vertex* vertex);
    void addEdge(Edge* edge);

private:
    //hexagon have:id,type,resourcetype,number,vertices,edges.
    int id;
    HexagonType hexType;
    ResourceType resourceType;
    int number;
    vector<Vertex*> vertices;
    vector<Edge*> edges;


    ResourceType typeToResource(HexagonType type) const;
};

#endif // HEXAGON_HPP
