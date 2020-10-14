/////////////////////////////////////////////
// Class that holds main application works //
// Really probably needs a rework          //
/////////////////////////////////////////////

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <vector>

#ifndef NDEBUG
#include <cassert>
#endif

#include "EnemyGroup.hpp"
#include "Qube.hpp"

class Application {
public:
    // initialize the game
    Application();

    // Main game loop
    void loopGame();

    // Draw the drawable things
    void drawEntities();

    // Move the window
    void moveView(const sf::Vector2f &move_dir);

    void gameOver(sf::String &&end_string);

    // end the game
    ~Application();

protected:
    // Window to draw to
    sf::RenderWindow window;

    // The main character
    Qube qube;

    // The enemies
    EnemyGroup enemies;

    // If the window is resized
    bool resized{};

    // Whether the game has started
    bool started{};

    // Modes
    std::vector<sf::VideoMode> modes;

    // Font
    sf::Font calibri;

    // Running directions
    sf::Vector2f run_dir;

    // Coordinates/Player info
    sf::Text player_info;

    // Starting text
    sf::Text start_text;

    // View for a resized window
    sf::View resized_view;

    // Clock for the fps
    sf::Clock fps_clock;

    // The fps variable
    int fps{60};
};

#endif