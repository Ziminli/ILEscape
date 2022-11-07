#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "HomePage.hpp"

using namespace std;

void secondPageActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    static bool finish(false);

    // Title
    Text titleSecondPage(window, "AndadaPro-Italic_wght.ttf", "Backstory", 120);
    titleSecondPage.drawText(700, 50, 200);

    // Next Button
    Button nextButton(window, WINDOW_WIDTH-1.1*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-1.1*SMALL_BUTTON_HEIGHT,
            SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    Text nextButtonText(window, "AndadaPro-Italic_wght.ttf", "Next", 60);

    // Backstory
    string bs = "It is the night before an important midterm exam and the air is cold and damp. A heavy "
        "rain begins to fall,\n here on Queen's University campus, so you rush towards the only refuge"
        " in sight, the ILC. As you enter the\n building, you are suddenly aware of the suffocating silence"
        " - you are the only one in the building. The ILC\n is dark except for one study room and so you head "
        "that way. The moment you enter,\n the door slams shut behind you.\n \"Hello?\" you call out,\n but only "
        "silence answers you. You try the door handle but it is locked. If you look carefully, \nhowever, "
        "you will notice that the door can be unlocked with a passcode. Have a look around for hints,\n "
        "but hurry! You wouldn't want to miss your important midterm... ";
        
    Text backStory(window, "AndadaPro-Italic_wght.ttf", bs, 42);
    backStory.changeLineSpace(1.5);


    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (finish && nextButton.checkBounds(mousePos)) {
                        state = 2; 
                        finish = false;
                        clock.restart();
                    }
                    else
                        finish = true;
                }
                break;  
        }
    }

    // Display Next Button
    if (backStory.drawAnimatedText(clock, finish, 50, 250)) {   
        // this_thread::sleep_for(chrono::milliseconds(200));

        nextButton.drawButton();    
        nextButtonText.drawText(WINDOW_WIDTH-0.88*SMALL_BUTTON_WIDTH, WINDOW_HEIGHT-0.9*SMALL_BUTTON_HEIGHT,
            0, 0, 0, 255);
    }
}

