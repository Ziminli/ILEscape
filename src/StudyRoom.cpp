#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "StudyRoom.hpp"

using namespace std;

void studyRoomActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    // Animation Indicator
    static bool finish(false);

    // Study Room background
    Image studyRoomBackground(window, "study_room.png");
    studyRoomBackground.drawImg(-100, 0, 1.2, 1, WINDOW_WIDTH, WINDOW_HEIGHT, 200, 20);


    static Tool* sticks = nullptr;
    // General Tool Pointer
    static Tool* tempToolPtr = nullptr;
    // Static or Dynamic Positioning?
    static bool dragging = false;


    // Create Inventory 
    static Inventory inventory(window, INVENTORY_POS_X, INVENTORY_POS_Y);
    inventory.drawInventory();

    // Draw Sticks
    if (inventory.checkHasTool(STICKS)) {
        // Has and display sword?
        if (sticks != nullptr && sticks->getShow()) {
            drawInventoryTool(window, inventory, sticks, tempToolPtr, dragging);
        }
    } 

    // Bag visual
    Image bagVisual(window, "bag.png");
    bagVisual.drawImg(BAG_XPOS, BAG_YPOS, 1, 1 , 0.1*WINDOW_WIDTH, 0.1*WINDOW_HEIGHT, 180, 0);

    //laptop Visual
    Image laptop(window, "laptop.png");
    laptop.drawImg(LAPTOP_XPOS, LAPTOP_YPOS, 1, 1, 0.2*WINDOW_WIDTH, 0.2*WINDOW_HEIGHT, 160, 0);

    //Whiteboard Visual
    Image whiteboard(window, "whiteboard.png");
    whiteboard.drawImg(WHITEBOARD_XPOS, WHITEBOARD_YPOS,1, 1, 0.4*WINDOW_WIDTH,0.25*WINDOW_HEIGHT, 180, 0);

    //Lock Visual
    Image lock(window, "lock.png");
    lock.drawImg(570, 701, 1, 1, 0.04*WINDOW_WIDTH, 0.08*WINDOW_HEIGHT, 200, 0);

    // Stick Visual
    Image stick(window, "sticks.png");
    if (sticks == nullptr)
        stick.drawImg(STICKS_XPOS, STICKS_YPOS, 1, 1, 0.11*WINDOW_WIDTH, 0.11*WINDOW_HEIGHT, 200, 0);




    // Bag Trigger
    Button bagTrigger(window, BAG_XPOS+20, BAG_YPOS, BAG_TRIGGER_WIDTH, BAG_TRIGGER_HEIGHT);

    // Laptop Trigger
    Button laptopTrigger(window, LAPTOP_XPOS+65, LAPTOP_YPOS+55, LAPTOP_TRIGGER_WIDTH, LAPTOP_TRIGGER_HEIGHT);

    //Whiteboard Trigger
    Button whiteboardTrigger(window, WHITEBOARD_XPOS+25, WHITEBOARD_YPOS+25,
        WHITEBOARD_TRIGGER_WIDTH, WHITEBOARD_TRIGGER_HEIGHT);

    // Door Handle
    Button doorTrigger(window, 570, 730, 0.18*SMALL_BUTTON_WIDTH, 0.7*SMALL_BUTTON_HEIGHT);

    // Sticks Trigger
    Button sticksTrigger(window, STICKS_XPOS, STICKS_YPOS+30, STICKS_TRIGGER_WIDTH, STICKS_TRIGGER_HEIGHT);

    //Unrelated triggers
    //U doors
    Button udoorTrigger(window, UDOOR_XPOS, UDOOR_YPOS, UDOOR_TRIGGER_WIDTH, UDOOR_TRIGGER_HEIGHT);

    //U Windows
    Button uwindowTrigger(window, UWINDOW_XPOS, UWINDOW_YPOS, UWINDOW_TRIGGER_WIDTH, UWINDOW_TRIGGER_HEIGHT);

    //U AC 
    Button uacTrigger(window, UAC_XPOS, UAC_YPOS, UAC_TRIGGER_WIDTH, UAC_TRIGGER_HEIGHT);



    // Next Button
    static bool NEXT_SHOW = false;
    static bool WIN_SHOW = false;
    Button nextButton(window, WINDOW_WIDTH-1.38*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-1.35*SMALL_BUTTON_HEIGHT,
            SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    DialogBox escaped(window, 0, "Whew, finally! I don't know when they changed the doors to have passwords.\n"
        "I think now I should look around to see if there are others who are also in the ILC.");
    if (NEXT_SHOW){
        nextButton.drawButton();
        Text nextButtonText(window, "airstrikeacad.ttf", "Next", 45);
        nextButtonText.drawText(WINDOW_WIDTH-1.15*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-1.10*SMALL_BUTTON_HEIGHT,
            0, 0, 0, 255);
    }    
    if (WIN_SHOW)
        escaped.drawDialogBox(clock, finish);



    // Bag Hint
    static bool BAG_HINT_SHOW = false;
    DialogBox bagHint(window, 0, "A receipt...The owner of the bag bought some ice pops...");
    if (BAG_HINT_SHOW)
        bagHint.drawDialogBox(clock, finish);

    // Laptop Hint
    static bool SCREEN_SHOW = false;
    string screenHint;
    if (sticks == nullptr)
        screenHint = "Whose laptop? Nothing Special though...";
    else {
        screenHint = "Looks like the bag, the popsicle sticks, and the laptop are owned by the same person.\n"
            "Hmm...The room booking system says this person booked the room 112 and 388 at the same time..."
            "\nSomething doesn't feel right.";
    }
    DialogBox screen(window, 0, screenHint);
    if (SCREEN_SHOW)
        screen.drawDialogBox(clock, finish);

    // Whiteboard Hint
    static bool WHITEBOARD_HINT_SHOW = false;
    DialogBox whiteboardHint(window, 0, "Diagrams, bullet points about computer architecture...\n"
        "But why they say 0 is true and 1 is false...");
    if (WHITEBOARD_HINT_SHOW)
        whiteboardHint.drawDialogBox(clock, finish);

    // Sticks pick-up box
    static bool STICKS_PICKUP_BOX_SHOW = false;
    DialogBox sticksPickUp(window, 1, "Pick Up", STICKS_XPOS+STICKS_TRIGGER_WIDTH, STICKS_YPOS);
    if (STICKS_PICKUP_BOX_SHOW)
        sticksPickUp.drawDialogBox();

    // Door Hint
    static bool UDOOR_SHOW = false;
    DialogBox udoorHint(window, 0, "It's locked...I don't even remember the room number.");
    if (UDOOR_SHOW)
        udoorHint.drawDialogBox(clock, finish);

    // Window Hint
    static bool UWINDOW_SHOW = false;
    DialogBox uwindowHint(window, 0, "The corridor seems to be quiet, for now...");
    if (UWINDOW_SHOW)
        uwindowHint.drawDialogBox(clock, finish);
 
    // AC Hint
    static bool UAC_SHOW = false;
    DialogBox uacHint(window, 0, "The Central AC is still working...");
    if (UAC_SHOW)
        uacHint.drawDialogBox(clock, finish);




    // Introductory Backstory / Opening words
    static bool INTRO_BACKSTORY_SHOW = true;
    DialogBox studyRoomBackstory(window, 0, "What happened?! Why the door slamed and locked by itself? "
        "God, I still have a midterm tomorrow!\nI should probably Look around and see what I can get.");
    if (INTRO_BACKSTORY_SHOW)
        studyRoomBackstory.drawDialogBox(clock, finish);


    // Show Pzzule
    static bool PUZZLE_SHOW = false;
    // Initialize and Draw Keypad
    static KeyPad puzzle(window, "0112");
    if (PUZZLE_SHOW) {
        puzzle.drawKeyPad();
    }


    // //Return Button
    // Button returnButton(window,  WINDOW_WIDTH-7.8*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-1.35*SMALL_BUTTON_HEIGHT,
    //         SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    // returnButton.drawButton();

    // //Return Button
    // Text returnButtonText(window, "airstrikeacad.ttf", "Return", 45);
    // returnButtonText.drawText(WINDOW_WIDTH-7.7*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-1.10*SMALL_BUTTON_HEIGHT, 
    //     0, 0, 0, 255);
    



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
                        if (finish && studyRoomBackstory.checkBounds(mousePos)) {
                            INTRO_BACKSTORY_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && studyRoomBackstory.checkBounds(mousePos))
                            finish = true; 
                        break;
                    }

                    // Laptop Screen Hint
                    else if (SCREEN_SHOW) {
                        if (finish && screen.checkBounds(mousePos)) {
                            SCREEN_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && screen.checkBounds(mousePos))
                            finish = true;
                        break;
                    }

                    // Bag Hint 
                    else if (BAG_HINT_SHOW) {
                        if (finish && bagHint.checkBounds(mousePos)) {
                            BAG_HINT_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && bagHint.checkBounds(mousePos))
                            finish = true;
                        break;
                    }

                    // Whiteboard Hint
                    else if (WHITEBOARD_HINT_SHOW) {
                        if (finish && whiteboardHint.checkBounds(mousePos)) {
                            WHITEBOARD_HINT_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && whiteboardHint.checkBounds(mousePos))
                            finish = true;
                        break;
                    }

                    // Door Hint
                    else if (UDOOR_SHOW) {
                        if (finish && udoorHint.checkBounds(mousePos)) {
                            UDOOR_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && udoorHint.checkBounds(mousePos)) 
                            finish = true;
                        break;
                    }

                    // Window Hint 
                    else if (UWINDOW_SHOW) {
                        if (finish && uwindowHint.checkBounds(mousePos)) {
                            UWINDOW_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && uwindowHint.checkBounds(mousePos)) 
                            finish = true;
                        break;
                    }

                    // AC Hint
                    else if (UAC_SHOW) {
                        if (finish && uacHint.checkBounds(mousePos)) {
                            UAC_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && uacHint.checkBounds(mousePos)) 
                            finish = true;
                        break;
                    }
                    

                    //Laptop trigger check
                    if (WIN_SHOW) {
                    }
                    else if (laptopTrigger.checkBounds(mousePos)) {
                        SCREEN_SHOW = true;
                        clock.restart();
                    }

                    //Bag trigger check
                    else if (bagTrigger.checkBounds(mousePos)) {
                        BAG_HINT_SHOW = true;
                        clock.restart();
                    }

                    //Whiteboard trigger check
                    else if (whiteboardTrigger.checkBounds(mousePos)) {
                        WHITEBOARD_HINT_SHOW = true;
                        clock.restart();
                    }

                    //Udoor trigger check
                    else if (udoorTrigger.checkBounds(mousePos)) {
                        UDOOR_SHOW = true;
                        clock.restart();
                    }

                    //Uwindow trigger check
                    else if (uwindowTrigger.checkBounds(mousePos)) {
                        UWINDOW_SHOW = true;
                        clock.restart();
                    }

                    //Uac trigger check
                    else if (uacTrigger.checkBounds(mousePos)) {
                        UAC_SHOW = true;
                        clock.restart();
                    }

                    // Door/Puzzle Trigger
                    else if (doorTrigger.checkBounds(mousePos)) {
                        PUZZLE_SHOW = true;
                    }

                    // Close KeyPad
                    if (puzzle.checkCancelBounds(mousePos)) {
                        PUZZLE_SHOW = false;
                        puzzle.restorePuzzle();
                    }

                    //Buttons Next & Return
                    if (NEXT_SHOW && nextButton.checkBounds(mousePos)) {
                        state = 3;
                        finish = false;
                        clock.restart();
                    }

                    // if (returnButton.checkBounds(mousePos)) {
                    //     state = 1; 
                    //     finish = false;
                    //     clock.restart();
                    // }

                    // Escape check
                    if (WIN_SHOW) {
                        if (finish && escaped.checkBounds(mousePos)) {
                            WIN_SHOW = false;
                            NEXT_SHOW = true;
                            finish = false;
                        }
                        else if (!finish && escaped.checkBounds(mousePos))
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

                    // Testing Tool-inventory linking / Generating a tool
                    // Sword trigger -> Pop up pick-up box
                    if (sticksTrigger.checkBounds(mousePos)) {
                        if (sticks == nullptr) {
                            STICKS_PICKUP_BOX_SHOW = true;  
                        }       
                    }

                    // Check pick-up window for collecting the sword
                    if (STICKS_PICKUP_BOX_SHOW && sticksPickUp.checkBounds(mousePos)) {
                        sticks = new Tool(window, TOOL_LIST.at(STICKS) + ".png", STICKS);
                        sticks->setShow(true);
                        STICKS_PICKUP_BOX_SHOW = false;

                        if (!inventory.storeTool(STICKS, sticks)) {
                            cout << "Item stored failed! The inventory is full!" << endl;
                        }
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    STICKS_PICKUP_BOX_SHOW = false;
                    
                }
                break;
            }

            case sf::Event::MouseButtonReleased: {
                if (dragging == true) {
                    dragging = false;
                }
                break;
            }

            case sf::Event::KeyPressed: {
                if (PUZZLE_SHOW) {
                    if (sf::Keyboard::isKeyPressed && puzzle.checkInputSize()) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (puzzle.checkPasswordMatch()) {
                                PUZZLE_SHOW = false;
                                puzzle.restorePuzzle();
                                WIN_SHOW = true;
                                clock.restart();
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
// End of function studyRoomActions
