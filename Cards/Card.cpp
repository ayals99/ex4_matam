#include "Card.h"

std::ostream& Card::stringToPrint(std::ostream& os) const{
    printCardDetails(os, m_name);
    printEndOfCardDetails(os);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Card& card){
    return card.stringToPrint(os);
}