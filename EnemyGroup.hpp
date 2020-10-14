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

    // SPIN THEM ALLLLLLLLLLLLLLLL
    void spin(Enemy &enemy);

    // Update all the health meters
    void updateHealthMeters(Enemy &enemy);

    // Whether anything has made contact with another thing
    void contact(Qube &qube, Enemy &enemy);

    // Move it. Seriously why did I put this comment here
    void move(Qube &qube, Enemy &enemy, int fps);

    // Do all the functions that are needed each loop
    void update(Qube &qube, int fps);

protected:
    // Dynamic array of all the enemies
    std::vector<Enemy> enemies;
private:
    // Draw all the enemies
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif