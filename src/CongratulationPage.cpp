#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "congratulationPage.hpp"

using namespace std;

// Waiting to be implemented
void congratulationPageActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    static bool finish(false);

    // Background
    Image background(window, "background_ILC_end.jpg");
    background.drawImg(-100, 0, 1.1, 1, WINDOW_WIDTH, WINDOW_HEIGHT, 120, 10);

    // Title
    Text titleSecondPage(window, "AndadaPro-Italic_wght.ttf", "You Escaped!", 120);
    titleSecondPage.drawText(0.33*WINDOW_WIDTH, 50, 200);

    // Next Button
    Button nextButton(window, (WINDOW_WIDTH - BUTTON_WIDTH)/2, (WINDOW_HEIGHT + 5.2*BUTTON_HEIGHT)/2,
            1.55*SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    Text nextButtonText(window, "Andada_Pro/static/AndadaPro-BoldItalic.ttf", "Back to Home Page", 40);

    // Backstory
    string story = "You successfully escaped! What an experience.\nBut what happened? Why nobody was in the ILC? "
        "The barista is so strange. Why the doors just closed \nand locked by themselves? Queen's University campus, " 
        "the only refuge in sight, the ILC. \nIs this a coincidence? I hope I still have enough time to study for tomorrow's "
        "midterm. I probably should \nreport this to someone...\nWait. I still remember a myth about the secret "
        "experiment conducted by Prof. Manjikian...\nIf that is real... !! ";
        
    Text backStory(window, "AndadaPro-Italic_wght.ttf", story, 42);
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
                        state = 0; 
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
    if (backStory.drawAnimatedText(clock, finish, 50, 260)) {   
        // this_thread::sleep_for(chrono::milliseconds(200));

        nextButton.drawButton();    
        nextButtonText.drawText((WINDOW_WIDTH - 0.9*BUTTON_WIDTH)/2, (WINDOW_HEIGHT + 5.6*BUTTON_HEIGHT)/2,
            0, 0, 0, 255);
    }
}
