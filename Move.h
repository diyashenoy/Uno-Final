//
// Created by sruth on 11/4/2019.
//
#include <string>
#include <bits/stdc++.h>
#include "Game.h"
#include <vector>
#include "Card.h"
#include "Player.h"
#ifndef UNO_MOVE_H
#define UNO_MOVE_H

namespace Uno{
    class Move {

        std::string moveInput;
        std::vector<std::string> colors;

        std::vector<Uno::Card> deck;
    public:

        std::vector<std::string> setColors(std::vector<std::string> initColors);

        enum GameMoves  {help,skip,play,draw,quit,uno,invalid};

        Move(std::string move);

        Move::GameMoves validateInputAndReturnStep(std::string move);

        std::string changeToFullWord(std::string cardColor);

        bool isMoveValid(Uno::Card cardLeft, Uno::Card cardRight, Uno::Game *game, Uno::Player *player);

        bool compareCards(Uno::Card cardLeft, Uno::Card cardRight);

        bool canPlayerPlay(Uno::Card lastPlayedCard, std::vector<Uno::Card> playerHand, Uno::Game game);


        void PlayHelp();


        bool PlaySkip(Uno::Game game, Uno::Player player, int deckSize, int discardPileSize, Uno::Card lastPlayedCard, std::vector<Uno::Card> playerHand);


        bool PlayDraw(Uno::Game game, Uno::Player& player, std::vector<Uno::Card> &discardPile, std::vector<Uno::Card> &deck, bool playerAtDrawCount);

        void setDeckForMove(std::vector<Uno::Card> deck);




    };

}


#endif //UNO_MOVE_H
