#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "teaRoom.hpp"

using namespace std;

void teaRoomActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    // Animation Indicator
    static bool finish(false);

    Image background(window, "teaRoomPhoto.jpg");
    background.drawImg(-100, 0, 1.2, 1, WINDOW_WIDTH, WINDOW_HEIGHT, 180, 20);

    static Inventory inventory(window, INVENTORY_POS_X, INVENTORY_POS_Y);
    inventory.drawInventory();

    static Tool* pencil = nullptr;
    // General Tool Pointer
    static Tool* tempToolPtr = nullptr;
    // Static or Dynamic Positioning?
    static bool dragging = false;  

    // Pencil
    if (inventory.checkHasTool(PENCIL)) {
        // Has and display pencil
        if (pencil != nullptr && pencil->getShow()) {      
            drawInventoryTool(window, inventory, pencil, tempToolPtr, dragging);
        }
    }  

    // Pencil Visual
    if (pencil == nullptr) {
        Image pencilVisual(window, TOOL_LIST.at(PENCIL) + ".png");
        pencilVisual.drawImg(PENCIL_XPOS-40, PENCIL_YPOS-20, 0.9, 0.9,
            PENCIL_TRIGGER_WIDTH, PENCIL_TRIGGER_HEIGHT, 150, 0);
    }

    // Next Button
    static bool PUZZLE_COMPLETE(false);
    Button nextButton(window, WINDOW_WIDTH-1.1*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-1.1*SMALL_BUTTON_HEIGHT,
            SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // End dialog
    static bool NEXT_SHOW(false);
    DialogBox endDialogTeaRoom(window, 0, "The entire ILC just feels strange today...\n"
        "I need to find a way to get out of here. Hmm...\n! The Design Bay may be a good place to find some tools!");
    if (PUZZLE_COMPLETE) {
        endDialogTeaRoom.drawDialogBox(clock, finish);
    }
    if (NEXT_SHOW) {
        Text nextButtonText(window, "AndadaPro-Italic_wght.ttf", "Next", 60);
        nextButton.drawButton();
        nextButtonText.drawText(WINDOW_WIDTH-0.88*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-0.92*SMALL_BUTTON_HEIGHT,
            0, 0, 0);
    }

    static bool INTRO_BACKSTORY_SHOW = true;
    DialogBox introBackstory(window, 0, "Hmm... a barista here this late? Strange.\n"
        "But it's good to know there are other people here! I should see what they know");
    if (INTRO_BACKSTORY_SHOW)
        introBackstory.drawDialogBox(clock, finish); 


    // Pencil Trigger
    Button pencilTrigger(window, PENCIL_XPOS-20, PENCIL_YPOS-25, 0.7*PENCIL_TRIGGER_WIDTH, PENCIL_TRIGGER_HEIGHT);


    //Pencil pick up dialog box
    static bool PENCIL_PICKUP_BOX_SHOW = false;
    DialogBox pencilPickUp(window, 1, "Pick Up", PENCIL_XPOS-20+0.7*PENCIL_TRIGGER_WIDTH, PENCIL_YPOS-25);
    if (PENCIL_PICKUP_BOX_SHOW)
        pencilPickUp.drawDialogBox();


    //barista trigger and chai tea hint
    Button baristaTrigger(window,BARISTA_XPOS, BARISTA_YPOS, BARISTA_TRIGGER_WIDTH, BARISTA_TRIGGER_HEIGHT);


    // Chai Tea Hint
    static bool CHAI_TEA_HINT_SHOW = false;
    DialogBox chaiHint(window, 0, "Probably should order a chai tea at the register.");
    if (CHAI_TEA_HINT_SHOW)
        chaiHint.drawDialogBox(clock, finish);


    //paper trigger
    Button paperTrigger(window,PAPER_XPOS, PAPER_YPOS, PAPER_TRIGGER_WIDTH, PAPER_TRIGGER_HEIGHT);


    // Crypt Key Hint
    static bool CRYPTOGRAPHY_KEY_SHOW = false;
    DialogBox cryptKeyHint(window, 0, "\"a=%, c=#, e=Z, h=4, i=@, o=7, r=?, t=$, x=Q.\"\n\nHmm...");
    if (CRYPTOGRAPHY_KEY_SHOW)
        cryptKeyHint.drawDialogBox(clock, finish);


    // register trigger and crypt puzzle
    Button registerTrigger(window,REGISTER_XPOS, REGISTER_YPOS, REGISTER_TRIGGER_WIDTH, REGISTER_TRIGGER_HEIGHT);


    // Register conversation
    static char REGISTER_DIALOG_SHOW = -1;
    string sentence;
    switch (REGISTER_DIALOG_SHOW) {
        case 0:
            sentence = "Me:  A strange cash register. Excuse me, do you know how to use this?";
            break;
        case 1:
            sentence = "Barista: .........";
            break;
        case 2:
            sentence = "Okay...Looks like I need to figure it out by myself.";
            break;
        case 3:
            sentence = "Ah...I really have a bad memory. Better to write it down.";
            break;
        default:
            sentence = "";
            break;
    }
    DialogBox registerDialog(window, 0, sentence);
    if (REGISTER_DIALOG_SHOW >= 0)
        registerDialog.drawDialogBox(clock, finish);


    // Initialize and Draw Keypad
    static bool PUZZLE_SHOW = false;
    static KeyPad cryptPuzzle(window, "#4%@ $Z%");
    if (PUZZLE_SHOW) {
        cryptPuzzle.drawKeyPad();
    }



    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            
            case sf::Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    short inventoryChoice = inventory.checkBounds(mousePos);

                    // Introductory backstory
                    if (INTRO_BACKSTORY_SHOW) {
                        if (finish && introBackstory.checkBounds(mousePos)) {
                            INTRO_BACKSTORY_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && introBackstory.checkBounds(mousePos))
                            finish = true;  
                        break;
                    }

                    // Chai Tea hint
                    else if (CHAI_TEA_HINT_SHOW) {
                        if (finish && chaiHint.checkBounds(mousePos)) {
                            CHAI_TEA_HINT_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && chaiHint.checkBounds(mousePos))
                            finish = true;  
                        break;
                    }

                    // Crypt Key hint
                    else if (CRYPTOGRAPHY_KEY_SHOW) {
                        if (finish && cryptKeyHint.checkBounds(mousePos)) {
                            CRYPTOGRAPHY_KEY_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && cryptKeyHint.checkBounds(mousePos))
                            finish = true; 
                        break;
                    }

                    // End Dialog
                    else if (PUZZLE_COMPLETE) {
                        if (finish && endDialogTeaRoom.checkBounds(mousePos)) {
                            finish = false;
                            NEXT_SHOW = true;
                            PUZZLE_COMPLETE = false;
                        }
                        else if (!finish && endDialogTeaRoom.checkBounds(mousePos))
                            finish = true;  
                        break;
                    }


                    if (PUZZLE_COMPLETE) {
                    }
                    // Barista Trigger
                    else if (baristaTrigger.checkBounds(mousePos)) {
                        CHAI_TEA_HINT_SHOW = true;
                        clock.restart();
                    }
                    // Paper Trigger
                    else if (paperTrigger.checkBounds(mousePos)) {
                        CRYPTOGRAPHY_KEY_SHOW = true;
                        clock.restart();
                    }

                    // Register/Puzzle Trigger
                    else if (registerTrigger.checkBounds(mousePos) && REGISTER_DIALOG_SHOW == -1) {
                        REGISTER_DIALOG_SHOW++;
                        clock.restart();
                    }
                    // Register Dialog
                    if (REGISTER_DIALOG_SHOW >= 0) {
                        if (finish && registerDialog.checkBounds(mousePos)) {
                            if (REGISTER_DIALOG_SHOW >= 2) {
                                REGISTER_DIALOG_SHOW = -1;
                                PUZZLE_SHOW = true;
                            }
                            else {
                                REGISTER_DIALOG_SHOW++;
                            }
                            finish = false;
                            clock.restart();
                        }
                        else if (!finish && registerDialog.checkBounds(mousePos)) {
                            finish = true;
                        }
                        else   
                            break;
                    }


                    // Next Button
                    if (NEXT_SHOW && nextButton.checkBounds(mousePos)) {
                        state = 4;
                        finish = false;
                        PUZZLE_COMPLETE = true;
                        clock.restart();
                    }

                    // Close KeyPad
                    if (cryptPuzzle.checkCancelBounds(mousePos)) {
                        PUZZLE_SHOW = false;
                        cryptPuzzle.restorePuzzle();
                    }

                    
                    // Testing Inventory Response
                    if (inventoryChoice != -1) {
                        // Check whether the user is retrieving a tool in inventory
                        tempToolPtr = inventory.retrieveTool(inventoryChoice);
                        if (tempToolPtr != nullptr) {
                            dragging = true;
                        }
                    }

                    //pencil trigger -> pop up pick-up box
                    if (pencilTrigger.checkBounds(mousePos)) {
                        //pop up window here to have the user enter 112
                        if (pencil == nullptr) {
                            PENCIL_PICKUP_BOX_SHOW = true;
                        }       
                    }

                    //pencil pick-up and place in inventory
                    if (PENCIL_PICKUP_BOX_SHOW && pencilPickUp.checkBounds(mousePos)){
                        if (pencil == nullptr) {
                            pencil = new Tool(window, TOOL_LIST.at(PENCIL)+".png", PENCIL);
                            pencil->setShow(true);
                            PENCIL_PICKUP_BOX_SHOW = false;

                            if(!inventory.storeTool(PENCIL, pencil)){
                                cout << "Item stored failed! The inventory is full!" << endl;
                            }
                        }
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                        PENCIL_PICKUP_BOX_SHOW = false;
                        CRYPTOGRAPHY_KEY_SHOW = false;
                        CHAI_TEA_HINT_SHOW = false;
                }
                break;
            }  

            case sf::Event::MouseButtonReleased: {
                if (dragging)
                    dragging = false;
                break;
            }

            case sf::Event::KeyPressed: {
                if (PUZZLE_SHOW && pencil != nullptr) {
                    if (sf::Keyboard::isKeyPressed && cryptPuzzle.checkInputSize()) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (cryptPuzzle.checkPasswordMatch()) {
                                PUZZLE_SHOW = false;
                                cryptPuzzle.restorePuzzle();
                                PUZZLE_COMPLETE = true;
                                clock.restart();
                            }
                            else {
                                cryptPuzzle.restorePuzzle();
                                cryptPuzzle.setMessage();
                            }
                        }
                        else {
                            cryptPuzzle.storeUserInput(event);
                        }
                    }
                }
                else if (PUZZLE_SHOW && pencil == nullptr) {
                    REGISTER_DIALOG_SHOW = 3;
                }
            }
        }
    }  

};