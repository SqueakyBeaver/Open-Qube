///////////////////////////////
// Class for all the enemies //
// Probably needs a rework   //
///////////////////////////////

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "HealthBar.hpp"

class Enemy : public sf::Drawable, public Entity {
public:
    // Constructor
    Enemy(unsigned int radius, unsigned int points, unsigned int lvl,
          sf::Vector2f coords);

    // I must appease the compiler gods
    Enemy();

    // Destroy the enemy
    void destroy();

    // Initialize after creation
    void initialize(unsigned int lvl, sf::Vector2f coords);

    // Move the enemy
    void run(Entity &entity, int fps, sf::RenderWindow &window);

    // Sping the enemy
    void spin(float factor);

    // Get the hitbox of the enemy
    sf::FloatRect getHitbox();

    // Draw the enemy
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    // Body of the enemy
    sf::CircleShape enemy_body;

private:
    // Gotta have it here
    sf::Vector2f move_dir;
};

#endif