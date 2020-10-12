#include "EnemyGroup.hpp"

EnemyGroup::EnemyGroup(int enemy_count, sf::RenderWindow &window)
    : enemies(enemy_count) {
    for (Enemy &enemy : enemies) {
        enemy.initialize(
            genRand(40, 50), genRand(3, 13), genRand(1, 20),
            sf::Vector2f(
                genRand(300, 20 * window.getView().getSize().x - 300),
                genRand(300, 20 * window.getView().getSize().y - 300)));
        // To anyone who reads this: I am so very sorry
    }
}

float EnemyGroup::genRand(float low, float high) {

    static std::mt19937_64 random_gen(std::time(0));
    std::uniform_real_distribution<double> generate(low, high);
    return generate(random_gen);
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

void EnemyGroup::move(Qube &qube, Enemy &enemy) {
    sf::Vector2f run_dir;

    run_dir = enemy.findNextCoordinates(qube);
    enemy.run(run_dir);
}

void EnemyGroup::update(Qube &qube) {
    for (Enemy &enemy : enemies) {
        spin(enemy);
        contact(qube, enemy);
       // move(qube, enemy);
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