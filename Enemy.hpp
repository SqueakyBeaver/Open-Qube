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
                    sf::Vector2f coords);

    // Find coordinates if moving towards a specific entity
    sf::Vector2f findNextCoordinates(Entity &entity);

    void run(const sf::Vector2f &run_dir);

    void spin();

    virtual void
    draw(sf::RenderTarget &target,
         sf::RenderStates states) const;
};

#endif