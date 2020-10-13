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
    Enemy(unsigned int radius, unsigned int points, unsigned int lvl,
          sf::Vector2f coords);

    sf::CircleShape enemy_body;

    Enemy() : enemy_body(){};

    // Initialize after creation
    void initialize(unsigned int radius, unsigned int points, unsigned int lvl,
                    sf::Vector2f coords, int seed);

    // Move the enemy
    void run(Entity &entity, int fps);

    void spin();

    virtual void
    draw(sf::RenderTarget &target,
         sf::RenderStates states) const;

    sf::FloatRect getHitbox();

    private:
    sf::Clock move_clock;

    int seed{};
};

#endif