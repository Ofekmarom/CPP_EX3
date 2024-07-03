//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#include "Player.hpp"
#include "Hexagon.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>



Player::Player(const std::string& name) : name(name),myTurn(false) ,alreadyRolled(false),victoryPoints(0),numOfResources(0), numOfKnights(0), largestArmy(false) {
    resources = {
            {Hexagon::Wood, 0}, {Hexagon::Brick, 0}, {Hexagon::Wool, 0}, {Hexagon::Wheat, 0}, {Hexagon::Ore, 0}
    };
}
//returns the name of the player
const std::string& Player::getName() const {
    return name;
}
//retuurn if this is the turn of the player
bool Player::getMyTurn() {
    return myTurn;
}

//function to start the player turn
void Player::startTurn() {
    myTurn = true;
    alreadyRolled = false;
}
//function to end the player turn and it will start the next player turn
void Player::endTurn(Catan& catan) {
    if (!myTurn){
        throw std::runtime_error(getName() + ", you cant end the turn, its not your turn");
    }
    cout << getName() << " just finished his turn!" <<endl;
    catan.nextPlayer();
    myTurn = false;
    alreadyRolled = false;
    cout << catan.getCurrentPlayer()->getName() << " turn, start to play!!!!!!!" <<endl;
}
//add 1 to the victory points of the player
void Player::addVictoryPoint() {
    victoryPoints++;
}
//remove 1 from the victory points of the player
void Player::removeVictoryPoint() {
    victoryPoints--;
}
//return the victory points of the player
int Player::getVictoryPoints() const {
    return victoryPoints;
}
//return the number of resources of the player
int Player::getnumOfResources() {
    return numOfResources;
}

//return the number of knights of the player
int Player::getnumOfKnights() {
    return numOfKnights;
}
//add 1 knight to the player
void Player::addKnight() {
    numOfKnights++;
    this->checkArmy();
}
//remove 1 knight from the player
void Player::removeKnight() {
    numOfKnights--;
    this->checkArmy();
}
//function to check if there is update on the largest army
void Player::checkArmy() {
    //if not currently largest army and have 3 knights he is now the largest army
    if (!largestArmy) {
        if (numOfKnights == 3) {
            largestArmy = true;
            addVictoryPoint();
            addVictoryPoint();
        }
    }
    else {//if currently he have the largest army and dont have 3 knights he is not the largest army anymore
        if (numOfKnights != 3) {
            largestArmy = false;
            removeVictoryPoint();
            removeVictoryPoint();
        }
    }
}

//function to roll the dice
void Player::rollDice(Catan& catan) {
    if (!myTurn){
        throw std::runtime_error(getName() + ", you cant roll the dice now, its not your turn");
    }
    if(alreadyRolled){
        throw std::runtime_error(getName() + ", you cant roll the dice now, you already rolled for your turn");
    }
    catan.rollDice(); // call Catans rollDice method
    alreadyRolled = true;
}

//add resource
void Player::addResource(Hexagon::ResourceType type, int amount) {
    resources[type] += amount;
    numOfResources += amount;
}
//remove resource
void Player::removeResource(Hexagon::ResourceType type, int amount) {
    if (resources[type] < amount) {
        throw std::runtime_error(getName() + ", you cant remove this amount of resource, the amount is bigger than what you have");
    }
    resources[type] -= amount;
    numOfResources -= amount;
}
//check if the player have this resources
bool Player::hasResources( map<Hexagon::ResourceType, int>& price)  {
    //loop to go over each element in the map of resources
    for ( auto& resource : price) {
        Hexagon::ResourceType resourceType = resource.first;  // get the resource type of the price
        int requiredAmount = resource.second;                 // get the amount we need from this resource
        //handle the case of resourceType none of the desert
        if(resourceType == Hexagon::None)
        {
            continue;
        }
        // check if the player has less of that resource than the amount he need
        if (resources.at(resourceType) < requiredAmount) {
            return false; // if he dont have enough from this resource, return false
        }
    }
    return true; // if he have enough from all the resources , return true
}
//return the amount of resource a player have from specific resource type
int Player::getResourceAmount(Hexagon::ResourceType type) {
    return resources[type];
}

//return a map of all the resources of the player
map<Hexagon::ResourceType, int> &Player::getResources() {
    return resources;
}

//return vector of vertices that every vertex is a settlement of the player
vector<Vertex *> Player::getSettlements() {
    return settlements;
}


    //building!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//build starting settlement
void Player::buildStartingSettlement(int vertexId, Board* board) {
    //invalid id of vertex
    if (vertexId <1 || vertexId > 54){
        throw std::runtime_error(getName() + ", you cant build settlement, this vertex not in the board!");
    }
    Vertex* vertex = &board->getVertices()[static_cast<unsigned long>(vertexId - 1)];
    //if vertex already taken
    if (vertex->getBuilding() != Vertex::None) {
        throw std::runtime_error(getName() +", you cant place settlement here, vertex already tafus");
    }

    // check if all adjacent vertices are free
    const vector<Vertex*>& adjacentVertices = vertex->getAdjacentVertices();
    for (Vertex* adjVertex : adjacentVertices) {
        if (adjVertex->getBuilding() != Vertex::None) {
            throw std::runtime_error(getName() + ", you cant place a settlement here, there isnt a distance of 2 edges minimum from other building");
        }
    }

    //iff pass all until now he can place a starting settlement

    vertex->setBuilding(Vertex::Settlement, this);
    settlements.push_back(vertex);
    addVictoryPoint();
    cout << getName() << " successfully built a starting settlement on vertex ID : " << vertexId << endl;

}

//build starting road
void Player::buildStartingRoad(int edgeId, Board* board) {
    //invalid id of edge
    if (edgeId <1 || edgeId > 72){
        throw std::runtime_error(getName() + ", you cant build road, this edge not in the board!");
    }
    Edge* edge = &board->getEdges()[static_cast<unsigned long>(edgeId - 1)];
    //if edge already taken
    if (edge->getOwner() != nullptr) {
        throw std::runtime_error(getName() + ", you cant build a road, this edge already occupied");
    }
    bool canBuild = false;

    // check if one of the vertices has a building owned by this player
    if ((edge->getVertex1()->getOwner() == this || edge->getVertex2()->getOwner() == this)) {
        canBuild = true;
    }
    // check if this edge is adjacent to an edge this player have road on
    for (Edge* road : roads) {
        if (edge->isAdjacent(road)) {
            canBuild = true;
            break;
        }
    }
    if (!canBuild) {
        throw std::runtime_error(getName() + ", you cant build a road, its not by the rules of the format");
    }
    //if got here he is able to build starting road
    edge->setOwner(this);
    roads.push_back(edge);
    cout << getName() << " successfully built a starting road on edge ID : " << edgeId << endl;
}

//build starting settlement
void Player::buildSettlement(int vertexId, Board* board) {
    //check if its his turn
    if (!getMyTurn()){
        throw std::runtime_error(getName() + ", you cant build settlement, its not your turn!");
    }
    //invalid id of vertex
    if (vertexId <1 || vertexId > 54){
        throw std::runtime_error(getName() + ", you cant build settlement, this vertex not in the board!");
    }
    Vertex* vertex = &board->getVertices()[static_cast<unsigned long>(vertexId - 1)];
    //if vertex already taken
    if (vertex->getBuilding() != Vertex::None) {
        throw std::runtime_error(getName() +", you cant place settlement here, vertex already tafus");
    }

    // check if all adjacent vertices are free
    const vector<Vertex*>& adjacentVertices = vertex->getAdjacentVertices();
    for (Vertex* adjVertex : adjacentVertices) {
        if (adjVertex->getBuilding() != Vertex::None) {
            throw std::runtime_error(getName() + ", you cant place a settlement here, there isnt a distance of 2 edges minimum from other building");
        }
    }

    // check if the player has a road connected to this vertex
    bool hasConnectedRoad = false;
    for (Edge* road : roads) {
        if (road->getVertex1() == vertex || road->getVertex2() == vertex) {
            hasConnectedRoad = true;
            break;
        }
    }
    //if dont have road connected to where he want to build
    if (!hasConnectedRoad) {
        throw std::runtime_error(getName() + ", you cant place a settlement here, there is no connected road to the vertex you want to build settlement on");
    }

    std::map<Hexagon::ResourceType, int> price = {
            {Hexagon::Wood, 1},
            {Hexagon::Brick, 1},
            {Hexagon::Wool, 1},
            {Hexagon::Wheat, 1}
    };
    //check if he have the resources he need in order to build settlement
    if (!hasResources(price)) {
        throw std::runtime_error(getName() + ", you cant place settlement, you dont have enough resources");
    }

    //iff pass all until now he can place a settlement
    //pay for the building
    for (auto& resourceAndAmount : price) {
        removeResource(resourceAndAmount.first, resourceAndAmount.second);
    }
    vertex->setBuilding(Vertex::Settlement, this);
    settlements.push_back(vertex);
    addVictoryPoint();
    cout << getName() << " successfully built a settlement on vertex ID : " << vertexId << endl;
}

//build road
void Player::buildRoad(int edgeId, Board* board) {
    //check if its his turn
    if (!getMyTurn()){
        throw std::runtime_error(getName() + ", you cant build road, its not your turn!");
    }
    //invalid id of edge
    if (edgeId <1 || edgeId > 72){
        throw std::runtime_error(getName() + ", you cant build road, this edge not in the board!");
    }
    Edge* edge = &board->getEdges()[static_cast<unsigned long>(edgeId - 1)];
    //if edge already taken
    if (edge->getOwner() != nullptr) {
        throw std::runtime_error(getName() + ", you cant build a road, this edge already occupied");
    }
    bool canBuild = false;

    // check if one of the vertices has a building owned by this player
    if ((edge->getVertex1()->getOwner() == this || edge->getVertex2()->getOwner() == this)) {
        canBuild = true;
    }
    // check if this edge is adjacent to an edge this player have road on
    for (Edge* road : roads) {
        if (edge->isAdjacent(road)) {
            canBuild = true;
            break;
        }
    }
    //if cant build road throw exception
    if (!canBuild) {
        throw std::runtime_error(getName() + ", you cant build a road, its not by the rules of the format");
    }

    std::map<Hexagon::ResourceType, int> price = {
            {Hexagon::Wood, 1},
            {Hexagon::Brick, 1}
    };
    //if dont have enough resources for the road
    if (!hasResources(price)) {
        throw std::runtime_error("you cant build a road, not enough resources");
    }

    //iff pass all until now he can place a road
    //pay for road
    for (auto& resourceAndAmount : price) {
        removeResource(resourceAndAmount.first, resourceAndAmount.second);
    }

    edge->setOwner(this);
    roads.push_back(edge);
    cout << getName() << " successfully built a road on edge ID : " << edgeId << endl;
}


//build city
void Player::buildCity(int vertexId, Board* board) {
    //check if its his turn
    if (!getMyTurn()){
        throw std::runtime_error(getName() + ", you cant build city, its not your turn!");
    }
    //invalid id of vertex
    if (vertexId <1 || vertexId > 54){
        throw std::runtime_error(getName() + ", you cant build city, this vertex not in the board!");
    }

    Vertex* vertex = &board->getVertices()[static_cast<unsigned long>(vertexId - 1)];
    // check if the vertex has a settlement
    if (vertex->getBuilding() != Vertex::Settlement) {
        throw std::runtime_error(getName() + ", you cant build city, the vertex does not have a settlement to upgrade");
    }

    // check if the player is the owner of the settlement
    if (vertex->getOwner() != this) {
        throw std::runtime_error(getName() + ", you cant build city, you do not own the settlement on this vertex");
    }


    std::map<Hexagon::ResourceType, int> price = {
            {Hexagon::Ore, 3},
            {Hexagon::Wheat, 2}
    };
    //if dont have enough resources for the city
    if (!hasResources(price)) {
        throw std::runtime_error(getName() + ", you cant build city, you do not have enough resources");
    }

    //pay for the city
    for (auto& resourceAndAmount : price) {
        removeResource(resourceAndAmount.first, resourceAndAmount.second);
    }
    // remove vertex from settlements vector
    auto it = remove(settlements.begin(), settlements.end(), vertex);
    if (it != settlements.end()) {
        settlements.erase(it, settlements.end());
    }
    //set the city
    vertex->setBuilding(Vertex::City, this);
    cities.push_back(vertex);
    addVictoryPoint();
    cout << getName() << " successfully built a city on vertex ID : " << vertexId << endl;
}






         //development cards!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//buy development card
void Player::buyDevelopmentCard(Catan& catan) {
    //check if its his turn
    if (!getMyTurn()){
        throw std::runtime_error(getName() + ", you cant buy development card , its not your turn!");
    }

    // check if there are any development cards left in the deck
    if (catan.getDevelopmentCardsCatan().empty()) {
        throw std::runtime_error(getName() + ", you cant buy development card, no development cards left");
    }

    std::map<Hexagon::ResourceType, int> price = {
            {Hexagon::Ore, 1},
            {Hexagon::Wheat, 1},
            {Hexagon::Wool, 1}
    };
    //if dont have enough resources for the development card
    if (!hasResources(price)) {
        throw std::runtime_error(getName() + ", you cant buy development card, not enough resources");
    }

    //draw 1 card from the deck of the game
    DevelopmentCard card = catan.drawDevelopmentCard();
    developmentCards.push_back(card);
    cout << getName() << " bought this development card : " <<DevelopmentCard::typeToString(card.getType()) <<endl;
    //pay
    for (auto& resourceAndAmount : price) {
        removeResource(resourceAndAmount.first, resourceAndAmount.second);
    }
    //if got victory point card
    if (card.getType() == DevelopmentCard::VictoryPoint) {
        addVictoryPoint();
    }
    //if got knight card
    if (card.getType() == DevelopmentCard::Knight) {
        addKnight();
    }

}

//use development card
void Player::useDevelopmentCard(DevelopmentCard::Type type, Catan& catan) {
    //check if its his turn
    if (!getMyTurn()){
        throw std::runtime_error(getName() + ", you cant use development card , its not your turn!");
    }
    //check if he have the development card that he want to use
    auto it = std::find_if(developmentCards.begin(), developmentCards.end(),[type](DevelopmentCard& card) { return card.getType() == type; });
    //if he dont have the card throw exception
        if (it == developmentCards.end()) {
            throw std::runtime_error(getName() + ", you cant use this development card, you dont have it");
        }
        //handle the use of the development card based on its type
        switch (type) {
            //monopol card use (take all the players 1 resource type that he choose)
            case DevelopmentCard::Monopol: {
                //function that will choose the resource he have the least from
                Hexagon::ResourceType chosenResource = chooseMinResource();
                //function that will do the monopol card use
                catan.handleMonopol(*this, chosenResource);
                cout<< getName() << " used monopol card and now he have all the " << Hexagon::getResourceTypeString(chosenResource) << " of all the players "<<endl;
                //delete the card and end  his turn
                developmentCards.erase(it);
                endTurn(catan);
                break;
            }
                //road build card use (build 2 roads for free)
            case DevelopmentCard::RoadsBuild: {
                //function that will choose an available edge to build road on it (return the edge ID)
                int edgeID1 = chooseEdgeForRoadBuild(&catan.getBoard());
                //build starting road because he dont need to pay on the road
                buildStartingRoad(edgeID1 , &catan.getBoard());
                int edgeID2 = chooseEdgeForRoadBuild(&catan.getBoard());
                buildStartingRoad(edgeID2 , &catan.getBoard());
                cout<< getName() << " used roadBuild card and built 2 roads on this edges ID : "<<edgeID1 << " , "<<edgeID2<<endl;
                //delete the card and end  his turn
                developmentCards.erase(it);
                endTurn(catan);
                break;
            }
                // goodyear card use (choose 2 resources that he wants to get)
            case DevelopmentCard::GoodYear: {
                //function that will choose the resource he have the least from
                Hexagon::ResourceType resource1 = chooseMinResource();
                addResource(resource1, 1);
                Hexagon::ResourceType resource2 = chooseMinResource();
                addResource(resource2, 1);
                cout<<getName()<<" used goodyear development card"<<endl;
                //delete the card and end  his turn
                developmentCards.erase(it);
                endTurn(catan);
                break;
            }
            case DevelopmentCard::Knight: {
                // knight cards are already awarded on buy and cant use them
                throw std::runtime_error(getName() + ", you cant use knight development card, knight cards are already awarded on buy and cant use them");
            }
            case DevelopmentCard::VictoryPoint:
                // victory points are already awarded on buy and cant use them
                throw std::runtime_error(getName() + ", you cant use victory point development card, victory point cards are already awarded on buy and cant use them");

        }
    }


//function to choose the minimum resource of the player for monopol and goodYear cards
Hexagon::ResourceType Player::chooseMinResource() {
    //all the resources amounts
    int woodAmount = getResourceAmount(Hexagon::Wood);
    int brickAmount = getResourceAmount(Hexagon::Brick);
    int woolAmount = getResourceAmount(Hexagon::Wool);
    int wheatAmount = getResourceAmount(Hexagon::Wheat);
    int oreAmount = getResourceAmount(Hexagon::Ore);
    //set minimum resource to wood
    int minAmount = woodAmount;
    Hexagon::ResourceType leastResource = Hexagon::Wood;
    //find the minimum resource type
    if (brickAmount < minAmount) {
        minAmount = brickAmount;
        leastResource = Hexagon::Brick;
    }
    if (woolAmount < minAmount) {
        minAmount = woolAmount;
        leastResource = Hexagon::Wool;
    }
    if (wheatAmount < minAmount) {
        minAmount = wheatAmount;
        leastResource = Hexagon::Wheat;
    }
    if (oreAmount < minAmount) {
        minAmount = oreAmount;
        leastResource = Hexagon::Ore;
    }
    //return the minimum resource of the player
    return leastResource;
}

// function to choose a single edge for road building
int Player::chooseEdgeForRoadBuild(Board* board) {
    //the edges of the board
    vector<Edge>& edges = board->getEdges();

    // iterate through all edges to find good ones
    for (Edge& edge : edges) {
        // check if the edge is not owned by any player
        if (edge.getOwner() == nullptr) {
            // check if the edge is adjacent to a vertex owned by the player
            if (edge.getVertex1()->getOwner() == this || edge.getVertex2()->getOwner() == this) {
                return edge.getId();
            }

            // check if the edge is adjacent to another road owned by the player
            for (Edge* road : roads) {
                if (edge.isAdjacent(road)) {
                    return edge.getId();
                }
            }
        }
    }

    // if we got here it means there isnt good edge to buiiild roaad
    throw std::runtime_error(getName() + ", you don't have any good edge to build a road in the development card: road build");
}



        //trades!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//trade resources
void Player::tradeResources(Player* other, Hexagon::ResourceType giveResourceType, int giveAmount, Hexagon::ResourceType receiveResourceType, int receiveAmount) {
    //check if its his turn
    if (!getMyTurn()){
        throw std::runtime_error(getName() + ", you cant trade resources, its not your turn!");
    }//check valid resource type
    if (giveResourceType == Hexagon::None || receiveResourceType == Hexagon::None) {
        throw std::runtime_error(getName() + ", invalid resource type for this trade.");
    }//check the player have enough resources for the trade
    if (resources[giveResourceType] < giveAmount) {
        throw std::runtime_error(getName() + ", you cant trade resources, you dont have enough " + Hexagon::getResourceTypeString(giveResourceType));
    }//check the other player have enough resources for the trade
    if (other->resources[receiveResourceType] < receiveAmount) {
        throw std::runtime_error(getName() + ", you cant do this trade, " +other->getName() + " dont have enough " + Hexagon::getResourceTypeString(receiveResourceType) + " for the trade");
    }

    // do the trade
    resources[giveResourceType] -= giveAmount;
    numOfResources -= giveAmount;
    other->resources[giveResourceType] += giveAmount;
    other->numOfResources += giveAmount;
    other->resources[receiveResourceType] -= receiveAmount;
    other->numOfResources -= receiveAmount;
    resources[receiveResourceType] += receiveAmount;
    numOfResources += receiveAmount;

    std::cout << getName() << " successfully traded resources, he gave " << giveAmount << " " << Hexagon::getResourceTypeString(giveResourceType)
              << " to " << other->getName() << " for " << receiveAmount << " " << Hexagon::getResourceTypeString(receiveResourceType) << std::endl;
}
//trade development cards
void Player::tradeDevelopmentCards(Player* other, DevelopmentCard::Type giveCardType, DevelopmentCard::Type receiveCardType) {
    //check if its his turn
    if (!getMyTurn()){
        throw std::runtime_error(getName() + ", you cant trade development cards, its not your turn!");
    }

    auto giveIt = std::find_if(developmentCards.begin(), developmentCards.end(),
                               [giveCardType](const DevelopmentCard& card) { return card.getType() == giveCardType; });

    auto receiveIt = std::find_if(other->developmentCards.begin(), other->developmentCards.end(),
                                  [receiveCardType](const DevelopmentCard& card) { return card.getType() == receiveCardType; });
    //check that the player have the development card for the trade
    if (giveIt == developmentCards.end()) {
        throw std::runtime_error(getName() + ", you dont have the development card to trade: " + DevelopmentCard::typeToString(giveCardType));
    }
    //check that the other player have the development card for the trade
    if (receiveIt == other->developmentCards.end()) {
        throw std::runtime_error(other->getName() + " dont have the development card to trade: " + DevelopmentCard::typeToString(receiveCardType));
    }


    // handle special cases for Victory Point and Knight cards
    if (giveCardType == DevelopmentCard::VictoryPoint) {
        removeVictoryPoint();
        other->addVictoryPoint();
    }
    if (giveCardType == DevelopmentCard::Knight) {
        removeKnight();
        other->addKnight();
    }
    if (receiveCardType == DevelopmentCard::VictoryPoint) {
        addVictoryPoint();
        other->removeVictoryPoint();
    }
    if (receiveCardType == DevelopmentCard::Knight) {
        addKnight();
        other->removeKnight();
    }


    // do the trade
    other->developmentCards.push_back(*giveIt);
    developmentCards.erase(giveIt);

    developmentCards.push_back(*receiveIt);
    other->developmentCards.erase(receiveIt);

    std::cout << getName() << " successfully traded development card, he gave the card:" << DevelopmentCard::typeToString(giveCardType)
              << " to " << other->getName() << " for the card:" << DevelopmentCard::typeToString(receiveCardType) << std::endl;
}




//getters
vector<DevelopmentCard> Player::getDevelopmentCards() {
    return developmentCards;
}
vector<Edge *> Player::getRoads() {
    return roads;
}
vector<Vertex *> Player::getCities() {
    return cities;
}

bool Player::getIsLargestArmy() {
    return largestArmy;
}


