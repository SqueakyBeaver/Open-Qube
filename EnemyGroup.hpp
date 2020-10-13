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

    ~EnemyGroup() = default;

    // SPIN THEM ALLLLLLLLLLLLLLLL
    void spin(Enemy &enemy);

    // Update all the health meters
    void updateHealthMeters(Enemy &enemy);

    void contact(Qube &qube, Enemy &enemy);

    void move(Qube &qube, Enemy &enemy, int fps);

    void update(Qube &qube, int fps);

private:
    // Dynamic array of all the enemies
    std::vector<Enemy> enemies;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif