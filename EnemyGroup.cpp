#include "EnemyGroup.hpp"

EnemyGroup::EnemyGroup(int enemy_count, sf::RenderWindow &window)
    : enemies(enemy_count) {
    for (Enemy &iii : enemies) {
        iii.initialize(
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

void EnemyGroup::spin() {
    for (Enemy &iii : enemies) {
        iii.spin();
    }
}

void EnemyGroup::updateHealthMeters() {
    for (Enemy &iii : enemies) {
        iii.updateHealthMeter();
    }
}

// Need to overload if I will add other entities
void EnemyGroup::contact(Qube &qube) {
    if (qube.isSpinning()) {
        for (Enemy &iii : enemies) {
            if (iii.getHitbox().intersects(qube.getHitbox()))
                iii.damage(qube.getSpinSpeed() * .75F);
        }
    }
}

void EnemyGroup::draw(
    sf::RenderTarget &target,
    sf::RenderStates states = sf::RenderStates::Default) const {
    for (const Enemy &iii : enemies) {
        iii.draw(target, states);
    }
}