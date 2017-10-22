//
// Created by Dmitriy on 11.10.2017.
//

#ifndef GRAPHICSV1_CGAME_H
#define GRAPHICSV1_CGAME_H

#include "windows.h"
#include "Player.h"
#include "Renders/MainRender.h"
#include "GameState.h"

class CGame {
public:

    CGame();

    bool init(HWND hwnd, HINSTANCE hinst); // Init the game application
    void StartLoop(); // Run the game

private:
    MainRender render;

    void handleUserInput();
//    CWinObj2D win_obj;
//
//    // The cards and the back of the card
//    CDeck deck;
//    CImage card_back;
//
//    HWND buttons[eMaxButtons]; // Buttons for game input
    GameState gameState; // All other game data

    // ~~~~~~~~~~~~~~~ //
    // Private Methods //
    // ~~~~~~~~~~~~~~~ //

//    bool initButtons(); // Init all Win32 buttons
//    void initGameState(int initialBetAmt = kMinBet, EGameState gameState = eBet);
//
//    void process(float dt);
//    void processDealer();
//    void processStatus(); // Checks the win/lose status of all of the current hands
//
//    // Switch to a new game state
//    void setState(EGameState newState);
//    void setMsg(const char *text, int color = ARGB(0,0,0,0)); // Set the message text
//
//    int getCardValue(const CCard *card); // Returns the Blackjack value of the passed in card
//    int getHandValue(EPlayer which); // Returns the current value of the player's hand
//
//    bool isHandABust(EPlayer which);
//    bool isHandFull(EPlayer which); // Returns true if hand is full (player has kMaxCardsPerHand
//    // in their hand), otherwise false
//    bool isGameOver();
//
//    void awardBet(const char *msg); // Give player their earnings and start a new Blackjack hand
//    void deductBet(const char *msg); // Receive player's bet and start a new Blackjack hand
//
//    void redraw();
//
//    void drawPlayerHand();
//    void drawDealerHand();
//    void drawText();
//
//    void emptyHands(); // Empties the player and dealer hands
//    void dealCards(EPlayer which, int num); // Deals "num" cards to "which" player
};


#endif //GRAPHICSV1_CGAME_H
