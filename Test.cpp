//ID : 208336701
//mail : ofekmarom9@gmail.com

//matala 3




#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Player.hpp"
#include "Catan.hpp"
#include "Hexagon.hpp"
#include <vector>
#include <iostream>


using namespace std;



// Test initialization of a Player
TEST_CASE("player initialization") {
    Player player("yossi");
    CHECK(player.getName() == "yossi");
    CHECK(player.getVictoryPoints() == 0);
    CHECK(player.getnumOfResources() == 0);
    CHECK(player.getnumOfKnights() == 0);
    CHECK(player.getIsLargestArmy() == false);
}

// Test adding resources to a Player
TEST_CASE("player add resources") {
    Player player("yossi");
    player.addResource(Hexagon::ResourceType::Brick, 3);
    CHECK(player.getResourceAmount(Hexagon::ResourceType::Brick) == 3);
}

// test removing resources from a Player
TEST_CASE("Player remove resources") {
    Player player("yossi");
    player.addResource(Hexagon::ResourceType::Brick, 3);
    player.removeResource(Hexagon::ResourceType::Brick, 2);
    CHECK(player.getResourceAmount(Hexagon::ResourceType::Brick) == 1);
}


// test the game initialization with players and starting player selection
TEST_CASE("Game initialization") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dan");
    vector<Player*> players = { &p1, &p2, &p3 };
    Catan catan(players);
    catan.chooseStartingPlayer(); // Choose and print the starting player
    CHECK(catan.getCurrentPlayer()->getName() == "Amit");
}


// test player turns
TEST_CASE("players turns are good") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dan");
    vector<Player*> players = { &p1, &p2, &p3 };
    Catan catan(players);
    catan.chooseStartingPlayer();
    p1.endTurn(catan);
    CHECK(catan.getCurrentPlayer()->getName() == "Yossi");
    p2.endTurn(catan);
    CHECK(catan.getCurrentPlayer()->getName() == "Dan");
    p3.endTurn(catan);
    CHECK(catan.getCurrentPlayer()->getName() == "Amit");
}




//test the full demo
TEST_CASE("test the full demo") {

    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dan");
    vector<Player*> players = { &p1, &p2, &p3 };
    Catan catan(players);

    catan.chooseStartingPlayer(); // Choose and print the starting player
    Board& board = catan.getBoard();


//checking the init was good
    CHECK(p1.getVictoryPoints() == 0);
    CHECK(p2.getVictoryPoints() == 0);
    CHECK(p3.getVictoryPoints() == 0);

    CHECK(p1.getName() == "Amit");
    CHECK(p1.getnumOfResources() == 0);
    CHECK(p1.getnumOfKnights() == 0);
    CHECK(p1.getMyTurn() == true);
    CHECK(p2.getMyTurn() == false);

    //check if he have the resources at the start of the game,than add this resources so it will be true,and than remove them so will be false
    //this tests: hasresources,addresources,removeresources,getnumofresources.
    map<Hexagon::ResourceType, int> price = {
            {Hexagon::Wood, 1},
            {Hexagon::Brick, 1},
    };
    CHECK(p1.hasResources(price) == false);
    p1.addResource(Hexagon::Wood,1);
    p1.addResource(Hexagon::Brick,1);
    CHECK(p1.hasResources(price) == true);
    CHECK(p1.getnumOfResources() == 2);
    p1.removeResource(Hexagon::Wood,1);
    p1.removeResource(Hexagon::Brick,1);
    CHECK(p1.hasResources(price) == false);
    CHECK(p1.getnumOfResources() == 0);






    CHECK(catan.getCurrentPlayer()->getName() == "Amit");

    // the starting placements for every player
//checking that beffore the build the  vertex and edge was not taken and after the building theey are taken
//and also check that the owner is correct

    CHECK(catan.getBoard().getVertices()[2].getIsTaken() == false);
    //amit builds settlements on vertex id: 3,14.  and roads on edges id: 8,16
    p1.buildStartingSettlement(3,&board);
    CHECK(catan.getBoard().getVertices()[2].getOwner()->getName() == "Amit");
    CHECK(catan.getBoard().getVertices()[2].getIsTaken() == true);
    CHECK(catan.getBoard().getEdges()[7].getIsTaken() == false);
    p1.buildStartingRoad(8,&board);
    CHECK(catan.getBoard().getEdges()[7].getOwner()->getName() == "Amit");
    CHECK(catan.getBoard().getEdges()[7].getIsTaken() == true);
    p1.buildStartingSettlement(14,&board);
    CHECK(catan.getBoard().getVertices()[13].getOwner()->getName() == "Amit");
    p1.buildStartingRoad(16,&board);
    CHECK(catan.getBoard().getEdges()[15].getOwner()->getName() == "Amit");


    //its the same so check only the owner
    //yossi builds settlements on vertex id: 50,52.  and roads on edges id: 64,65.
    p2.buildStartingSettlement(50,&board);
    CHECK(catan.getBoard().getVertices()[49].getOwner()->getName() == "Yossi");
    p2.buildStartingRoad(64,&board);
    CHECK(catan.getBoard().getEdges()[63].getOwner()->getName() == "Yossi");
    p2.buildStartingSettlement(52,&board);
    p2.buildStartingRoad(65,&board);


    //dan try to build settlement on vertex that already taken
    CHECK_THROWS(p3.buildStartingSettlement(52, &board));

    //dan builds settlements on vertex id: 30,36.  and roads on edges id: 35,38.
    p3.buildStartingSettlement(30,&board);
    p3.buildStartingRoad(35,&board);
    p3.buildStartingSettlement(36,&board);
    p3.buildStartingRoad(38,&board);
    CHECK(catan.getBoard().getVertices()[29].getOwner()->getName() == "Dan");



    CHECK(p1.getnumOfResources() == 0);
    CHECK(p2.getnumOfResources() == 0);
    CHECK(p3.getnumOfResources() == 0);
    //give starting resources based on whhere the players build the settlments
    catan.giveStartingResources();
    CHECK(p1.getnumOfResources() != 0);
    CHECK(p2.getnumOfResources() != 0);
    CHECK(p3.getnumOfResources() != 0);

    //amit have settlements on vertex id: 3,14 so he need to have:
    //1 ore, 1 wool from the settlement on vertex id 3
    //1 wood, 1 brick, 1 wool from the settlement on vertex id 14
    CHECK(p1.getResourceAmount(Hexagon::Wood) == 1);
    CHECK(p1.getResourceAmount(Hexagon::Brick) == 1);
    CHECK(p1.getResourceAmount(Hexagon::Ore) == 1);
    CHECK(p1.getResourceAmount(Hexagon::Wool) == 2);
    CHECK(p1.getnumOfResources() == 5);






    //start of the game!!!!!!!!!!!!!

    p1.rollDice(catan);
    p1.buildRoad(15, &board);
    CHECK(catan.getBoard().getEdges()[14].getOwner()->getName() == "Amit");
    //amit try to roll again in the same turn
    CHECK_THROWS(p1.rollDice(catan));

    //check that when the player end his turn its works good
    CHECK(catan.getCurrentPlayer()->getName() == "Amit");
    p1.endTurn(catan);
    CHECK(catan.getCurrentPlayer()->getName() == "Yossi");
    CHECK(p1.getMyTurn()==false);
    CHECK(p2.getMyTurn()==true);

    //dan try to roll the dice not in his turn
    CHECK_THROWS(p3.rollDice(catan));
    //dan try to end his turn  not in his turn
    CHECK_THROWS(p3.endTurn(catan));


    //yossi roll the dice and finish his turn
    p2.rollDice(catan);
    p2.endTurn(catan);

    //dan roll the dice and finish his turn
    p3.rollDice(catan);
    p3.endTurn(catan);


    //amit roll the dice and do a trade
    p1.rollDice(catan);

    //test the trade
    int oreAmountBeforePlayer1=p1.getResourceAmount(Hexagon::Ore);
    int wheatAmountBeforePlayer1=p1.getResourceAmount(Hexagon::Wheat);

    int oreAmountBeforePlayer2=p2.getResourceAmount(Hexagon::Ore);
    int wheatAmountBeforePlayer2=p2.getResourceAmount(Hexagon::Wheat);
    //the trade
    p1.tradeResources(&p2,Hexagon::Ore,1,Hexagon::Wheat,1);

    int oreAmountAfterPlayer1=p1.getResourceAmount(Hexagon::Ore);
    int wheatAmountAfterPlayer1=p1.getResourceAmount(Hexagon::Wheat);

    int oreAmountAfterPlayer2=p2.getResourceAmount(Hexagon::Ore);
    int wheatAmountAfterPlayer2=p2.getResourceAmount(Hexagon::Wheat);
    //check the trade for p1
    CHECK(oreAmountBeforePlayer1 - oreAmountAfterPlayer1 == 1);
    CHECK(wheatAmountAfterPlayer1 - wheatAmountBeforePlayer1 == 1);

    //check the trade for p2
    CHECK(oreAmountAfterPlayer2 - oreAmountBeforePlayer2 == 1);
    CHECK(wheatAmountBeforePlayer2 - wheatAmountAfterPlayer2 == 1);

    p1.endTurn(catan);





    //yossi roll the dice and buy a development card
    p2.rollDice(catan);
    //check that the card move from the game deck to the player
    CHECK(catan.getDevelopmentCardsCatan().size() == 13);
    CHECK(p2.getDevelopmentCards().size() == 0);
    p2.buyDevelopmentCard(catan);
    CHECK(catan.getDevelopmentCardsCatan().size() == 12);
    CHECK(p2.getDevelopmentCards().size() == 1);


    //dan try to buy development card not in his turn
    CHECK_THROWS(p3.buyDevelopmentCard(catan));
    //yossi finish his turn
    p2.endTurn(catan);

    //dan roll the dice
    p3.rollDice(catan);
    //dan try to trade and dont have enough resources
    CHECK_THROWS(p3.tradeResources(&p1,Hexagon::Wood,1000,Hexagon::Ore,1));

    //cheeck that the vertex go from settlement to city and that dan gets 1 more victory point
    p3.addResource(Hexagon::Ore,3);
    p3.addResource(Hexagon::Wheat,2);
    CHECK(catan.getBoard().getVertices()[29].getBuilding() == Vertex::Settlement);
    CHECK(p3.getVictoryPoints() == 2);
    //dan build city
    p3.buildCity(30,&board);

    CHECK(catan.getBoard().getVertices()[29].getOwner()->getName() == "Dan");
    CHECK(catan.getBoard().getVertices()[29].getBuilding() == Vertex::City);
    CHECK(p3.getVictoryPoints() == 3);


    p3.endTurn(catan);

    //amit try to build city on settlement of another player
    CHECK_THROWS(p1.buildCity(50,  &board));



    //print the victory points of every player and if there is a winner
    catan.printWinner();


}






// test drawing development cards
TEST_CASE("draw development card") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dan");
    vector<Player*> players = { &p1, &p2, &p3 };
    Catan catan(players);

    catan.chooseStartingPlayer(); // Choose and print the starting player
    p1.addResource(Hexagon::Wool,1);
    p1.addResource(Hexagon::Wheat,1);
    p1.addResource(Hexagon::Ore,1);


    CHECK(catan.getDevelopmentCardsCatan().size() == 13);
    CHECK(p1.getDevelopmentCards().size() == 0);
    p1.buyDevelopmentCard(catan);
    CHECK(catan.getDevelopmentCardsCatan().size() == 12);
    CHECK(p1.getDevelopmentCards().size() == 1);

}


//testing all the development cards
TEST_CASE("development cards and using them") {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dan");
    vector<Player*> players = { &p1, &p2, &p3 };
    Catan catan(players);

    catan.chooseStartingPlayer(); // Choose and print the starting player
    Board& board = catan.getBoard();
    //add resource to buy all the development cards
    p1.addResource(Hexagon::Wool,14);
    p1.addResource(Hexagon::Wheat,13);
    p1.addResource(Hexagon::Ore,14);


    p1.buildStartingSettlement(3,&board);
    p1.buildStartingRoad(8,&board);
    p1.buildStartingSettlement(14,&board);
    p1.buildStartingRoad(16,&board);

    //check largest army before buying all the cards
    CHECK(p1.getnumOfKnights() == 0);
    CHECK(p1.getIsLargestArmy() == false);
    int victoryPointsBeforeeee = p1.getVictoryPoints();
    //buy all the cards
    for(int i=0; i<13; i++){
        p1.buyDevelopmentCard(catan);
    }
    int victoryPointsAfter = p1.getVictoryPoints();

    //check largest army after buying all the cards (knight card)
    CHECK(p1.getnumOfKnights() == 3);
    CHECK(p1.getIsLargestArmy() == true);


    //check victory point card effect ( 4 victorycard + 2 points because largest army = 6 more points)
    CHECK(victoryPointsAfter - victoryPointsBeforeeee == 6);


    //try to buy when the deck is empty
    CHECK_THROWS(p1.buyDevelopmentCard(catan));


    p2.addResource(Hexagon::Wood,10);
    p2.addResource(Hexagon::Brick,10);
    p2.addResource(Hexagon::Ore,10);
    p2.addResource(Hexagon::Wool,10);
    p2.addResource(Hexagon::Wheat,10);
    p3.addResource(Hexagon::Wood,10);
    p3.addResource(Hexagon::Brick,10);
    p3.addResource(Hexagon::Wool,10);
    p3.addResource(Hexagon::Wheat,10);
    p3.addResource(Hexagon::Ore,10);

//use of monopol card
    CHECK(p1.getResourceAmount(Hexagon::Wood) == 0);
    CHECK(p2.getResourceAmount(Hexagon::Wood) == 10);
    CHECK(p3.getResourceAmount(Hexagon::Wood) == 10);
    p1.useDevelopmentCard(DevelopmentCard::Monopol,catan);
    CHECK(p1.getResourceAmount(Hexagon::Wood) == 20);
    CHECK(p2.getResourceAmount(Hexagon::Wood) == 0);
    CHECK(p3.getResourceAmount(Hexagon::Wood) == 0);

    p2.endTurn(catan);
    p3.endTurn(catan);



    //use of goodyear card
    int currentresources = p1.getnumOfResources();
    //check that after the use of development card the turn goes to the next player
    CHECK(p1.getMyTurn() == true);
    p1.useDevelopmentCard(DevelopmentCard::GoodYear,catan);
    CHECK(p1.getMyTurn() == false);
    CHECK(p2.getMyTurn() == true);
    int currentresourcesAfter = p1.getnumOfResources();
    CHECK(currentresourcesAfter - currentresources == 2);



    p2.endTurn(catan);
    p3.endTurn(catan);


    //use of road build
    CHECK(p1.getRoads().size() == 2);
    p1.useDevelopmentCard(DevelopmentCard::RoadsBuild,catan);
    CHECK(p1.getRoads().size() == 4);




}



