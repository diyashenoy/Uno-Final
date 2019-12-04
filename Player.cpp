//
// Created by sruth on 11/4/2019.
//

#include "Player.h"

namespace Uno{

    Player::Player() {}

    void Player::setPlayerNumber(int val){
        playerNumber = val;
    }
    void Player::setPlayerName(std::string val){
        playerName = val;
    }

    void Player::setCardInPlayerHand(Card newCard){
        playerHand.push_back(newCard);
    }

    void Player::setPlayerDrawCount(int val){
        playerDrawCount = val;
    }

    void Player::setPlayerLastDrawnCard(Card drawnCard){
        playerLastDrawnCard = drawnCard;
    }
    void Player::setPlayerHand(std::vector<Uno::Card> playerNewHand){
        //erase the cards if any and update with new cards
        int count = playerHand.size();
        for(int i=0;i<count;i++){
            playerHand.pop_back();
        }
        count = playerNewHand.size();
        for(int j=0; j<count;j++){
            playerHand.push_back(playerNewHand[j]);
        }
    }

    void Player::setUnoShoutout(bool val){
        unoShoutOut = val;
    }

    int Player::getPlayerNumber(){
        return playerNumber;
    }

    std::string Player::getPlayerName(){
        return playerName;
    }

    int Player::getPlayerDrawCount(){
        return playerDrawCount;
    }

    std::vector<Uno::Card> Player::getPlayerHand(){
        return playerHand;
    }

    Uno::Card Player::getPlayerLastDrawnCard(){
        return playerLastDrawnCard;
    }

    bool Player::getUnoShoutout(){
        return unoShoutOut;
    }

    bool Player::isCardInPlayerHand(Card cardToCheck){

        std::vector<Uno::Card>::iterator iter = playerHand.begin();

        for (int i = 0; i < cardToCheck.cardColor.size(); ++i) {

            cardToCheck.cardColor[i] = tolower(cardToCheck.cardColor[i]);
        }

        while (iter != playerHand.end()) {
            std::string tempCardColor = iter->cardColor;
            for (int i = 0; i < iter->cardColor.size(); ++i) {

                tempCardColor[i] = tolower(tempCardColor[i]);
            }
            if (tempCardColor == cardToCheck.cardColor && iter->cardValue == cardToCheck.cardValue) {
                return true;
            }
            iter++;
        }
        return false;
    }


    void Player::deleteCardFromPlayerHand(Card cardToDelete)
    {


        //iterate through the deck and erase once you find both colour AND number on the same card
        std::vector<Uno::Card>::iterator iter = playerHand.begin();

        int i=0;
        while(iter != playerHand.end()){
            if(iter->cardColor == cardToDelete.cardColor && iter->cardValue == cardToDelete.cardValue){
                playerHand.erase(playerHand.begin()+i);
                return;
            }
            iter++;
            i++;
        }
    }




}
