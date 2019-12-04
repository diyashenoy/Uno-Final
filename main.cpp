#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <map>
#include <cctype>
#include "Card.h"
#include <string>
#include <stdlib.h>
#include "Game.h"
#include "Player.h"
#include "Move.h"
#include <algorithm>
#include <limits>
#include <exception>
#include <iterator>

using namespace Uno;


bool isEqual(std::string left, std::string right){
    if(left.size() == right.size()){
        for (int i = 0; i < left.size(); ++i) {
            if(tolower(left[i]) != tolower(right[i])){
                return false;
            }
        }return true;
    }
}

bool sortNameAndValue(Uno::Card cardLeft, Uno::Card cardRight){
    std::string tempLeft = cardLeft.cardColor;
    std::string tempRight = cardRight.cardColor;
    for (int i = 0; i < cardLeft.cardColor.size(); ++i) {
        tempLeft[i] = tolower(tempLeft[i]);
    }
    for (int i = 0; i < cardRight.cardColor.size(); ++i) {
        tempRight[i] = tolower(tempRight[i]);
    }
    if(tempLeft < tempRight){
        return true;
    } else if(tempLeft == tempRight){
        if (cardLeft.cardValue < cardRight.cardValue)
            return true;
        else if(cardLeft.cardValue == cardRight.cardValue){
            return true;
        }else{
            return false;
        }
    } else{
        return false;
    }
}

struct finalResults{
    std::string name;
    int cardValue = 0;
    int noOfCards = 0;
};

bool sortResults(finalResults left, finalResults right){
    for (int i = 0; i < left.name.size(); ++i) {
        left.name[i] = tolower(left.name[i]);
    }
    for (int i = 0; i < right.name.size(); ++i) {
        right.name[i] = tolower(right.name[i]);
    }
    if(left.cardValue < right.cardValue){
        return true;
    }else if (left.cardValue == right.cardValue){
        if (left.noOfCards < right.noOfCards){
            return true;
        }else if(left.noOfCards == right.noOfCards){
            if(left.name < right.name){
                return true;
            }

        }
    }
    return false;
}

//void readRulesFile

void printPlayerDeck(Uno::Player player, bool currentPlayer){

    if (currentPlayer){
        std::cout << "Your hand: " ;

    }else{
        std::cout << player.getPlayerName() << ": " ;
    }

    std::vector<Uno::Card> deck = player.getPlayerHand();

    for (int i = 0; i < deck.size(); ++i) {

        std::cout << deck[i].cardColor << " " << deck[i].cardValue ;
        if(i != deck.size() -1){
            std::cout << ", ";
        }
    }
    std::cout << "\n" ;
}

void printTopofDiscardPile(Uno::Card card){
    int firstLetter = 1;
    for (int i = 0; i < firstLetter; ++i) {
        card.cardColor[i] = toupper(card.cardColor[i]);
    }
    std::cout << "Top of discard pile: " << card.cardColor << " " << card.cardValue << std::endl;
}



void readRulesFile(std::string ruleFile,  Uno::Game& game){

    std::string lineFromRules;
    std::ifstream rulefileptr(ruleFile, std::ifstream::in);
    //reads the rules file and populates the rules.
    while (std::getline(rulefileptr, lineFromRules)) {

        if (lineFromRules.size() > 0) {
            int pos = lineFromRules.find(": ");

            std::string rule = lineFromRules.substr(0, pos);

            if (rule == "StartingHandSize ") {
                try {
                    game.setHandSize(stoi(lineFromRules.substr(pos + 2)));
                }
                catch (std::exception ex){
                    game.setHandSize(0);
                }
            } else if (rule == "UnoCalloutPenalty ") {
                try {
                    game.setUnoCalloutPenalty(stoi(lineFromRules.substr(pos + 2)));
                }
                catch (std::exception ex){
                    game.setUnoCalloutPenalty(0);
                }
            } else if (rule == "BadUnoCalloutPenalty ") {
                try {
                    game.setBadUnoCalloutPenalty(stoi(lineFromRules.substr(pos + 2)));
                }
                catch (std::exception ex) {
                    game.setBadUnoCalloutPenalty(0);
                }
            } else if (rule == "DrawLimit ") {
                try {
                    game.setDrawLimit(stoi(lineFromRules.substr(pos + 2)));
                }
                catch (std::exception ex)
                {
                    game.setDrawLimit(-1);
                }
            } else if (rule == "MustPlayCardEachTurn ") {
                if (lineFromRules.substr(pos + 2) == "true") {
                    game.setMustPlayCardEachTurn(true);
                } else if (lineFromRules.substr(pos + 2) == "false") {
                    game.setMustPlayCardEachTurn(false);
                }

            } else if (rule == "Reneging ") {
                game.setReneging(lineFromRules.substr(pos + 2));
            }
        }
    }
}



void readDeckFile(std::string deckFile, std::vector<Uno::Card> &deck){
    std::string str;
    std::ifstream deckfileptr  (deckFile, std::ifstream::in);
    if(!deckfileptr)
    {
        std::cerr << "Cannot open the File : "<<deckFile<<std::endl;
        return;
    }
    ;
    // Read the next line from File until it reaches the end.
    while (std::getline(deckfileptr, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0){
            int pos = str.find(" ");
            int noOfCards = stoi(str.substr(0,pos));
            Uno::Card newCard(str.substr(pos+1)); // create a new card
            for (int i = 0; i < noOfCards ; ++i) {
                deck.push_back(newCard); // Push the card into the deck
            }
        }
    }
    return;

}

void resetDeck(std::vector<Uno::Card> &deck, std::vector<Uno::Card> &discardPile, std::minstd_rand rng, Uno::Card topCard){
    int count = discardPile.size();
    if (deck.size() == 0 && discardPile.size() != 0){

        for (int i = 0; i < count; ++i) {
           ///if(!(discardPile[0].cardValue == topCard.cardValue && discardPile[0].cardColor == topCard.cardColor)) {

                deck.push_back(discardPile[0]);
                discardPile.erase(discardPile.begin());
            }


        }
            std::shuffle(deck.begin(), deck.end(), rng);
    count = deck.size();
    std::vector<Uno::Card>::iterator iter = deck.begin();
    for (int i = 0; i < count; ++i) {

        if(!(deck[i].cardValue == topCard.cardValue && deck[i].cardColor == topCard.cardColor)){
            discardPile.push_back(deck[i]);
            deck.erase(iter);
            break;
        }
        iter++;

    }
}

void resetPlayersHandToSort(std::vector<Uno::Card> &playerNewHand) {
    //erase the cards if any and update with new cards
    for (int i = 0; i < playerNewHand.size(); i++) {
        playerNewHand.pop_back();
    }
}


int main(int argc, char* argv[]) {

    std::minstd_rand randomNumberGenerator;
    std::string deckFile = argv[1];
    std::string ruleFile = argv[2];
    if (argc > 3) {

        int iSeed = atoi(argv[3]);
        randomNumberGenerator.seed(iSeed);
    } else {
        randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }


    std::string inputFromDeck = "";

    std::vector<Uno::Card> deck;

    std::vector<std::string> colors;

    readDeckFile(deckFile, deck);

    Uno::Game game;

    readRulesFile(ruleFile, game);


    int noOfPlayers = 0;
    std::string value;
    bool validInput;
    do {
        validInput = true;
        std::cout << "Enter the number of players in the game: ";

        std::getline(std::cin, value);

        //std::cin.ignore();

        for (int i = 0; i < value.size(); ++i) {

            if (!isdigit(value[i])){
                validInput = false;
                break;
            }
        }

        if(validInput == true){
            try{
                noOfPlayers = stoi(value);
            }
            catch(std::exception ex){
                noOfPlayers = 0;
            }
        }

        if (noOfPlayers < 2) {
            validInput = false;

        }

    } while (validInput == false);


    std::string playersNames;
    Uno::Player players[noOfPlayers];

    for (int i = 0; i < noOfPlayers; ++i) {
        bool isNameValid = false;
        do {
            isNameValid = false;
            std::cout << "Player " << i + 1 << " enter your name: ";
            std::getline(std::cin, playersNames);



            int pos = playersNames.find(" ");
            if(pos >= 0){
                isNameValid = true;
            }else{
                isNameValid = false;
            }

            for (int j = 0; j < i; ++j) {
                if ((isEqual(playersNames, players[j].getPlayerName())) == true) {
                    isNameValid = true;
                    break;
                }
            }

        } while (isNameValid == true);

        players[i].setPlayerName(playersNames);
        players[i].setPlayerNumber(i + 1);

    }

    //shuffle the deck (std::shuffle). make a for loop with the number of cards needed, distributing it to the players.



    std::shuffle(deck.begin(), deck.end(), randomNumberGenerator);

    // distribute he cards among players

    std::vector<Uno::Card> tempDeck = deck;


    for (int k = 0; k < game.getHandSize(); ++k) {
        for (int i = 0; i < noOfPlayers; ++i) {
            players[i].setCardInPlayerHand(deck[deck.size()-1]);
            std::vector<Uno::Card>::iterator iter = deck.end();
            iter--;
            deck.erase(iter);

            if (deck.size() == 1){ // handling corner case of deck size being smaller than the players*handsize
                break;
            }
        }
        if (deck.size() == 1){
            break;
        }
    }
    std::vector<Uno::Card> playerHandToSort;
    for (int i = 0; i < noOfPlayers; ++i) {
        playerHandToSort =  players[i].getPlayerHand();
        std::sort(playerHandToSort.begin(), playerHandToSort.end(), sortNameAndValue);
        players[i].setPlayerHand(playerHandToSort);
    }


    std::vector<std::string> initColors;

    int currentPlayer=0;
    // Add card to discard pile.
    Uno::Card topOfDiscardPile = deck[deck.size()-1];
    std::vector<Uno::Card>::iterator iter = deck.end();
    iter--;
    deck.erase(iter);

    std::vector<Uno::Card>discardPile;
    discardPile.push_back(topOfDiscardPile);

    //std::cin.ignore();
    bool gameDone = false;
    std::string move="move";
   // std::cin.ignore();

    do{
        // while it is not end of the game

        resetPlayersHandToSort(playerHandToSort);

        // print the players and their deck
        for (int i = 0; i < noOfPlayers; ++i) {
            if (i != currentPlayer){
                printPlayerDeck(players[i], false);
            }
        }

        printTopofDiscardPile(topOfDiscardPile);

        printPlayerDeck(players[currentPlayer],true);


        std::cout << players[currentPlayer].getPlayerName()<<", enter your move or h for help: ";

        //take move from player

        std::getline(std::cin, move);


        Uno::Move thisMove(move);

        thisMove.setDeckForMove(tempDeck);

        initColors = thisMove.setColors(initColors);

        Move::GameMoves step = thisMove.validateInputAndReturnStep(move);

        bool nextPlayerTurn = false;
        bool canDraw;
        bool playerAtDrawCount = true;

        int pos = 0;
        int firstLetter = 1;
        std::string tempName;

        Uno::Card playersCard;
        int j=0;
        switch(step)
        {
            case Uno::Move::help:
                thisMove.PlayHelp();
                nextPlayerTurn = false;
                break;
            case Uno::Move::skip:
                if(thisMove.PlaySkip(game,players[currentPlayer], deck.size(), discardPile.size(), topOfDiscardPile, players[currentPlayer].getPlayerHand()))
                    nextPlayerTurn=true;
                else
                    nextPlayerTurn=false;
                break;
            case Uno::Move::quit:
                gameDone = true;
                break;

            case Uno::Move::draw:

                if (deck.size() == 0 && discardPile.size() == 0){
                    std::cout << "There are no cards left to draw. Please play a card." << std::endl;
                   // nextPlayerTurn = false;

                }else{
                    //If it is no longer possible for the player to draw more cards this turn and the player has no playable cards in hand.
                    //Don't forget to consider the Reneging option when considering if they have playable cards or not.
                    if (players[currentPlayer].getPlayerDrawCount() < game.getDrawLimit()){
                        playerAtDrawCount = false;
                    }
                    else{
                        // reneging case
                        if(game.getReneging() == "LastDrawn"){
                            if(!thisMove.isMoveValid(topOfDiscardPile, players[currentPlayer].getPlayerLastDrawnCard(), &game, &players[currentPlayer])){
                                playerAtDrawCount = false;
                            }
                        }else if(!thisMove.canPlayerPlay(topOfDiscardPile, players[currentPlayer].getPlayerHand(), game)){
                            playerAtDrawCount = false;
                        }

                    }



                    if (deck.size()==0)
                        resetDeck(deck, discardPile, randomNumberGenerator, topOfDiscardPile);
                    canDraw = thisMove.PlayDraw(game, players[currentPlayer], discardPile, deck, playerAtDrawCount);
                    if(canDraw == false){
                        // if player cannot draw then nextPlayerTurn is false
                        std::cout << "You have already drawn the maximum number of cards this round." << std::endl;

                        if (game.getMustPlayCardEachTurn()){
                            if(thisMove.canPlayerPlay(topOfDiscardPile, players[currentPlayer].getPlayerHand(), game)){
                                nextPlayerTurn = false;
                            }else{
                                nextPlayerTurn = true;
                            }

                        }else{
                            if(deck.size() == 0 && discardPile.size() == 0){
                                nextPlayerTurn = true;
                            }
                        }

                    } else {
                        playerHandToSort = players[currentPlayer].getPlayerHand();
                        std::sort(playerHandToSort.begin(), playerHandToSort.end(), sortNameAndValue);
                        players[currentPlayer].setPlayerHand(playerHandToSort);
                        if(players[currentPlayer].getPlayerDrawCount() == game.getDrawLimit()) {
                            if (game.getReneging() == "LastDrawn") {
                                 if(!thisMove.isMoveValid(topOfDiscardPile, players[currentPlayer].getPlayerLastDrawnCard(), &game, &players[currentPlayer])){
                                     nextPlayerTurn = true;
                                 } else{
                                     nextPlayerTurn = false;
                                 }
                            }


                        }
                        else
                        nextPlayerTurn = false;

                    }

                }

                break;

            case Uno::Move::play:
                  players[currentPlayer].setUnoShoutout(false);
                    pos = 0;

                    playersCard.cardSplit(move);

                    playersCard.cardColor = thisMove.changeToFullWord(playersCard.cardColor);

                    if (players[currentPlayer].isCardInPlayerHand(playersCard)==true) {

                        if (thisMove.isMoveValid(topOfDiscardPile, playersCard, &game, &players[currentPlayer])) {

                            nextPlayerTurn = true;
                            topOfDiscardPile = playersCard;
                            discardPile.push_back(topOfDiscardPile);
                            players[currentPlayer].deleteCardFromPlayerHand(playersCard);


                            std::cout << players[currentPlayer].getPlayerName() << " played " << topOfDiscardPile.cardColor << " " << topOfDiscardPile.cardValue << "." << std::endl;
                            playerHandToSort = players[currentPlayer].getPlayerHand();
                            std::sort(playerHandToSort.begin(), playerHandToSort.end(), sortNameAndValue);
                            players[currentPlayer].setPlayerHand(playerHandToSort);
                        } else
                            { // not a valid move
                            std::cout << "Your card must match either the color or value of the top card on the discard pile which is " << topOfDiscardPile.cardColor << " "
                            << topOfDiscardPile.cardValue << "." << std::endl;
                            nextPlayerTurn = false;
                             }
                    }  else{ // player does not have the card or player entered the wrong command
                        if(playersCard.cardValue == -1){
                            std::cout << " Unknown command entered." << std::endl;
                            thisMove.PlayHelp();
                        }else{
                            std::cout << "You can't play a " << playersCard.cardColor << " " << playersCard.cardValue << " because you aren't holding one." << std::endl;

                        }
                        nextPlayerTurn = false;

                    }
                    if(move.size() > 0){
                        pos = move.find(" ");
                        move = move.substr(pos+1);

                        pos = move.find("uno");
                    }
                    if (pos >= 0) // called uno
                    {
                        std::cout << players[currentPlayer].getPlayerName() << " shouted UNO." << std::endl;

                        if(players[currentPlayer].getPlayerHand().size() == 1){
                            players[currentPlayer].setUnoShoutout(true);

                        }else{
                            std::cout << "You can't call UNO unless playing your second to last card." << std::endl;
                        }

                    }

                break;

            case Uno::Move::uno:
                pos = move.find(" ");
                tempName = move.substr(pos+1);



                for ( j=0;j < noOfPlayers ;j++ )
                    if (isEqual(tempName, players[j].getPlayerName())) {
                        break;
                    }

                if (j==noOfPlayers) // player name not found
                {
                    std::cout << tempName << " is not in this game." << std::endl;
                    nextPlayerTurn=false;
                    break;
                }
                if (players[j].getPlayerHand().size() == 1) {
                        if (!players[j].getUnoShoutout()) {
                            // give penalty number of cards to the player
                            if (deck.size() < game.getUnoCalloutPenalty())
                            {
                                resetDeck(deck, discardPile, randomNumberGenerator, topOfDiscardPile);
                                if(discardPile.size() > 0){
                                    topOfDiscardPile = discardPile[0];
                                }
                            }
                            for (int i = 0; i < game.getUnoCalloutPenalty(); ++i) {
                                players[j].setCardInPlayerHand(deck[deck.size() - 1]);
                                std::vector<Uno::Card>::iterator iter = deck.end();
                                iter--;
                                deck.erase(iter);
                            }
                            std::cout << "You called out " << players[j].getPlayerName() << " for not saying UNO.\n" << players[j].getPlayerName() <<
                                      " had to draw " << game.getUnoCalloutPenalty()
                                      << " cards for forgetting to call UNO." << std::endl;
                            playerHandToSort = players[j].getPlayerHand();
                            std::sort(playerHandToSort.begin(), playerHandToSort.end(), sortNameAndValue);
                            players[j].setPlayerHand(playerHandToSort);
                        } else {
                            if (game.getBadUnoCalloutPenalty() > 0) {
                                std::cout << players[j].getPlayerName() << " DID call UNO." << "\nYou had to draw "
                                          << game.getBadUnoCalloutPenalty() << " cards for a bad UNO call." << std::endl;
                                if (deck.size() < game.getBadUnoCalloutPenalty())
                                {
                                    resetDeck(deck, discardPile, randomNumberGenerator, topOfDiscardPile);
                                    if(discardPile.size() > 0){
                                        topOfDiscardPile = discardPile[0];
                                    }
                                }
                                for (int i = 0; i < game.getBadUnoCalloutPenalty(); ++i) {
                                    players[currentPlayer].setCardInPlayerHand(deck[deck.size() - 1]);
                                    std::vector<Uno::Card>::iterator iter = deck.end();
                                    iter--;
                                    deck.erase(iter);
                                }
                                playerHandToSort = players[currentPlayer].getPlayerHand();
                                std::sort(playerHandToSort.begin(), playerHandToSort.end(), sortNameAndValue);
                                players[currentPlayer].setPlayerHand(playerHandToSort);
                            } else {
                                std::cout << players[j].getPlayerName() << "DID call UNO." << std::endl;
                            }
                        }


                    } else if (players[j].getPlayerHand().size() > 1) {//give penalty number of cards to the current player
                        if (game.getBadUnoCalloutPenalty() > 0) {
                            std::cout << "You can't call UNO on " << players[j].getPlayerName()
                                      << " because they have more than 1 card in their hand"
                                         "\nYou had to draw " << game.getBadUnoCalloutPenalty() << " cards for a bad UNO call."
                                      << std::endl;
                            if (deck.size() < game.getBadUnoCalloutPenalty())
                            {
                                resetDeck(deck, discardPile, randomNumberGenerator, topOfDiscardPile);
                                if(discardPile.size() > 0){
                                    topOfDiscardPile = discardPile[0];
                                }
                            }
                            for (int i = 0; i < game.getBadUnoCalloutPenalty(); ++i) {
                                players[currentPlayer].setCardInPlayerHand(deck[deck.size() - 1]);
                                std::vector<Uno::Card>::iterator iter = deck.end();
                                iter--;
                                deck.erase(iter);
                            }
                            playerHandToSort = players[currentPlayer].getPlayerHand();
                            std::sort(playerHandToSort.begin(), playerHandToSort.end(), sortNameAndValue);
                            players[currentPlayer].setPlayerHand(playerHandToSort);
                        } else {
                            std::cout << "You can't call UNO on " << players[j].getPlayerName()
                                      << " because they have more than 1 card in their hand" << std::endl;
                        }
                    }


                    nextPlayerTurn = false;
                    break;

            default:
                std::cout << " Unknown command entered." << std::endl;
            thisMove.PlayHelp();
            nextPlayerTurn = false;


        }
        if(nextPlayerTurn){
            currentPlayer = currentPlayer + 1;
            currentPlayer = (currentPlayer)%(noOfPlayers);

           /* if (deck.size() == 0){
                resetDeck(deck,discardPile, randomNumberGenerator,topOfDiscardPile);
                }*/


        }


        for (int i = 0; i < noOfPlayers; ++i) {
            if (players[i].getPlayerHand().size() == 0){

                gameDone = true;
            }

        }



    }while(gameDone == false);

    std::vector<finalResults>resultScore;
    for (int i = 0; i < noOfPlayers; ++i) {
        finalResults item;
        int cardValue = 0;
        item.name = players[i].getPlayerName();
        item.noOfCards = players[i].getPlayerHand().size();
        std::vector<Uno::Card>playerHand = players[i].getPlayerHand();
        for (int j = 0; j < playerHand.size(); ++j) {
            item.cardValue = item.cardValue + playerHand[j].cardValue;

        }
        resultScore.push_back(item);
    }


    std::sort(resultScore.begin(), resultScore.end(), sortResults);

    std::cout <<  resultScore[0].name << " won the game" << std::endl;

    std::cout << "\n==== Leader Board ====" << std::endl;
    for (int l = 0; l < resultScore.size(); ++l) {

        std::cout << l << ".) " << resultScore[l].name << " : " << resultScore[l].cardValue << std::endl;
    }

    return 0;
}