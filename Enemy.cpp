#include "Enemy.hpp"

#include "RandGen.hpp"

Enemy::Enemy(unsigned int radius, unsigned int points, unsigned int lvl,
             sf::Vector2f coords)
    : Entity(coords, radius, Teams::Enemy, lvl, (lvl * 25)),
      enemy_body(radius, points), move_dir() {
    enemy_body.setOutlineColor(sf::Color(0, 0, 0, 175));
    enemy_body.setOutlineThickness(1.3);
    enemy_body.setPosition(coordinates);
    enemy_body.setOrigin(radius, radius);
}

Enemy::Enemy() : enemy_body() {}

void Enemy::initialize(unsigned int r, unsigned int points, unsigned int lvl,
                       sf::Vector2f coords) {
    radius = r;
    coordinates = coords;
    team = Teams::Enemy;
    level = lvl;
    max_health = lvl * 25;
    health = max_health;
    health_meter = HealthBar(coords, r);

    enemy_body.setRadius(r);
    enemy_body.setPointCount(points);
    enemy_body.setFillColor(sf::Color(100, 17, 200, 100));
    enemy_body.setOutlineColor(sf::Color(0, 0, 0, 175));
    enemy_body.setOutlineThickness(1.3);
    enemy_body.setPosition(coordinates);
    enemy_body.setOrigin(radius, radius);
} // Dang, that's a lot of stuff

void Enemy::spin() { enemy_body.rotate(50 * ((level % 4) + 1)); }

void Enemy::run(Entity &entity, int fps) {
    static float one_direction_for{};
    if (std::sqrt((entity.getCoordinates().x - coordinates.x) *
                      (entity.getCoordinates().x - coordinates.x) +
                  (entity.getCoordinates().y - coordinates.y) *
                      (entity.getCoordinates().y - coordinates.y)) <= 650) {

        enemy_body.setFillColor(sf::Color(199, 16, 16, 200));

        if (coordinates.x < entity.getCoordinates().x)
            enemy_body.move(5.0F * (60.0F / fps), 0);
        if (coordinates.x > entity.getCoordinates().x)
            enemy_body.move(-5.0F * (60.0F / fps), 0);

        if (coordinates.y < entity.getCoordinates().y)
            enemy_body.move(0, 5.0F * (60.0F / fps));
        if (coordinates.y > entity.getCoordinates().y)
            enemy_body.move(0, -5.0F * (60.0F / fps));
    } else {
        if (move_dir == sf::Vector2f(0, 0) && one_direction_for == 0) {
            move_dir =
                sf::Vector2f(static_cast<int>(ran_gen::genRand(-100, 100)) % 5,
                             static_cast<int>(ran_gen::genRand(-100, 100)) % 5);
        }
        if (one_direction_for < 50 * (60.0F / fps)) {
            enemy_body.move(move_dir * (60.0F / fps));
            ++one_direction_for;
        }
        if (one_direction_for >= 50 * (60.0F / fps)) {
            one_direction_for = 0;
            move_dir = sf::Vector2f(0, 0);
        }
        enemy_body.setFillColor(sf::Color(100, 17, 200, 100));
    }
    coordinates = enemy_body.getPosition();
}

sf::FloatRect Enemy::getHitbox() { return enemy_body.getGlobalBounds(); }

void Enemy::draw(sf::RenderTarget &target,
                 sf::RenderStates states = sf::RenderStates::Default) const {
    if (health > 0) {
        target.draw(enemy_body, states);
        target.draw(health_meter, states);
    }
}