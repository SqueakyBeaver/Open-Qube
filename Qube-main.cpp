/*
TODO:
HIT DETECTION
*/
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Application.hpp"
#include "Enemy.hpp"
#include "Qube.hpp"

// Uncomment when doing release
//#define NDEBUG

int main() {
    Application game_application;

    game_application.loopGame();

    return 0;
}
