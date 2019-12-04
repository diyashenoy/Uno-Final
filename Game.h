//
// Created by sruth on 11/2/2019.
//

#ifndef UNO_GAME_H
#define UNO_GAME_H

#include <string>

namespace Uno{
    class Game {
    private:


        int startingHandSize = 0;
        int unoCalloutPenalty = 0;
        int badUnoCalloutPenalty = 0;
        int drawLimit = 0;
        bool mustPlayCardEachTurn = 0;
        std::string reneging;
    public:
        Game();

        void setHandSize(int val);

        void setUnoCalloutPenalty(int val);

        void setBadUnoCalloutPenalty(int val);

        void setDrawLimit(int val);

        void setMustPlayCardEachTurn(bool val);

        void setReneging(std::string val);

        int getHandSize();

        int getUnoCalloutPenalty();

        int getBadUnoCalloutPenalty();

        int getDrawLimit();

        bool getMustPlayCardEachTurn();

        std::string getReneging();

    };

}


#endif //UNO_GAME_H