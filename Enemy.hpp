#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy
{
public:
    Enemy(unsigned int radius, unsigned int points, sf::Color edge_color, unsigned int lvl, sf::Vector2f coords);
    sf::CircleShape enemy_body;

    void findNextCoordinates();

    void run(sf::Vector2f run_dir);
    void spin();

private:
    unsigned int level{};
    float health{};
    sf::Vector2f coordinates;
};

#endif