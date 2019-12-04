//
// Created by sruth on 11/2/2019.
//
#include <iostream>
#include <string>

#ifndef UNO_CARD_H
#define UNO_CARD_H

namespace Uno{
    class Card {
    public:

        std::string card;
        std::string cardColor;
        int cardValue = 0;

        Card(){

        }

        Card(std::string newValue){

            int position = newValue.find(" ");
            if (position > 0){
                cardColor = newValue.substr(0, position);

                cardValue = stoi(newValue.substr(position+1));
            }



        }

        void cardSplit(std::string newValue);


    };
}




#endif //UNO_CARD_H
