#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Headers.hpp"

using namespace std;

unsigned char state = 0;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ILEscape", sf::Style::Close);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;

        window.clear();

        switch (state) {
            // Scene 1 - Home Page
            case 0:
                homePageActions(window, event, clock);
                break;
            // Scene 2 - Backstory (after clicking "Start")
            case 1:
                secondPageActions(window, event, clock);
                break;
            // Scene 3 - Study Room
            case 2:
                studyRoomActions(window, event, clock);
                break;

            // Scene 4 - Tea Room
            case 3:
                teaRoomActions(window, event, clock);
                break;

            // Scene 5 - The Workshop/Design Bay
            case 4:
                workshopActions(window, event, clock);
                break;

            // Scene 6 - Engineering Society Lounge
            case 5:
                engSocLoungeActions(window, event, clock);
                break;

            // Scene 7 - Tea Room
            case 6:
                congratulationPageActions(window, event, clock);
                break;
                
            default:
                break;
        }

        window.display();
    }

    return 0;
}

