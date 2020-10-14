////////////////////////////////////////////////////////////////
// This is for spawning in/doing things to all of the enemies //
////////////////////////////////////////////////////////////////

#ifndef ENEMYGROUP_HPP
#define ENEMYGROUP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.hpp"
#include "Qube.hpp"

class EnemyGroup : public sf::Drawable {
public:
    // Initialise enemy_count enemies
    EnemyGroup(int enemy_count, sf::RenderWindow &window);

    // Whether anything has made contact with another thing
    void contact(Qube &qube, Enemy &enemy);

    // Do all the functions that are needed each loop
    void update(Qube &qube, int fps, sf::RenderWindow &window);

    std::size_t getEnemyCount();

protected:
    // Dynamic array of all the enemies
    std::vector<Enemy> enemies;

private:
    // Draw all the enemies
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif