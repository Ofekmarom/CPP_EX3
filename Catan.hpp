//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
#include "Player.hpp"
#include "Board.hpp"
#include "DevelopmentCard.hpp"
#include "Hexagon.hpp"

class Catan {
public:
    Catan(const vector<Player*>& players);

    void chooseStartingPlayer();//the first player in the vector of players start the game
    Player * getCurrentPlayer();//return the player that this is his turn
    void nextPlayer();//set the turn to the next player
    void rollDice();//roll the dice

    void giveStartingResources();//give resources to players based on the strating settlements of the players

    void printWinner() const;//function to print the points for every player and if there is winner

    Board& getBoard() ;

    DevelopmentCard drawDevelopmentCard();//function to draw development card from the deck when a player buys development card
    void handleMonopol(Player& player, Hexagon::ResourceType chosenResource);//function for monopol development card

    vector<DevelopmentCard>& getDevelopmentCardsCatan();//returns the deck of the cards


private:
    vector<Player*> players;
    Board board;
    int currentPlayerIndex;
    vector<DevelopmentCard> developmentCardsCatan;

    void diceGiveResources(int diceResult);//give resources to players based on the dice result



};

#endif // CATAN_HPP
