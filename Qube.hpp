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
    // initial coordinates, length, and width
    Qube(sf::Vector2f coords, std::string file, sf::RenderWindow &draw_window,
         int lvl);

    // Default constructor
    Qube();

    // run in a direction
    void run(sf::Vector2f &run_dir, sf::RenderWindow &window);

    // YOU SPIN ME RIGHT ROUND
    void spin(int fps);

    // Regenerate
    void regenerate();

    // Returns whether the entity is spinning
    bool isSpinning();

    // Get the speed of the spin
    float getSpinSpeed();

    void updateHealthMeter(sf::RenderWindow &window);

    // Get the hitbox
    sf::FloatRect getHitbox();

    // Angles of roation (combine and divide by 2 to get north-west, etc.)
    enum class FacingDirections : int {
        North = 0,
        East = 90,
        South = 180,
        West = 270,
    };

    // Whether the player is sprinting
    bool sprinting{};

protected:
    // Sprite for the hero
    sf::Sprite body{};

    // Large health meter
    HealthBar health_bar;
    // Speed of the rotation
    float rotate_speed{};

    // Is it healing??
    bool healing{false};

    // Whether qube is spinning
    bool spinning{};

    // Angle of direction Qube is facing
    float angle_rotation{};

    // Where to load sprite from
    sf::Texture hero_texture;

private:
    // Draw the sprite, entity health meter, and large health meter
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif