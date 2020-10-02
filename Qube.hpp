#ifndef HERO_HPP
#define HERO_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib> //std::exit

#include "HealthBar.hpp"

class Qube
{
public:
    //initial coordinates, length, and width
    Qube(sf::Vector2f coords, std::string file, sf::RenderWindow &draw_window);

    //Qube's coordinates
    sf::Vector2f coordinates;

    //Sprite for the hero
    sf::Sprite qube_hero{};

    //Health meter
    HealthBar health_bar;

    //run in a direction
    void run(sf::Vector2f &run_for);

    //YOU SPIN ME RIGHT ROUND
    void spin();

    //Regenerate
    void regenerate();

    //Get the Health
    float getHealth();

    //Angles of roation (combine and divide by 2 to get north-west, etc.)
    enum class FacingDirections : int
    {
        North = 0,
        East = 90,
        South = 180,
        West = 270,
    };

protected:
    //Is it healing??
    bool healing{false};

    //Hero's max health
    float max_health{};

    //Hero's current health
    float health{};

    //Hero's current level
    unsigned int level{1};

    //Spinning stuff
    bool spinning{};
    float angle_rotation{};

    //Where to load sprite from
    sf::Texture hero_texture;
};

#endif