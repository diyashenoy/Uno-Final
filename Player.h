//
// Created by sruth on 11/4/2019.
//

#include <string>
#include <iostream>
#include "Card.h"
#include <vector>
#include <iterator>


#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H

namespace Uno{
    class Player {
    private:
        int playerNumber = 0;
        std::string playerName;
        std::vector<Uno::Card> playerHand;
        int playerDrawCount = 0;
        Uno::Card playerLastDrawnCard;
        bool unoShoutOut = false;


    public:
        Player();

        void setPlayerNumber(int val);

        void setPlayerName(std::string val);

        void setCardInPlayerHand(Card newCard);

        void setPlayerDrawCount(int val);

        void setPlayerLastDrawnCard(Card drawnCard);

        void setPlayerHand(std::vector<Uno::Card> playerNewHand);

        void setUnoShoutout(bool unoShoutOut);

        int getPlayerNumber();

        std::string getPlayerName();

        int getPlayerDrawCount();

        std::vector<Uno::Card> getPlayerHand();

        Uno::Card getPlayerLastDrawnCard();

        bool isCardInPlayerHand(Card cardToCheck);

        void deleteCardFromPlayerHand(Card cardToDelete);

        bool getUnoShoutout();








    };

};


#endif //UNO_PLAYER_H