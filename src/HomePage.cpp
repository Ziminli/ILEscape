#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Global.hpp"
#include "GUI.hpp"
#include "HomePage.hpp"

using namespace std;

void homePageActions(sf::RenderWindow& window, sf::Event& event, sf::Clock& clock) {
    Image background(window, "background_ILC.jpg");
    background.drawImg(-100, 0, 1.2);

    Button startButton(window, (WINDOW_WIDTH - BUTTON_WIDTH)/2, (WINDOW_HEIGHT - 0.8*BUTTON_HEIGHT)/2);
    startButton.drawButton();

    Button exitButton(window, (WINDOW_WIDTH - BUTTON_WIDTH)/2, (WINDOW_HEIGHT + 2.2*BUTTON_HEIGHT)/2);
    exitButton.drawButton();

    Text title(window, "OriginTech.ttf", "ILEscape", 260);
    title.drawText(360, 50);

    Text subtitle(window, "airstrike.ttf", "Can you escape?", 70);
    subtitle.drawText(620, 340);

    Text startButtonText(window, "airstrikeacad.ttf", "Start", 70);
    startButtonText.drawText((WINDOW_WIDTH - 0.7*BUTTON_WIDTH)/2, (WINDOW_HEIGHT - 0.4*BUTTON_HEIGHT)/2, 
        0, 0, 0, 255);

    Text exitButtonText(window, "airstrikeacad.ttf", "Exit", 70);
    exitButtonText.drawText((WINDOW_WIDTH - 0.5*BUTTON_WIDTH)/2, (WINDOW_HEIGHT + 2.6*BUTTON_HEIGHT)/2, 
        0, 0, 0, 255);

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Testing Mouse Click
                    // cout << mousePos.x << ", " << mousePos.y << endl;
                    // cout << "Start In bound?: " << startButton.checkBounds(mousePos) << endl;
                    // cout << "Exit In bound?: " << exitButton.checkBounds(mousePos) << endl;

                    if (startButton.checkBounds(mousePos)) {
                        state = 1;
                        clock.restart();
                    }
                    else if (exitButton.checkBounds(mousePos)) {
                        window.close();
                    }
                }
                break;
            }
        }
}

