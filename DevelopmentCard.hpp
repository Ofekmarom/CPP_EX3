//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

class DevelopmentCard {
public:

    enum Type { Monopol, RoadsBuild, GoodYear, Knight, VictoryPoint };//enum for the type of the card

    DevelopmentCard(Type type);

    Type getType() const;

    static std::string typeToString(Type type);//function to get the string representing the type of the card

private:
    Type type;
};

#endif // DEVELOPMENTCARD_HPP
