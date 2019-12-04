//
// Created by sruth on 11/4/2019.
//

#include "Move.h"
#include <iostream>

namespace Uno {

    Move::Move(std::string thisMove) {
        moveInput = thisMove;
    }
    
    std::vector<std::string> Move::setColors(std::vector<std::string> initColors)
    {
        
        bool found = false;
        int count = 0;
        int j = 0;
        if (initColors.size()==0) {
            for (int i = 0; i < deck.size(); ++i) {
                found = false;
                count = colors.size();

                for (j = 0; j < count; j++) {
                    if (deck[i].cardColor == colors[j]) {
                        found = true;
                        break;
                    }

                }
                if (!found)
                    colors.push_back(deck[i].cardColor);
            }
        } else
            colors = initColors;
        return colors;

    }

    Move::GameMoves Move::validateInputAndReturnStep(std::string move) {


        for (int i = 0; i < move.size(); i++) {
            move[i] = tolower(move[i]);
        }
        std::string tempMove = move;

        if (move.size() > 0) {
            int pos = move.find(" ");
            if (pos>0)
                move = move.substr(0, pos);
        }
        Move::GameMoves moveOfPlayer = invalid;



        if (move == "h" || move == "help" || move == "he" || move == "hel") {
            moveOfPlayer = Move::help;

        } else if (move == "s" || move == "skip" || move == "sk" || move == "ski") {
            moveOfPlayer = Move::skip;
        } else if (move == "q" || move == "quit" || move == "qu" || move == "qui") {
            moveOfPlayer = Move::quit;
        } else if (move == "d" || move == "draw" || move == "dr" || move == "dra") {
            moveOfPlayer = Move::draw;
        } else if (move == "p" || move == "play" || move == "pl" || move == "pla") {
            moveOfPlayer = Move::play;
        } else if (move == "u" || move == "uno" || move == "un") {
            moveOfPlayer = Move::uno;
        }

        int pos = tempMove.find(" ");
        if(pos > 0){
            tempMove = tempMove.substr(pos+1); // first space
            if(moveOfPlayer == Move::uno){
                pos = tempMove.find(" ");
                if(pos > 0){
                    moveOfPlayer = Move::invalid; // invalid if there is more than one parameter after uno
                }
            }else
                if(moveOfPlayer == Move::play){
                pos = tempMove.find(" "); // second space
                if(pos > 0){
                    tempMove = tempMove.substr(pos+1);
                    pos = tempMove.find(" "); // third space
                    if(pos > 0) {
                        if(tempMove.substr(pos+1) != "uno" && tempMove.substr(pos+1) != "u" && tempMove.substr(pos+1) != "un"){
                            moveOfPlayer = Move::invalid; // invalid if there are more than 2 parameters after play
                        }

                    }
                } else
                    moveOfPlayer = Move::invalid; // invalid if there are less than 2 parameters after play
            } else{
                    moveOfPlayer = Move::invalid;
                }

        } else{
            if (moveOfPlayer == Move::uno || moveOfPlayer == Move::play) // if there is not parameter after play ot uno then the move is invalid
                moveOfPlayer = Move::invalid;
        }

        return moveOfPlayer;
    }

    std::string Move::changeToFullWord(std::string cardColor) {

        for (int i = 0; i < cardColor.size(); ++i) {
            cardColor[i] = tolower(cardColor[i]);
        }
      /*  if (cardColor == "r" || cardColor == "re" || cardColor == "red") {
            cardColor = "Red";
        } else if (cardColor == "b" || cardColor == "bl" || cardColor == "blu" || cardColor == "blue") {
            cardColor = "Blue";
        } else if (cardColor == "y" || cardColor == "ye" || cardColor == "yel" || cardColor == "yell" ||
                   cardColor == "yello" || cardColor == "yellow") {
            cardColor = "Yellow";
        } else if (cardColor == "gr" || cardColor == "gre" || cardColor == "gree" ||
                   cardColor == "green") {
            cardColor = "Green";
        }else if (cardColor == "go" || cardColor == "gol" || cardColor == "gold"){
            cardColor = "Gold";
        }else if(cardColor == "g"){*/

            for (int i = 0; i < colors.size(); ++i) {

                std::string tempColor = colors[i];

                //convert temp colorto lower
                for (int k = 0; k < tempColor.size(); ++k) {
                    tempColor[k] = tolower(tempColor[k]);
                }
                int j = 0;
                // find match
                for (j = 0; j < cardColor.size(); ++j) {
                    if(cardColor[j] != tempColor[j]) {
                        break;
                    }
                }
                if (j==cardColor.size())
                    return colors[i];

                }


       return cardColor;
    }

    bool Move::isMoveValid(Uno::Card cardLeft, Uno::Card cardRight, Uno::Game *game, Uno::Player *player) {

        for (int i = 0; i < cardLeft.cardColor.size(); ++i) {

            cardLeft.cardColor[i] = tolower(cardLeft.cardColor[i]);
        }
        for (int i = 0; i < cardRight.cardColor.size(); ++i) {
            cardRight.cardColor[i] = tolower(cardRight.cardColor[i]);
        }
        cardLeft.cardColor = changeToFullWord(cardLeft.cardColor);
        cardRight.cardColor = changeToFullWord(cardRight.cardColor);
      /*  if (game != NULL) {
            if (game->getReneging() == "LastDrawn") {
                if (cardRight.cardColor != player->getPlayerLastDrawnCard().cardColor ||
                    cardRight.cardValue != player->getPlayerLastDrawnCard().cardValue) {
                    return false;
                }
            }
        }*/
        if (cardLeft.cardColor == cardRight.cardColor || cardLeft.cardValue == cardRight.cardValue) {
            return true;
        } else {
            return false;
        }
    }

    bool Move::compareCards(Uno::Card cardLeft, Uno::Card cardRight) {
        return (isMoveValid(cardLeft, cardRight, NULL, NULL));

    }

    bool Move::canPlayerPlay(Uno::Card lastPlayedCard, std::vector<Uno::Card> playerHand, Uno::Game game) {
        for (int i = 0; i < playerHand.size(); ++i) {
            if ((isMoveValid(lastPlayedCard, playerHand[i], NULL, NULL) == true) && (game.getMustPlayCardEachTurn() == true)) {
                return true;

            }
        }
        return false;
    }


    void Move::PlayHelp() {
        std::cout << "\t- play card_color card_value [uno]\n"
                     "\t- draw\n"
                     "\t- uno player_name\n"
                     "\t- skip\n"
                     "\t- quit\n"
                     "\t- help" << std::endl;
    }

    bool Move::PlaySkip(Uno::Game game, Uno::Player player, int deckSize, int discardPileSize, Uno::Card lastPlayedCard,
                        std::vector<Uno::Card> playerHand) {

        // can skip if
            //There are no more cards left to draw and you cannot play any cards
            //Or you have drawn the maximum amount of cards for a turn and you are not required to play a card

        if ((game.getMustPlayCardEachTurn() == true) && player.getPlayerDrawCount() < game.getDrawLimit()) {
            std::cout << "You cannot pass until you either play a card or draw at least 1 more cards." << std::endl;
            return false;
        }
        if ((game.getMustPlayCardEachTurn() == true) &&  (canPlayerPlay(lastPlayedCard, playerHand, game)))
        {
            std::cout << "You cannot pass. You must play a card this turn." << std::endl;
            return false;
        }

        if ((deckSize == 0 && discardPileSize == 0)&&(canPlayerPlay(lastPlayedCard, playerHand, game)==false)){
                return true;
            }
        if(player.getPlayerDrawCount() >= game.getDrawLimit() && game.getMustPlayCardEachTurn() == false){

            return true;
        }
    }

    void Move::setDeckForMove(std::vector<Uno::Card> tempDeck){
        deck = tempDeck;
    }




    bool Move::PlayDraw(Uno::Game game, Uno::Player &player, std::vector<Uno::Card> &discardPile, std::vector<Uno::Card> &currentDeck,bool playerAtDrawCount) {
        if ((game.getDrawLimit() == -1) || playerAtDrawCount==false) {
            if (currentDeck.size() != 0){
                player.setCardInPlayerHand(currentDeck[currentDeck.size() - 1]);
                player.setPlayerLastDrawnCard(currentDeck[(currentDeck.size() - 1)]);
                if ( player.getPlayerDrawCount() < game.getDrawLimit() )
                 player.setPlayerDrawCount(player.getPlayerDrawCount() + 1);
                else {
                    if (game.getDrawLimit() == -1)
                        player.setPlayerDrawCount(0);
                    else
                        player.setPlayerDrawCount(game.getDrawLimit());
                }
                std::vector<Uno::Card>::iterator iter = currentDeck.end();
                iter--;
                currentDeck.erase(iter);
            } else{//if the deck is empty

                player.setCardInPlayerHand(discardPile[discardPile.size() - 1]);
                player.setPlayerLastDrawnCard(discardPile[(discardPile.size() - 1)]);
                player.setPlayerDrawCount(player.getPlayerDrawCount() + 1);
                std::vector<Uno::Card>::iterator iter = discardPile.end();
                iter--;
                discardPile.erase(iter);
            }


            return true;
        } else
            return false;

        }

    }





