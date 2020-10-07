//////////////////////////////////////////////////
// This is the class for the player's character //
//////////////////////////////////////////////////

#ifndef QUBE_HPP
#define QUBE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib> //std::exit
#include <string>

#include "Entity.hpp"

#include "HealthBar.hpp"

class Qube : public sf::Drawable, public Entity {
public:
    // Default constructor
    Qube();

    // initial coordinates, length, and width
    Qube(sf::Vector2f coords, std::string file, sf::RenderWindow &draw_window,
         int lvl);

    // Sprite for the hero
    sf::Sprite qube_hero{};

    // Large health meter
    HealthBar health_bar;

    // run in a direction
    void run(sf::Vector2f &run_for);

    // YOU SPIN ME RIGHT ROUND
    void spin();

    // Regenerate
    void regenerate();

    // Get the Health
    float getHealth();

    // Angles of roation (combine and divide by 2 to get north-west, etc.)
    enum class FacingDirections : int {
        North = 0,
        East = 90,
        South = 180,
        West = 270,
    };

    bool sprinting{};

protected:
    // Is it healing??
    bool healing{false};

    // Angle of direction Qube is facing
    float angle_rotation{};

    // Where to load sprite from
    sf::Texture hero_texture;

private:
    virtual void
    draw(sf::RenderTarget &target,
         sf::RenderStates states = sf::RenderStates::Default) const {
        target.draw(qube_hero, states);
        target.draw(health_bar, states);
        target.draw(health_meter, states);
    }
};

#endif