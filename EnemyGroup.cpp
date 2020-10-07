#include "EnemyGroup.hpp"

EnemyGroup::EnemyGroup(int enemy_count, sf::RenderWindow &window)
    : enemies(enemy_count) {
    for (Enemy &iii : enemies) {
        iii.initialize(
            genRand(30, 50), genRand(3, 13), genRand(1, 20),
            sf::Vector2f(
                genRand(100, 20 * window.getView().getSize().x - 100),
                genRand(100, 20 * window.getView().getSize().y - 100)));
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