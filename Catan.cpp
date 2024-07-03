//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#include "Catan.hpp"
#include "Hexagon.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

//constructor of catan
Catan::Catan(const vector<Player*>& players) : players(players), board() , currentPlayerIndex(0) {
   //init the development cards deck (2 monopol, 2 roads, 2 year, 3 knights, 4 victory points)
    developmentCardsCatan = {
            DevelopmentCard(DevelopmentCard::Monopol),
            DevelopmentCard(DevelopmentCard::Monopol),
            DevelopmentCard(DevelopmentCard::RoadsBuild),
            DevelopmentCard(DevelopmentCard::RoadsBuild),
            DevelopmentCard(DevelopmentCard::GoodYear),
            DevelopmentCard(DevelopmentCard::GoodYear),
            DevelopmentCard(DevelopmentCard::Knight),
            DevelopmentCard(DevelopmentCard::Knight),
            DevelopmentCard(DevelopmentCard::Knight),
            DevelopmentCard(DevelopmentCard::VictoryPoint),
            DevelopmentCard(DevelopmentCard::VictoryPoint),
            DevelopmentCard(DevelopmentCard::VictoryPoint),
            DevelopmentCard(DevelopmentCard::VictoryPoint)
    };
    srand(time(0)); // seed for random number generation
    random_shuffle(developmentCardsCatan.begin(), developmentCardsCatan.end());//shuffle the cards
}

//the first player in the vector of players start the game
void Catan::chooseStartingPlayer() {
    currentPlayerIndex = 0;
    players[static_cast<unsigned long>(currentPlayerIndex)]->startTurn();
    cout << "starting player: " << players[0]->getName() << endl;
    cout << "second player: " << players[1]->getName() << endl;
    cout << "third player: " << players[2]->getName() << endl;
}
//return the player that this is his turn
Player* Catan::getCurrentPlayer() {
    return players[static_cast<unsigned long>(currentPlayerIndex)];
}
//set the turn to the next player
void Catan::nextPlayer() {
    currentPlayerIndex = static_cast<unsigned long>(static_cast<int>((currentPlayerIndex + 1))) % players.size();
    players[static_cast<unsigned long>(currentPlayerIndex)]->startTurn();
    //check if the players that this is his turn now have enough victory point to win
    if (players[static_cast<unsigned long>(currentPlayerIndex)]->getVictoryPoints() >= 10){
        printWinner();
        exit(0);
    }
}
//roll the dice
void Catan::rollDice() {
    int diceResult = (rand() % 6 + 1) + (rand() % 6 + 1);
    cout << getCurrentPlayer()->getName()  << " Rolled: " << diceResult << endl;
    diceGiveResources(diceResult);
}
//give resources to players based on the dice result
void Catan::diceGiveResources(int diceResult) {


    // handle removing half of every resource if a 7 is rolled and player has more than 7 resources
    if (diceResult == 7) {
        cout << "the dice result is 7 so now all the players with more than 7 resources will remove half of their resources" << endl;
        for (Player* player : players) {
            //check if the player have more than 7 resources
            if (player->getnumOfResources() > 7) {
                //two variables two make sure that we removed half from the player resources
                int halfStartingResources = player->getnumOfResources() / 2;
                int resourcesRemoved = 0;
                //remove from every resource half of the amount the player have
                for (auto &resource: player->getResources()) {
                    Hexagon::ResourceType type = resource.first;
                    int amount = resource.second;
                    if (amount > 0) {
                        int toRemove = amount / 2;
                        if(toRemove != 0) {
                            player->removeResource(type, toRemove);
                            resourcesRemoved += toRemove;
                            cout << player->getName() << " removed " << toRemove << " "
                                 << Hexagon::getResourceTypeString(type)
                                 << " because the dice result was 7." << endl;
                        }
                    }
                }
                // calculate how many more resources need to be removed to reach half of the starting total
                int remainingToRemove = halfStartingResources - resourcesRemoved;
                if (remainingToRemove > 0) {
                    // remove more resources to reach exactly half of the starting total resources
                    for (auto &resource: player->getResources()) {
                        Hexagon::ResourceType type = resource.first;
                        int amount = resource.second;
                        //check if the player have more than 0 from this resource and still need to remove
                        if (amount > 0 && remainingToRemove > 0) {
                            int toRemove = min(amount, remainingToRemove);
                            //remove the min between the amount from this resource to the remaining to move
                            if(toRemove != 0) {
                                player->removeResource(type, toRemove);
                                remainingToRemove -= toRemove;

                                cout << player->getName() << " removed additional " << toRemove << " "
                                     << Hexagon::getResourceTypeString(type)
                                     << " to remove exactly half of the starting total resources" << endl;
                            }
                        }
                    }
                }
            }
        }
        return;
    }
    //if the dice result is not 7
    cout << "all the players that have building near hexagon with the number " << diceResult <<" will now get their resources" << endl;
   //for every hexagon we check if the number on it equals to the dice roll
    for ( Hexagon& hexagon : board.getHexagons()) {
        if (hexagon.getNumber() == diceResult) {
            for (Vertex* vertex : hexagon.getVertices()) {
                //for every vertex in the good hexagon we check the owner and if it city or settlmenet so we know how much to add
                if (vertex->getBuilding() != Vertex::None) {
                    Player* owner = vertex->getOwner();
                    int resourceAmount = 0;
                    if (vertex->getBuilding() == Vertex::Settlement) {
                        resourceAmount = 1;
                    }
                    if (vertex->getBuilding() == Vertex::City) {
                        resourceAmount = 2;
                    }
                    owner->addResource(hexagon.getResourceType(), resourceAmount);
                    cout << owner->getName() << " received " << resourceAmount << " " << hexagon.getResourceTypeString() << " from hexagon with id  " << hexagon.getId() << endl;

                }
            }
        }
    }
}

//give resources to players based on the strating settlements of the players
void Catan::giveStartingResources() {
    cout << "based on the strating settlements of the players:" << endl;
    //for every player we pass on its settlement and for each setllement we take the adjecancy hexagons and add the resources to the player based on that
    for (Player* player : players) {
        for (Vertex* vertex : player->getSettlements()) {
                for (Hexagon* hexagon : vertex->getAdjacentHexagons()) {
                    if (hexagon->getResourceType() != Hexagon::None) {
                        player->addResource(hexagon->getResourceType(), 1);
                        cout << player->getName() << " received 1 "
                                  << Hexagon::getResourceTypeString(hexagon->getResourceType())
                                  << " from hexagon ID: " << hexagon->getId() << endl;
                    }
                }
            }
        }
    cout << "now the game starts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" <<endl;
    cout << players[0]->getName() << ", its your turn, start to play!!!!!!" <<endl;
    }


//function to print the points for every player and if there is winner
void Catan::printWinner() const {
    for (const Player* player : players) {
        cout << player->getName() << " num of victory points is = " << player->getVictoryPoints() << endl;
    }

    for (const Player* player : players) {
        if (player->getVictoryPoints() >= 10) {
            cout << "Winner: " << player->getName() << endl;
            return;
        }
    }
    cout << "No winner yet." << endl;
}

 Board& Catan::getBoard() {
    return board;
}



//function to draw development card from the deck when a player buys development card
DevelopmentCard Catan::drawDevelopmentCard() {
    if (developmentCardsCatan.empty()) {
        throw std::runtime_error("cant buy development card, no development cards left");
    }
    //take the top card and remove it from the deck
    DevelopmentCard card = developmentCardsCatan.back();
    developmentCardsCatan.pop_back();
    return card;
}

//function for monopol development card
void Catan::handleMonopol(Player& player, Hexagon::ResourceType chosenResource) {
    for (Player* other : players) {
        if (other != &player) {
            int resourceAmount = other->getResourceAmount(chosenResource);
            other->removeResource(chosenResource, resourceAmount);
            player.addResource(chosenResource, resourceAmount);
        }
    }
}


//returns the deck of the cards
vector<DevelopmentCard>& Catan::getDevelopmentCardsCatan()  {
    return developmentCardsCatan;
}