#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "EngSocLounge.hpp"

using namespace std;

// Waiting to be implemented
void engSocLoungeActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    // Animation Indicator
    static bool finish(false);

    //set background 
    static bool COMPUTER_HINT = false;
    //helps determine what the do if the user presses certain places
    static bool PUZZLE_COMPLETE = false;

    if(COMPUTER_HINT){
        Image studyRoomBackgroundnew(window, "engsocLoungewithhint.png");
        studyRoomBackgroundnew.drawImg(-100, 0, 1.2);
    }
    else {
        Image studyRoomBackground(window, "engsoc_loungeV2.png");
        studyRoomBackground.drawImg(-100, 0, 1.2);
    }

    //set up mouse press events
    //sword press trigger
    Button swordTrigger(window,SWORD_XPOS,SWORD_YPOS,SWORD_TRIGGER_WIDTH, SWORD_TRIGGER_HEIGHT);

    //computer press event to get hint window
    Button computerHintTrigger(window, COMPUTER_XPOS, COMPUTER_YPOS, COMPUTER_TRIGGER_WIDTH, COMPUTER_TRIGGER_HEIGHT);

    //door press trigger to exit the room
    Button exitDoorTrigger(window, ENGSOC_DOOR_XPOS, ENGSOC_DOOR_YPOS,
        ENGSOC_DOOR_TRIGGER_WIDTH, ENGSOC_DOOR_TRIGGER_HEIGHT);

    // Create Inventory 
    static Inventory inventory(window, INVENTORY_POS_X, INVENTORY_POS_Y);
    inventory.drawInventory();

    // Testing Tool Class through manipulating the sword
    // Add tools whenever is needed
    static Tool* sword = nullptr;
    // General Tool Pointer
    static Tool* tempToolPtr = nullptr;
    // Static or Dynamic Positioning?
    static bool dragging = false;  

    // Draw Sword
    if (inventory.checkHasTool(0)) {
        // Has and display sword?
        if (sword != nullptr && sword->getShow()) {
            drawInventoryTool(window, inventory, sword, tempToolPtr, dragging);
        }
    }  

    //create dialogue box for room description
    static bool ROOM_DESCRIPTION = true;
    DialogBox testDescription (window, 0, "I remember there's a sword somewhere in this room. "
        "Likely to be really useful.");
    if (ROOM_DESCRIPTION){
        testDescription.drawDialogBox(clock, finish);
    }

    // Sword pick-up box
    static bool SWORD_PICKUP_BOX_SHOW = false;
    DialogBox swordPickUp(window, 1, "Pick Up", SWORD_XPOS+SWORD_TRIGGER_WIDTH, SWORD_YPOS);
    if (SWORD_PICKUP_BOX_SHOW)
        swordPickUp.drawDialogBox();


    // EngSoc Keypad Hint
    static bool ENGSOC_KEYPAD_HINT_SHOW = false;
    DialogBox engsocHint(window, 0, "Hmm...It needs a password."); 
    if (ENGSOC_KEYPAD_HINT_SHOW) {
        engsocHint.drawDialogBox(clock, finish);
    }

    // EngSoc Exit Door Hint
    static bool ENGSOC_DOOR_HINT_SHOW = false;
    string hint;
    if (sword == nullptr) 
        hint = "Seems like the door is locked.";
    else
        hint = "I can use the sword to destroy the lock.";
    DialogBox exitDoorHint(window, 0, hint);
    if (ENGSOC_DOOR_HINT_SHOW)
        exitDoorHint.drawDialogBox(clock, finish);


    //create the puzzle
    static bool PUZZLE_SHOW;
    static KeyPad puzzle(window, "112");
    if (PUZZLE_SHOW) {
        puzzle.drawKeyPad();
    }

    //functionality of the GUI window
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    short inventoryChoice = inventory.checkBounds(mousePos);

                    //tell the user what to do in the room
                    if (ROOM_DESCRIPTION) {
                        if (finish && testDescription.checkBounds(mousePos)) {
                            ROOM_DESCRIPTION = false;
                            finish = false;
                        }
                        else if (!finish && testDescription.checkBounds(mousePos))
                            finish = true;
                        else   
                            break;
                    }

                    // Keypad Hint
                    if (ENGSOC_KEYPAD_HINT_SHOW) {
                        if (finish && engsocHint.checkBounds(mousePos)) {
                            ENGSOC_KEYPAD_HINT_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && engsocHint.checkBounds(mousePos))
                            finish = true;
                        else   
                            break;
                    }

                    // Exit Door Hint
                    if (ENGSOC_DOOR_HINT_SHOW) {
                        if (finish && exitDoorHint.checkBounds(mousePos)) {
                            ENGSOC_DOOR_HINT_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && exitDoorHint.checkBounds(mousePos))
                            finish = true;
                        else   
                            break;
                    }

                    // Testing Inventory Response
                    if (inventoryChoice != -1) {
                        // Check whether the user is retrieving a tool in inventory
                        tempToolPtr = inventory.retrieveTool(inventoryChoice);
                        if (tempToolPtr != nullptr) {
                            dragging = true;
                        }
                    }

                    // Close KeyPad
                    if (puzzle.checkCancelBounds(mousePos)) {
                        if (sword == nullptr) {
                            ENGSOC_KEYPAD_HINT_SHOW = true;
                        }
                        PUZZLE_SHOW = false;
                        puzzle.restorePuzzle();
                        clock.restart();
                    }

                    // Testing Tool-inventory linking 
                    //can get the sword if puzzle is completed
                    if (swordTrigger.checkBounds(mousePos) && PUZZLE_COMPLETE) {
                        SWORD_PICKUP_BOX_SHOW = true;
                    }

                    if (PUZZLE_COMPLETE && swordPickUp.checkBounds(mousePos)) {
                        //pop up window here to have the user enter 112
                        if (sword == nullptr) {
                            sword = new Tool(window, TOOL_LIST.at(SWORD) + ".png", SWORD);
                            sword->setShow(true);
                            SWORD_PICKUP_BOX_SHOW = false;
                            ENGSOC_KEYPAD_HINT_SHOW = false;

                            if (!inventory.storeTool(SWORD, sword)) {
                                cout << "Item stored failed! The inventory is full!" << endl;
                            }
                        }       
                    }

                    //show the user the puzzle so that they can get the sword
                    if (swordTrigger.checkBounds(mousePos) && PUZZLE_COMPLETE == false){
                        PUZZLE_SHOW = true;
                    }

                    //if the computer is pressed give a pop up window with a hint
                    if (computerHintTrigger.checkBounds(mousePos)){
                        COMPUTER_HINT = !COMPUTER_HINT;
                    }

                    //if the door is pressed, move to the congratulations window
                    if (exitDoorTrigger.checkBounds(mousePos)){
                        ENGSOC_DOOR_HINT_SHOW = true;
                        clock.restart();
                    }

                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    SWORD_PICKUP_BOX_SHOW = false;
                }
                break;



            case sf::Event::MouseButtonReleased:
                if (dragging) {
                    dragging = false;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (tempToolPtr == sword && exitDoorTrigger.checkBounds(mousePos)) {
                        //can only go if the sword has been collected
                        if(sword != nullptr){
                            state = 6; 
                            finish = false;
                            clock.restart();
                        }
                    }
                }
                break;

            case sf::Event::KeyPressed: {
                if (PUZZLE_SHOW) {
                    if (sf::Keyboard::isKeyPressed && puzzle.checkInputSize()) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (puzzle.checkPasswordMatch()) {
                                PUZZLE_COMPLETE = true;
                                PUZZLE_SHOW = false;
                                puzzle.restorePuzzle();
                            }
                            else {
                                puzzle.restorePuzzle();
                                puzzle.setMessage();
                            }
                        }
                        else {
                            puzzle.storeUserInput(event);
                        }
                    }
                }
            }
            
        }
    }

};



