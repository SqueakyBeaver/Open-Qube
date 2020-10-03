#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

#include "HealthBar.hpp"

class Enemy : public sf::Drawable
{
public:
    Enemy(unsigned int radius, unsigned int points, sf::Color edge_color, unsigned int lvl, sf::Vector2f coords);

    sf::CircleShape enemy_body;

    HealthBar health_meter;

    void findNextCoordinates();

    void run(sf::Vector2f run_dir);
    void spin();

private:
    //Level of enemy
    unsigned int level{};

    //Enemy's max health
    float max_health;

    //Enemy's current health
    float health{};

    //Current coordinates of the enemy
    sf::Vector2f coordinates;

    //Radius of enemy
    float radius{};

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const
    {
        target.draw(enemy_body, states);
        target.draw(health_meter, states);
    }
};

#endif