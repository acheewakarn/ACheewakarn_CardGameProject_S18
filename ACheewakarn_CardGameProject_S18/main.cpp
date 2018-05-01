//
//  main.cpp
//  ACheewakarn_CardGameProject_S18
//
//  Created by Anon on 4/26/18.
//  Copyright © 2018 Anon. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <random>
#include <chrono>
#include <array>
#include <iomanip>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

enum type_of_hand {noPair=0, onePair, twoPairs, threeOfAKind, straight, flushh, fullHouse, fourOfAKind, straightFlush, royalFlush};
enum card_suits { Clubs=0, Diamonds, Hearts, Spades};
enum card_ranks { Ace=0, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};


class Card{
    friend class Deck;
    friend class PokerHand;
    friend class Player;
private:
    card_suits suit;
    card_ranks rank;
public:
    Card(){}
    Card(int suitNdx, int rankNdx){
        
        switch(suitNdx){
            case 0:
                suit = Clubs;
                break;
            case 1:
                suit = Diamonds;
                break;
            case 2:
                suit = Hearts;
                break;
            case 3:
                suit = Spades;
                break;
        }
        
        switch(rankNdx){
            case 0:
                rank = Ace;
                break;
            case 1:
                rank = Two;
                break;
            case 2:
                rank = Three;
                break;
            case 3:
                rank = Four;
                break;
            case 4:
                rank = Five;
                break;
            case 5:
                rank = Six;
                break;
            case 6:
                rank = Seven;
                break;
            case 7:
                rank = Eight;
                break;
            case 8:
                rank = Nine;
                break;
            case 9:
                rank = Ten;
                break;
            case 10:
                rank = Jack;
                break;
            case 11:
                rank = Queen;
                break;
            case 12:
                rank = King;
                break;
                
        }
        
    }
    void displayCard(){
        
        cout << rank << " of " << suit << endl;
    }
    
};



class Deck {
    friend class Game;
    friend class Player;
    friend class Poker;
protected:
    vector<Card> deck;
public:
    Deck(){}
    void buildDeck(){
        for(int suitNdx = 0; suitNdx < 4; suitNdx++){
            for(int rankNdx = 0; rankNdx < 13; rankNdx++ ){
                deck.push_back(Card( suitNdx, rankNdx));
            }
        }
        shuffleDeck();
    }
    void shuffleDeck(){
        unsigned seed = (unsigned) chrono::system_clock::now().time_since_epoch().count();;
        shuffle(deck.begin(), deck.end(), default_random_engine(seed));
    }
    
    
    
    void displayDeck(){
        string strRank, strSuit;
        
        for(int i = 0; i < deck.size(); i++){
            switch(deck[i].rank){
                case 0:
                    strRank = "Ace";
                    break;
                case 1:
                    strRank = "Two";
                    break;
                case 2:
                    strRank = "Three";
                    break;
                case 3:
                    strRank = "Four";
                    break;
                case 4:
                    strRank = "Five";
                    break;
                case 5:
                    strRank = "Six";
                    break;
                case 6:
                    strRank = "Seven";
                    break;
                case 7:
                    strRank = "Eight";
                    break;
                case 8:
                    strRank = "Nine";
                    break;
                case 9:
                    strRank = "Ten";
                    break;
                case 10:
                    strRank = "Jack";
                    break;
                case 11:
                    strRank = "Queen";
                    break;
                case 12:
                    strRank = "King";
                    break;
                    
            }
            
            switch(deck[i].suit){
                case 0:
                    strSuit = "Clubs";
                    break;
                case 1:
                    strSuit = "Diamonds";
                    break;
                case 2:
                    strSuit = "Hearts";
                    break;
                case 3:
                    strSuit = "Spades";
                    break;
                    
            }
            
            cout << i+1 << ". ";
            cout << left << setw(5) << strRank;
            cout << " of ";
            cout << left << setw(7) << strSuit << endl;
        }
    }
    
};

class PokerHand: public Deck{
public:
    
    void countRanks(){
        int countByRank[13] = {0};
        for (Card c : deck){
            countByRank[c.rank]++;
        }
        
    }
    
    void sortRank(){
        for(int i = 1; i < deck.size(); i++){
            Card tmpCard (deck[i].suit, deck[i].rank);
            for(int j = 0; j < i; j++){
                if (tmpCard.rank < deck[j].rank){
                    for(int k = i; k > j; k--){
                        deck[k] =  deck[k-1];
                    }
                    deck[j] = tmpCard;
                    break;
                }
            }
        }
    }
    
    bool isOnePair(){
        int countByRank[13] = {0};
        int pairCount = 0;
        for (Card c : deck){
            countByRank[c.rank]++;
        }
        
        for (int i = 0; i < 13; i++){
            if (countByRank[i] == 2)
                pairCount++;
        }
        
        if (pairCount == 1)
            return true;
        return false;
    }
    
    bool isTwoPairs(){
        int countByRank[13] = {0};
        int pairCount = 0;
        for (Card c : deck){
            countByRank[c.rank]++;
        }
        
        for (int i = 0; i < 13; i++){
            if (countByRank[i] == 2)
                pairCount++;
        }
        
        if (pairCount == 2)
            return true;
        return false;
    }
    
    bool isThreeOfAKind(){
        int countByRank[13] = {0};
        for (Card c : deck){
            countByRank[c.rank]++;
        }
        
        for (int i = 0; i < 13; i++){
            if (countByRank[i] == 3)
                return true;
        }
        return false;
    }
    
    bool isStraight(){
        int consecutiveCount = 0;
        int countByRank[13] = {0};
        int countBySuit[4] = {0};
        
        for(Card c: deck){
            countBySuit[c.suit]++;
        }
        
        for(Card c: deck){
            countByRank[c.rank]++;
        }
        for (int i = 0; i < 12; i++){
            if (countByRank[i] == 1 && countByRank[i+1] == 1)
                consecutiveCount++;
            else
                consecutiveCount = 0;
        }
        
        for (int i = 0; i < 4; i++){
            if (countBySuit[i] == 5){
                return false;
            }
        }
        if (consecutiveCount == 4)
            return true;
        return false;
    }
    
    bool isFlush(){
        int consecutiveCount = 0;
        int countBySuit[4] = {0};
        int countByRank[13] = {0};
        bool sameSuit = false;
        for(Card c: deck){
            countBySuit[c.suit]++;
        }
        
        for(Card c: deck){
            countByRank[c.rank]++;
        }
        
        for(int i = 0; i< 4; i++){
            if (countBySuit[i] == 5){
                sameSuit = true;
            }
        }
        for (int i = 0; i < 12; i++){
            if (countByRank[i] == 1 && countByRank[i+1] == 1)
                consecutiveCount++;
            else
                consecutiveCount = 0;
        }
        if (sameSuit && consecutiveCount <5)
            return true;
        return false;
    }
    
    bool isFullHouse(){
        if (isThreeOfAKind() && isOnePair())
            return true;
        return false;
    }
    
    bool isFourOfAKind(){
        int countByRank[13] = {0};
        for (Card c : deck){
            countByRank[c.rank]++;
        }
        
        for (int i = 0; i < 13; i++){
            if (countByRank[i] == 4)
                return true;
        }
        return false;
    }
    
    bool isStraightFlush(){
        int consecutiveCount = 0;
        int countBySuit[4] = {0};
        int countByRank[13] = {0};
        bool sameSuit = false;
        for(Card c: deck){
            countBySuit[c.suit]++;
        }
        
        for(Card c: deck){
            countByRank[c.rank]++;
        }
        
        for(int i = 0; i< 4; i++){
            if (countBySuit[i] == 5){
                sameSuit = true;
            }
        }
        for (int i = 0; i < 12; i++){
            if (countByRank[i] == 1 && countByRank[i+1] == 1)
                consecutiveCount++;
            else
                consecutiveCount = 0;
        }
        if (sameSuit && consecutiveCount ==4)
            return true;
        return false;
    }
    
    bool isRoyalFlush(){
        int countByRank[13] = {0};
        int countBySuit[4] = {0};
        bool sameSuit = false;
        for (Card c : deck)
            countByRank[c.rank]++;
        for (Card c : deck)
            countBySuit[c.suit]++;
        
        for(int i = 0; i < 4; i++){
            if (countBySuit[i] == 5)
                sameSuit = true;
        }
        
        if (countByRank[0] == 1 && countByRank[10] == 1 && countByRank[11] == 1 && countByRank[12] == 1 && sameSuit)
            return true;
        
        return false;
    }
};

class Player{
public:
    string name;
    PokerHand hand;
    type_of_hand type;
public:
    Player(){}
    void setName(string name){
        this->name = name;
    }
    
    void displayHand(){
        cout << name << "'s Hand: " << endl;
        hand.displayDeck();
    }
    
    void discardCard(){
        
    }
    void getHandType(){
        if(hand.isRoyalFlush()){
            type = royalFlush;
        } else if (hand.isStraightFlush()){
            type = straightFlush;
        } else if (hand.isFourOfAKind()){
            type = fourOfAKind;
        } else if (hand.isFullHouse()){
            type = fullHouse;
        }else if (hand.isFlush()){
            type = flushh;
        } else if (hand.isStraight()){
            type = straight;
        } else if (hand.isThreeOfAKind()){
            type = threeOfAKind;
        } else if (hand.isTwoPairs()){
            type = twoPairs;
        } else if (hand.isOnePair()){
            type = onePair;
        } else {
            type = noPair;
        }
    }
    
    void displayType(){
        string strType;
        switch(type){
            case 0:
                strType = "no pair";
                break;
            case 1:
                strType = "1 pair";
                break;
            case 2:
                strType = "2 pairs";
                break;
            case 3:
                strType = "3 of a kind";
                break;
            case 4:
                strType = "straight";
                break;
            case 5:
                strType = "flush";
                break;
            case 6:
                strType = "full house";
                break;
            case 7:
                strType = "4 of a kind";
                break;
            case 8:
                strType = "straight flush";
                break;
            case 9:
                strType = "royal flush";
                break;
        }
        cout << name << " has " << strType << "." << endl;
    }
    
    type_of_hand getType(){
        return type;
    }
    
};

class Game{
    friend class Poker;
    friend class Player;
protected:
    Deck playingDeck;
    int playerCount;
    vector<Player> players;
    
public:
    Game(){}
    Game(int count, string playerNames[]){
        playerCount = count;
        playingDeck.buildDeck();
        players.resize(count);
        for(int i = 0; i < count; i++){
            players[i].setName(playerNames[i]);
        }
    }
    
    void displayPlayingDeck(){
        playingDeck.displayDeck();
    }
    
    void dealCards(){
        for(int i = 0; i < playerCount; i++){
            players[i].hand.deck.resize(5);
            move(playingDeck.deck.begin(), playingDeck.deck.begin()+5, players[i].hand.deck.begin());
            playingDeck.deck.erase(playingDeck.deck.begin(), playingDeck.deck.begin()+5);
        }
    }
    
    void displayHands(){
        
        for(int i = 0; i < playerCount; i++){
            players[i].displayHand();
            players[i].getHandType();
            players[i].displayType();
            cout<<endl;
        }
        
    }
};

class Poker: public Game{
private:
    vector<type_of_hand> types;
    type_of_hand type;
    int winnerNdx;
    
public:
    Poker(int count, string playersNames[]): Game(count, playersNames){}
    
    void sortHand(){
        for (int i = 0; i < players.size(); i++){
            players[i].hand.sortRank();
        }
    }
    void shufflePlayingDeck(){
        playingDeck.shuffleDeck();
    }
    
    void getType(){
        for(Player p : players){
            p.getHandType();
        }
    }
    string getWinner(){
        
        string result;
        int highScoreCount = 0;
        int winnerNum  = 0;
        string winner;
        //rint points[5] = {0, 0, 0, 0, 0};
        array<int, 5> points;
        points.fill(0);
        
        for (int i = 0; i < players.size(); i++){
            points[i] += players[i].getType();
            if (points[i] > winnerNum ){
                highScoreCount = 0;
                winnerNum = points[i];
                winner = players[i].name;
            } else if (points[i] == winnerNum){
                highScoreCount++;
            }
        }
        
        if (highScoreCount >= 1){
            result = "There is a tie.";
        } else {
            result = "The Winner is " + winner + ".";
        }
        
        return result;
    }
    
    void replaceCards(){
        for(Player& p: players){
            
            string replaceCommand;
            do {
                
                cout << "Enter Index of a Card to be Replaced for " << p.name << " or 'd' if Done: " ;
                cin >> replaceCommand;
                
                if (replaceCommand == "d"){
                    break;
                }
                
                int cardNdx;
                try{
                    cardNdx = stoi(replaceCommand);
                } catch(std::invalid_argument& e ){
                    cout << "Invalid Command" << endl;
                    continue;
                } catch (std::out_of_range& e){
                    cout << "Enter Index between 1 to 5" << endl;
                    continue;
                }
                
                if (cardNdx > 5|| cardNdx < 1){
                    cout << "Invalid Index. Please Re-Enter" << endl;
                    
                } else {
                    p.hand.deck[cardNdx-1] = playingDeck.deck[0];
                    playingDeck.deck.erase(playingDeck.deck.begin());
                }
            } while (replaceCommand != "d");
            
        }
    }
};

void launchGame(){
    char command;
    cout << "Hello. Let's play some Poker!" << endl;
    
    do{
        cout << "Enter 'p' to Play or 'q' to Quit..." << endl;
        cin >> command;
        
        if (command == 'q'){
            break;
        } else if (command == 'p'){
            
            string input;
            int playerCount;
            
            do{
                cout << "Please Enter The Number Of Players (2-5 Players): ";
                cin >> input;
                try{
                    playerCount  = stoi(input);
                } catch(std::out_of_range e){
                    cout << "Invalid Input. Please Re-Enter" << endl;
                    continue;
                } catch (std::invalid_argument e){
                    cout << "Invalid Input. Please Re-Enter" << endl;
                    continue;
                }
            } while(playerCount > 5 || playerCount <= 1);
            if (playerCount > 1 && playerCount < 6){
                string playerNames[playerCount];
                for(int i = 0; i < playerCount; i++){
                    cout << "Please Enter A Name For Player " << i+1 << ": ";
                    cin >> playerNames[i];
                }
                cout << endl;
            
                Poker pokerGame (playerCount, playerNames);
                pokerGame.dealCards();
                pokerGame.sortHand();
                pokerGame.displayHands();
                pokerGame.replaceCards();
                pokerGame.sortHand();
                pokerGame.displayHands();
                cout << pokerGame.getWinner() << endl;
            }
            
        }
    } while(command != 'q');
    cout << "Good Bye!" << endl;
}

int main(int argc, const char * argv[]) {
    launchGame();
    return 0;
}
