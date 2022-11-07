#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "Workshop.hpp"

using namespace std;

// Waiting to be implemented
void workshopActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    static bool finish(false);

    // Insert Background here
    Image workshopBackground(window, "workshop.jpg");
    workshopBackground.drawImg(-100, 0, 1.2, 1, WINDOW_WIDTH, WINDOW_HEIGHT, 250);

    // Initialize items and temp ptr
    static Tool* fakeSword = nullptr;
    static Tool* wood = nullptr;
    static Tool* nails = nullptr;
    static Tool* hammer = nullptr;
    static Tool* tempToolPtr = nullptr;
    // Static / Dynamic Positioning 
    static bool dragging = false; 

    // Visual for Nails in the scene
    if (nails == nullptr) {
        Image nailsVisual(window, TOOL_LIST.at(NAILS)+".png");
        nailsVisual.drawImg(NAILS_XPOS, NAILS_YPOS-20, 1, 1, TOOL_HEIGHT-INVENTORY_OUTLINE_THICKNESS,
            TOOL_HEIGHT-INVENTORY_OUTLINE_THICKNESS, 255, 0);
    }

    // Visual for Hammer in the scene
    if (hammer == nullptr) {
        Image hammerVisual(window, TOOL_LIST.at(HAMMER)+".png");
        hammerVisual.drawImg(HAMMER_XPOS, HAMMER_YPOS+80, 1, 1, HAMMER_TRIGGER_WIDTH, HAMMER_TRIGGER_WIDTH, 160, 0, -80);
    }
   
    // Create Inventory
    static Inventory inventory(window, INVENTORY_POS_X, INVENTORY_POS_Y);
    inventory.drawInventory();


    // Table button -- need to adjust position to match table in photo
    static bool WORKBENCH_SHOW = false;
    Button workbenchTrigger(window, WINDOW_WIDTH-5.1*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-4.8*SMALL_BUTTON_HEIGHT,
            1.1*BUTTON_WIDTH, 0.8*BUTTON_HEIGHT);

    // puzzle display boolean
    static bool PUZZLE_SHOW = false;


    // Initialize Workbench
    static bool ASSEMBLE_BUTTON_SHOW = false;
    static Workbench workbench(window);
    if (!PUZZLE_SHOW && WORKBENCH_SHOW) {
        workbench.drawWorkbench(ASSEMBLE_BUTTON_SHOW);
    }


    //have fake sword?
    if (inventory.checkHasTool(FAKESWORD)) {
        // Has and display sword?
        if (fakeSword != nullptr && fakeSword->getShow()) {
            drawInventoryTool(window, inventory, fakeSword, tempToolPtr, dragging);
        }
    }

    // Have nails?
    if (inventory.checkHasTool(NAILS)){
        if (nails != nullptr && nails->getShow()) {
            drawInventoryTool(window, inventory, nails, tempToolPtr, dragging);
        }
    }

    // Have wood?
    if (inventory.checkHasTool(WOOD)){
        if (wood != nullptr && wood->getShow()) {
            drawInventoryTool(window, inventory, wood, tempToolPtr, dragging);
        }
    }
        
    // Have hammer?
    if (inventory.checkHasTool(HAMMER)){
        if (hammer != nullptr && hammer->getShow()) {
            drawInventoryTool(window, inventory, hammer, tempToolPtr, dragging);
        }
    }

    // Prev/Next Button and End Dialog box
    static bool END_DIALOG_SHOW(false);
    Button doorButton(window, WINDOW_WIDTH-1.1*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-1.1*SMALL_BUTTON_HEIGHT,
            SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    DialogBox endDialogWorkshop(window, 0, "I remember the EngSoc Lounge has something that is really useful...\n");
    if (fakeSword != nullptr) {
        if (END_DIALOG_SHOW)
            endDialogWorkshop.drawDialogBox(clock, finish);
        else {
            Text doorButtonText(window, "AndadaPro-Italic_wght.ttf", "Next", 60);
            doorButton.drawButton();
            doorButtonText.drawText(WINDOW_WIDTH-0.88*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-0.92*SMALL_BUTTON_HEIGHT,
                0, 0, 0);
        }
    }
    else {
        Text doorButtonText(window, "AndadaPro-Italic_wght.ttf", "Prev", 60);
        doorButton.drawButton();
        doorButtonText.drawText(WINDOW_WIDTH-0.88*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-0.92*SMALL_BUTTON_HEIGHT,
            0, 0, 0);
    }


    // Initialize and Draw Keypad
    static KeyPad puzzle(window, "QSET");
    if (PUZZLE_SHOW) {
        puzzle.drawKeyPad();
    }


    //Dialog Box relavent to room objective
    static bool WORKSHOP_INTRO_DISPLAY = true;
    DialogBox workshopIntro(window, 0, "Okay, let's see what we got here."); 
    if (WORKSHOP_INTRO_DISPLAY) {
        workshopIntro.drawDialogBox(clock, finish);
    }

    // Workshop Hints
    static bool WORKSHOP_HINT_SHOW = false;
    string hint;
    if (nails == nullptr) 
        hint = "Is that a space rover in the back?";
    else if (hammer == nullptr || wood == nullptr)
        hint = "I think I still lack some materials to build something useful.";
    else
        hint = "Hmm...I wonder what is the password...Probably something meaningful to this room";
    DialogBox workshopHint(window, 0, hint); 
    if (WORKSHOP_HINT_SHOW) {
        workshopHint.drawDialogBox(clock, finish);
    }


    // nail trigger
    Button nailsTrigger(window,NAILS_XPOS,NAILS_YPOS,NAILS_TRIGGER_WIDTH,NAILS_TRIGGER_HEIGHT);
    // Nail Pick-up Box
    static bool NAIL_PICKUP_BOX_SHOW = false;
    DialogBox nailPickUp(window, 1, "Pick Up", NAILS_XPOS+NAILS_TRIGGER_WIDTH, NAILS_YPOS);
    if (NAIL_PICKUP_BOX_SHOW)
        nailPickUp.drawDialogBox();


    // wood trigger
    Button woodTrigger(window,WOOD_XPOS,WOOD_YPOS,WOOD_TRIGGER_WIDTH,WOOD_TRIGGER_HEIGHT);
    // Wood Pick-up Box
    static bool WOOD_PICKUP_BOX_SHOW = false;
    DialogBox woodPickUp(window, 1, "Pick Up", WOOD_XPOS+WOOD_TRIGGER_WIDTH, WOOD_YPOS);
    if (WOOD_PICKUP_BOX_SHOW)
        woodPickUp.drawDialogBox();


    // hammer trigger
    Button hammerTrigger(window,HAMMER_XPOS,HAMMER_YPOS,HAMMER_TRIGGER_WIDTH,HAMMER_TRIGGER_HEIGHT);
    // Hammer Pick-up Box
    static bool HAMMER_PICKUP_BOX_SHOW = false;
    DialogBox hammerPickUp(window, 1, "Pick Up", HAMMER_XPOS+HAMMER_TRIGGER_WIDTH, HAMMER_YPOS);
    if (HAMMER_PICKUP_BOX_SHOW)
        hammerPickUp.drawDialogBox();

    

    while(window.pollEvent(event)){  
        switch(event.type){ 
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:                    
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    short inventoryChoice = inventory.checkBounds(mousePos);

                    // Introductory backstory
                    if (WORKSHOP_INTRO_DISPLAY) {
                        if (finish && workshopIntro.checkBounds(mousePos)) {
                            WORKSHOP_INTRO_DISPLAY = false;
                            finish = false;
                        }
                        else if (!finish && workshopIntro.checkBounds(mousePos))
                            finish = true; 
                        break;
                    }

                    // Hint
                    else if (WORKSHOP_HINT_SHOW) {
                        if (finish && workshopHint.checkBounds(mousePos)) {
                            WORKSHOP_HINT_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && workshopHint.checkBounds(mousePos))
                            finish = true;  
                        break;
                    }

                    // End Dialog
                    if (END_DIALOG_SHOW) {
                        if (finish && endDialogWorkshop.checkBounds(mousePos)) {
                            END_DIALOG_SHOW = false;
                            finish = false;
                        }
                        else if (!finish && endDialogWorkshop.checkBounds(mousePos))
                            finish = true;  
                        break;
                    }

                    // Door Button
                    if (!PUZZLE_SHOW && !WORKBENCH_SHOW && doorButton.checkBounds(mousePos)) {
                        if (fakeSword == nullptr) 
                            state = 3;
                        else
                            state = 5;
                        finish = false;
                        clock.restart();
                    }

                    // Testing Inventory Response
                    if (inventoryChoice != -1) {
                        // Check whether the user is retrieving a tool in inventory
                        tempToolPtr = inventory.retrieveTool(inventoryChoice);
                        if (tempToolPtr != nullptr) {
                            dragging = true;
                        }
                    }

                    // Nails trigger
                    if ((nails == nullptr) && nailsTrigger.checkBounds(mousePos)) {
                        NAIL_PICKUP_BOX_SHOW = true;
                    }
                    // Nails Pick-up Box
                    if (NAIL_PICKUP_BOX_SHOW && nailPickUp.checkBounds(mousePos)) {
                        if (nails == nullptr) {
                            nails = new Tool(window, TOOL_LIST.at(NAILS) + ".png", NAILS); 
                            nails->setShow(true);
                            NAIL_PICKUP_BOX_SHOW = false;
                            
                            if (!inventory.storeTool(NAILS, nails)) {
                                cout << "Item stored failed! The inventory is full!" << endl;
                            }  
                        }
                    }

                    // wood trigger
                    if ((wood == nullptr) && woodTrigger.checkBounds(mousePos)) {
                        WOOD_PICKUP_BOX_SHOW = true;
                    }
                    if (WOOD_PICKUP_BOX_SHOW && woodPickUp.checkBounds(mousePos)) {
                        if (wood == nullptr) {
                            wood = new Tool(window, TOOL_LIST.at(WOOD) + ".png",WOOD);
                            wood->setShow(true);
                            WOOD_PICKUP_BOX_SHOW = false;

                            if (!inventory.storeTool(WOOD, wood)) {
                                cout << "Item stored failed! The inventory is full!" << endl;
                            }
                        }       
                    }

                    // hammer trigger
                    if ((hammer == nullptr) && hammerTrigger.checkBounds(mousePos)) {
                        HAMMER_PICKUP_BOX_SHOW = true;
                    }
                    if (HAMMER_PICKUP_BOX_SHOW && hammerPickUp.checkBounds(mousePos)) {
                        if (hammer == nullptr) {
                            hammer = new Tool(window, TOOL_LIST.at(HAMMER) + ".png", HAMMER); 
                            hammer->setShow(true);
                            HAMMER_PICKUP_BOX_SHOW = false;

                            if (!inventory.storeTool(HAMMER, hammer)) {
                                cout << "Item stored failed! The inventory is full!" << endl;
                            } 
                        }
                    }


                    // Close KeyPad
                    if (PUZZLE_SHOW && !WORKBENCH_SHOW && puzzle.checkCancelBounds(mousePos)) {
                        PUZZLE_SHOW = false;
                        puzzle.restorePuzzle();
                        WORKSHOP_HINT_SHOW = true;
                        clock.restart();
                        break;
                    }

                    // workbench trigger
                    if (!WORKBENCH_SHOW && workbenchTrigger.checkBounds(mousePos)) {
                        PUZZLE_SHOW = true; //show the puzzle to access the workbench
                    }



                    // Testing Workbench
                    if (WORKBENCH_SHOW) {
                        // Close Workbench
                        if (workbench.checkCloseBounds(mousePos)) {
                            WORKBENCH_SHOW = false;
                            ASSEMBLE_BUTTON_SHOW = false;
                            inventory.collectBackTools();
                            workbench.clearTools();
                            if (fakeSword != nullptr) {
                                END_DIALOG_SHOW = true;
                                clock.restart();
                            }
                        }
                        // Assemble the tools
                        if (ASSEMBLE_BUTTON_SHOW && workbench.checkAssembleBounds(mousePos)) {
                            for (short id : WORKBENCH_TOOLS) {
                                tempToolPtr = inventory.retrieveTool(inventory.findTool(id));
                                inventory.removeTool(tempToolPtr);
                            }
                            workbench.clearTools();
                            
                            // Create fakesword tool as the final assembly
                            if (fakeSword == nullptr) {
                                fakeSword = new Tool(window, TOOL_LIST.at(FAKESWORD) + ".png", FAKESWORD);
                                fakeSword->setShow(true);
                            
                                if (!inventory.storeTool(FAKESWORD, fakeSword)) {
                                    cout << "Item stored failed! The inventory is full!" << endl;
                                }
                            }

                        }
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right) {
                    NAIL_PICKUP_BOX_SHOW = false;
                    HAMMER_PICKUP_BOX_SHOW = false;
                    WOOD_PICKUP_BOX_SHOW = false;
                }
                break;

            case sf::Event::MouseButtonReleased:
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

            case sf::Event::KeyPressed: {
                if (PUZZLE_SHOW) {
                    if (sf::Keyboard::isKeyPressed && puzzle.checkInputSize()) {
                        if (event.key.code == sf::Keyboard::Enter) {
                            if (puzzle.checkPasswordMatch()) {
                                PUZZLE_SHOW = false;
                                puzzle.restorePuzzle();
                                WORKBENCH_SHOW = true;
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
