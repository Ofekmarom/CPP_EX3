//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#include <iostream>
#include <vector>
#include "Catan.hpp"
#include "Player.hpp"
#include "Board.hpp"

using namespace std;

int main() {
    Player p1("Amit");
    Player p2("Yossi");
    Player p3("Dan");
    vector<Player*> players = { &p1, &p2, &p3 };
    Catan catan(players);

    catan.chooseStartingPlayer(); // Choose and print the starting player
    Board& board = catan.getBoard();


    // the starting placements for every player

    //amit builds settlements on vertex id: 3,14.  and roads on edges id: 8,16
    p1.buildStartingSettlement(3,&board);
    p1.buildStartingRoad(8,&board);
    p1.buildStartingSettlement(14,&board);
    p1.buildStartingRoad(16,&board);

    //yossi builds settlements on vertex id: 50,52.  and roads on edges id: 64,65.
    p2.buildStartingSettlement(50,&board);
    p2.buildStartingRoad(64,&board);
    p2.buildStartingSettlement(52,&board);
    p2.buildStartingRoad(65,&board);


    //dan try to build settlement on vertex that already taken
    try {
    p3.buildStartingSettlement(52, &board);
}
    catch (const exception &e)
{
    cout << e.what() << endl;
}
    //dan builds settlements on vertex id: 30,36.  and roads on edges id: 35,38.
    p3.buildStartingSettlement(30,&board);
    p3.buildStartingRoad(35,&board);
    p3.buildStartingSettlement(36,&board);
    p3.buildStartingRoad(38,&board);


    //give starting resources based on whhere the players build the settlments
    catan.giveStartingResources();



         //start of the game!!!!!!!!!!!!!

    p1.rollDice(catan);
    p1.buildRoad(15, &board);
    //amit try to roll again in the same turn
    try {
        p1.rollDice(catan);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    p1.endTurn(catan);

    //yossi roll the dice and finish his turn
    p2.rollDice(catan);
    p2.endTurn(catan);

    //dan roll the dice and finish his turn
    p3.rollDice(catan);
    p3.endTurn(catan);


    //yossi try to roll the dice not in his turn
    try {
        p2.rollDice(catan);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }

    //amit roll the dice and do a trade
    p1.rollDice(catan);
    p1.tradeResources(&p2,Hexagon::Ore,1,Hexagon::Wheat,1);
    p1.endTurn(catan);

    //yossi roll the dice and buy a development card
    p2.rollDice(catan);
    p2.buyDevelopmentCard(catan);
    p2.endTurn(catan);

    //dan roll the dice and try to trade and build city(this will work or not based on the dice results)
    p3.rollDice(catan);
    //dan try to trade -give 1 wood get 1 ore
    try {
        p3.tradeResources(&p1,Hexagon::Wood,1,Hexagon::Ore,1);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    //dan try to build city
    try {
        p3.buildCity(30,&board);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    p3.endTurn(catan);


    //print the victory points of every player and if there is a winner
    catan.printWinner();




    return 0;
}





