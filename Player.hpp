//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <map>
#include "Catan.hpp"
#include "Board.hpp"
#include "Hexagon.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "DevelopmentCard.hpp"


class Catan;
using namespace std;

class Player {      //full explanations of the methods in player.cpp
public:
    Player(const string& name);

    const string& getName() const;
    int getVictoryPoints() const;
    int getnumOfResources();
    int getnumOfKnights();


    void rollDice(Catan& catan);
    void startTurn();
    void endTurn(Catan& catan);
    bool getMyTurn();
    bool getIsLargestArmy();

        //resources
    void addResource(Hexagon::ResourceType type, int amount);
    void removeResource(Hexagon::ResourceType type, int amount);
    int getResourceAmount(Hexagon::ResourceType type);
    map<Hexagon::ResourceType, int>& getResources();
    bool hasResources( map<Hexagon::ResourceType, int>& cost) ;


        //buildings
    void buildStartingSettlement(int vertexId, Board* board);
    void buildStartingRoad(int edgeId, Board* board);

    void buildSettlement(int vertexId, Board* board);
    void buildRoad(int edgeId, Board* board);
    void buildCity(int vertexId, Board* board);



        //development cards
    void buyDevelopmentCard(Catan& catan);
    void useDevelopmentCard(DevelopmentCard::Type type, Catan& catan);
         //helper functions for use development card
    Hexagon::ResourceType chooseMinResource();
    int chooseEdgeForRoadBuild(Board* board);

        //getters
    vector<Vertex*> getSettlements();
    vector<DevelopmentCard> getDevelopmentCards();
    vector<Edge*> getRoads();
    vector<Vertex*> getCities();






    //trades
    void tradeResources(Player* other, Hexagon::ResourceType giveResourceType, int giveAmount, Hexagon::ResourceType receiveResourceType, int receiveAmount);

    void tradeDevelopmentCards(Player* other, DevelopmentCard::Type giveCardType, DevelopmentCard::Type receiveCardType);





private:
    string name;
    bool myTurn;
    bool alreadyRolled;
    int victoryPoints;
    int numOfResources;
    int numOfKnights;
    bool largestArmy;
    map<Hexagon::ResourceType, int> resources;
    vector<Vertex*> settlements;
    vector<Vertex*> cities;
    vector<Edge*> roads;
    vector<DevelopmentCard> developmentCards;




    void addVictoryPoint();
    void removeVictoryPoint();
    void addKnight();
    void removeKnight();
    void checkArmy();

};

#endif // PLAYER_HPP
