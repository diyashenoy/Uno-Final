//
// Created by sruth on 11/2/2019.
//

#include "Game.h"

namespace Uno
{
    Game::Game()
    {

    }
    void Game::setHandSize(int val){
        startingHandSize = val;
    }
    void Game::setUnoCalloutPenalty(int val){
        unoCalloutPenalty = val;
    }
    void Game::setBadUnoCalloutPenalty(int val){
        badUnoCalloutPenalty = val;
    }
    void Game::setDrawLimit(int val){
        drawLimit = val;
    }
    void Game::setMustPlayCardEachTurn(bool val){
        mustPlayCardEachTurn = val;
    }
    void Game::setReneging(std::string val){
        reneging = val;
    }

    int Game::getHandSize(){
        return startingHandSize;
    }
    int Game::getUnoCalloutPenalty(){
        return unoCalloutPenalty;
    }

    int Game::getBadUnoCalloutPenalty(){
        return badUnoCalloutPenalty;
    }

    int Game::getDrawLimit(){
        return drawLimit;
    }
    bool Game::getMustPlayCardEachTurn(){
        return mustPlayCardEachTurn;
    }
    std::string Game::getReneging(){
        return reneging;
    }

}



