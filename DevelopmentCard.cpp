//ID : 208336701
//MAIL : ofekmarom9@gmail.com

#include <string>
#include "DevelopmentCard.hpp"

DevelopmentCard::DevelopmentCard(Type type) : type(type) {}

DevelopmentCard::Type DevelopmentCard::getType() const {
    return type;
}

//function to get the string representing the type of the card
std::string DevelopmentCard::typeToString(Type type) {
    switch (type) {
        case Monopol:
            return "Monopol";
        case RoadsBuild:
            return "RoadsBuild";
        case GoodYear:
            return "GoodYear";
        case Knight:
            return "Knight";
        case VictoryPoint:
            return "VictoryPoint";
        default:
            return "None";
    }
}
