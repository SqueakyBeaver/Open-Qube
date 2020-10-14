#include "EnemyGroup.hpp"
#include "RandGen.hpp"

EnemyGroup::EnemyGroup(int enemy_count, sf::RenderWindow &window)
    : enemies(enemy_count) {
    int seed{};
    for (Enemy &enemy : enemies) {
        enemy.initialize(
            ran_gen::genRand(40, 50), ran_gen::genRand(3, 13),
            ran_gen::genRand(1, 20),
            sf::Vector2f(
                ran_gen::genRand(300, 20 * window.getView().getSize().x - 300),
                ran_gen::genRand(300, 20 * window.getView().getSize().y - 300)),
            seed++);
        // To anyone who reads this: I am so very sorry
    }
}

void EnemyGroup::spin(Enemy &enemy) { enemy.spin(); }

void EnemyGroup::updateHealthMeters(Enemy &enemy) { enemy.updateHealthMeter(); }

// Need to overload if I will add other entities
void EnemyGroup::contact(Qube &qube, Enemy &enemy) {
    if (qube.isSpinning()) {
        if (enemy.getHitbox().intersects(qube.getHitbox()))
            enemy.damage(qube.getSpinSpeed() * .75F);
    }
}

void EnemyGroup::move(Qube &qube, Enemy &enemy, int fps) {
    enemy.run(qube, fps);
}

void EnemyGroup::update(Qube &qube, int fps) {
    for (Enemy &enemy : enemies) {
        move(qube, enemy, fps);
        spin(enemy);
        contact(qube, enemy);
        updateHealthMeters(enemy);
    }
}

void EnemyGroup::draw(
    sf::RenderTarget &target,
    sf::RenderStates states = sf::RenderStates::Default) const {
    for (const Enemy &enemy : enemies) {
        enemy.draw(target, states);
    }
}