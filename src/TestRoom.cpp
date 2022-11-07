#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "StudyRoom.hpp"

using namespace std;

void testRoomActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    static bool finish(false);
    /* Insert Background here
    *  Change the filename variable into the corresponding filename(std::string)
    */
    Image studyRoomBackground(window, "background_ILC.jpg");
    studyRoomBackground.drawImg(-100, 0, 1.2);

    // Testing tool triggers 
    // Each tool should have a corresponding trigger in the scene
    Button swordTrigger(window,200,200);
    swordTrigger.setFillColor(sf::Color(255,255,255,50));
    swordTrigger.setOutlineColor(sf::Color::Transparent);
    swordTrigger.drawButton();

    // Create Inventory 
    static Inventory inventory(window, INVENTORY_POS_X, INVENTORY_POS_Y);
    inventory.drawInventory();

    // Testing Tool Class through manipulating the sword
    // Add tools whenever is needed
    static Tool* sword = nullptr;
    static Tool* ladder = nullptr;
    // General Tool Pointer
    static Tool* tempToolPtr = nullptr;
    // Static or Dynamic Positioning?
    static bool dragging = false;

    // Testing Dialog Boxes
    // Introductory Backstory
    static bool INTRO_BACKSTORY_SHOW = true;
    DialogBox testBackstory(window, 0, "Looking around and see what you can get.");
    if (INTRO_BACKSTORY_SHOW)
        testBackstory.drawDialogBox(clock, finish);

    // Tool pick-up box
    static bool SWORD_PICKUP_BOX_SHOW = false;
    DialogBox swordPickUp(window, 1, "Pick Up", 200+BUTTON_WIDTH, 200);
    if (SWORD_PICKUP_BOX_SHOW)
        swordPickUp.drawDialogBox();


    // Door/puzzle trigger
    static bool PUZZLE_SHOW = false;
    Button doorTrigger(window,700,200);
    doorTrigger.setFillColor(sf::Color(255,255,255,50));
    doorTrigger.setOutlineColor(sf::Color::Transparent);
    doorTrigger.drawButton();

    // Initialize and Draw Keypad
    static KeyPad puzzle(window, "A123");
    if (PUZZLE_SHOW) {
        puzzle.drawKeyPad();
    }

    // Workbench Trigger
    static bool WORKBENCH_SHOW = false;
    Button workbenchTrigger(window,1100,200);
    workbenchTrigger.setFillColor(sf::Color(255,255,255,50));
    workbenchTrigger.setOutlineColor(sf::Color::Transparent);
    workbenchTrigger.drawButton();

    // Initialize Workbench
    static bool ASSEMBLE_BUTTON_SHOW = false;
    static Workbench workbench(window);
    if (WORKBENCH_SHOW) {
        workbench.drawWorkbench(ASSEMBLE_BUTTON_SHOW);
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
                        if (finish && testBackstory.checkBounds(mousePos))
                            INTRO_BACKSTORY_SHOW = false;
                        else if (!finish && testBackstory.checkBounds(mousePos)) 
                            finish = true;
                        else   
                            break;
                    }

                    // Testing Door/Puzzle Trigger
                    if (doorTrigger.checkBounds(mousePos)) {
                        PUZZLE_SHOW = true;
                    }

                    // Close KeyPad
                    if (puzzle.checkCancelBounds(mousePos)) {
                        PUZZLE_SHOW = false;
                        puzzle.restorePuzzle();
                    }

                    // Testing Workbench Trigger
                    if (workbenchTrigger.checkBounds(mousePos)) {
                        WORKBENCH_SHOW = true;
                    }
                    
                    // Testing Workbench
                    if (WORKBENCH_SHOW) {
                        // Close Workbench
                        if (workbench.checkCloseBounds(mousePos)) {
                            WORKBENCH_SHOW = false;
                            ASSEMBLE_BUTTON_SHOW = false;
                            inventory.collectBackTools();
                            workbench.clearTools();
                        }
                        // Assemble the tools
                        if (ASSEMBLE_BUTTON_SHOW && workbench.checkAssembleBounds(mousePos)) {
                            for (short id : WORKBENCH_TOOLS) {
                                inventory.removeTool(tempToolPtr);
                            }
                            workbench.clearTools();
                            
                            // Create ladder tool as the final assembly
                            if (ladder == nullptr) {
                                ladder = new Tool(window, TOOL_LIST.at(LADDER) + ".png", LADDER);
                                ladder->setShow(true);
                            
                                if (!inventory.storeTool(LADDER, ladder)) {
                                    cout << "Item stored failed! The inventory is full!" << endl;
                                }
                            }

                        }
                    }


                    // Testing Inventory Response
                    if (inventoryChoice != -1) {
                        cout << inventoryChoice << endl;

                        // Check whether the user is retrieving a tool in inventory
                        tempToolPtr = inventory.retrieveTool(inventoryChoice);
                        if (tempToolPtr != nullptr) {
                            dragging = true;
                        }
                        // Testing Removing a stored tool from the inventory
                        else if (inventoryChoice == 9 && dragging == false) {
                            tempToolPtr = inventory.retrieveTool(0);
                            if (tempToolPtr != nullptr) {
                                cout << TOOL_LIST.at(tempToolPtr->getID()) << " got removed" << endl;
                                inventory.removeTool(tempToolPtr);
                            }
                        }
                    }

                    // Testing Tool-inventory linking / Generating a tool
                    // Sword trigger -> Pop up pick-up box
                    if (swordTrigger.checkBounds(mousePos)) {
                        if (sword == nullptr) {
                            SWORD_PICKUP_BOX_SHOW = true;  
                        }       
                    }

                    // Check pick-up window for collecting the sword
                    if (SWORD_PICKUP_BOX_SHOW && swordPickUp.checkBounds(mousePos)) {
                        sword = new Tool(window, TOOL_LIST.at(SWORD) + ".png", SWORD);
                        sword->setShow(true);
                        SWORD_PICKUP_BOX_SHOW = false;

                        if (!inventory.storeTool(SWORD, sword)) {
                            cout << "Item stored failed! The inventory is full!" << endl;
                        }
                    }

                    // Adding other Tool Triggers Whenever Needed
                    
                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    SWORD_PICKUP_BOX_SHOW = false;
                    
                }
                break;
            }

            case sf::Event::MouseButtonReleased: {
                if (dragging) {
                    dragging = false;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (WORKBENCH_SHOW && workbench.checkBounds(mousePos)) {
                        tempToolPtr->setStatus(2);
                        workbench.addTool(tempToolPtr->getID());
                        ASSEMBLE_BUTTON_SHOW = workbench.checkToolComplete();
                    }
                }

                break;
            }


            case sf::Event::KeyPressed: {
                if (PUZZLE_SHOW) {
                    if (sf::Keyboard::isKeyPressed && puzzle.checkInputSize()) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (puzzle.checkPasswordMatch()) {
                                cout << "Escaped!" << endl;
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

    // Sword
    if (inventory.checkHasTool(SWORD)) {
        // Has and display sword?
        if (sword != nullptr && sword->getShow()) {
            drawInventoryTool(window, inventory, sword, tempToolPtr, dragging);
        }
    } 

    // Ladder
    if (inventory.checkHasTool(LADDER)) {
        // Has and display ladder?
        if (ladder != nullptr && ladder->getShow()) {
            drawInventoryTool(window, inventory, ladder, tempToolPtr, dragging);
        }
    }    


    // add other tools whenever needed
}
// End of function studyRoomActions


