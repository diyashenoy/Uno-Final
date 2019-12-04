//
// Created by sruth on 11/2/2019.
//

#include "Card.h"


namespace Uno{

    void Card::cardSplit(std::string newValue){
        int pos = newValue.find(" ");
        newValue = newValue.substr(pos+1);
        pos = newValue.find(" ");
        if (pos > 0){
            cardColor = newValue.substr(0, pos);
            try {
                cardValue = stoi(newValue.substr(pos + 1));
            }
            catch(std::exception ex){
                cardValue = -1;
            }            }

    }


}
