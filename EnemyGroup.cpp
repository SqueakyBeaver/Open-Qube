#include "EnemyGroup.hpp"
#include "RandGen.hpp"

EnemyGroup::EnemyGroup(int enemy_count, sf::RenderWindow &window)
    : enemies(enemy_count) {
    for (Enemy &enemy : enemies) {
        enemy.initialize(
            rand_gen::genRand(5, 20),
            sf::Vector2f(
                rand_gen::genRand(300, 20 * window.getView().getSize().x - 300),
                rand_gen::genRand(300,
                                  20 * window.getView().getSize().y - 300)));
        // To anyone who reads this: I am so very sorry
    }
}

// Need to overload if I will add other entities
void EnemyGroup::contact(Qube &qube, Enemy &enemy) {
    if (enemy.getHitbox().intersects(qube.getHitbox())) {
        if (qube.isSpinning())
            enemy.damage(qube.getSpinSpeed() * .75F);
        else if (qube.getSpinSpeed() < 50)
            qube.damage(.25F);
    }
}

void EnemyGroup::update(Qube &qube, int fps, sf::RenderWindow &window) {
    for (Enemy &enemy : enemies) {
        if (enemy.getHealth() > 0) {
        enemy.run(qube, fps, window);
        contact(qube, enemy);
        enemy.updateHealthMeter();
        } else {
            enemy.destroy();
        }
    }
}

std::size_t EnemyGroup::getEnemyCount() { return enemies.size(); }

void EnemyGroup::draw(
    sf::RenderTarget &target,
    sf::RenderStates states = sf::RenderStates::Default) const {
    for (const Enemy &enemy : enemies) {
        enemy.draw(target, states);
    }
}