/*
TODO:
MAKE MAIN SHORTER
PUT MOST STUFF IN A CLASS
*/
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Application.hpp"
#include "Qube.hpp"
#include "Enemy.hpp"

//Uncomment when doing release
//#define NDEBUG

int main()
{
    Application game_application;

    game_application.loopGame();

    return 0;
}
