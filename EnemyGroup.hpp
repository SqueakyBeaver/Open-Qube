////////////////////////////////////////////////////////////////
// This is for spawning in/doing things to all of the enemies //
////////////////////////////////////////////////////////////////

#ifndef ENEMYGROUP_HPP
#define ENEMYGROUP_HPP

#include <SFML/Graphics.hpp>
#include <random>
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

    void move(Qube &qube, Enemy &enemy);

    void update(Qube &qube);

private:
    // Generate random numbers (may need to move)
    float genRand(float low, float high);

    // Dynamic array of all the enemies
    std::vector<Enemy> enemies;

    virtual void
    draw(sf::RenderTarget &target,
         sf::RenderStates states) const;
};

#endif