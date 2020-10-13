#include "Enemy.hpp"

#include "RandGen.hpp"

Enemy::Enemy(unsigned int radius, unsigned int points, unsigned int lvl,
             sf::Vector2f coords)
    : Entity(coords, radius, Teams::Enemy, lvl, (lvl * 25)),
      enemy_body(radius, points) {
    enemy_body.setOutlineColor(sf::Color(0, 0, 0, 175));
    enemy_body.setOutlineThickness(1.3);
    enemy_body.setPosition(coordinates);
    enemy_body.setOrigin(radius, radius);
}

void Enemy::initialize(unsigned int r, unsigned int points, unsigned int lvl,
                       sf::Vector2f coords, int seed) {
    radius = r;
    coordinates = coords;
    team = Teams::Enemy;
    level = lvl;
    max_health = lvl * 25;
    health = max_health;
    health_meter = HealthBar(coords, r);
    seed = seed;

    enemy_body.setRadius(r);
    enemy_body.setPointCount(points);
    enemy_body.setFillColor(sf::Color(100, 17, 200, 100));
    enemy_body.setOutlineColor(sf::Color(0, 0, 0, 175));
    enemy_body.setOutlineThickness(1.3);
    enemy_body.setPosition(coordinates);
    enemy_body.setOrigin(radius, radius);
} // Dang, that's a lot of stuff

void Enemy::spin() { enemy_body.rotate(50 * ((level % 4) + 1)); }

void Enemy::draw(sf::RenderTarget &target,
                 sf::RenderStates states = sf::RenderStates::Default) const {
    if (health > 0) {
        target.draw(enemy_body, states);
        target.draw(health_meter, states);
    }
}

void Enemy::run(Entity &entity, int fps) {
    static sf::Vector2f move_dir;
    if (coordinates.x - entity.getCoordinates().x <= 250 &&
        coordinates.y - entity.getCoordinates().y <= 250) {

        enemy_body.setFillColor(sf::Color(199, 16, 16));

        if (move_dir != sf::Vector2f(0, 0))
            move_dir = sf::Vector2f(0, 0);

        if (coordinates.x - entity.getCoordinates().x <= 250) {
            if (coordinates.x < entity.getCoordinates().x)
                move_dir.x += 5 * (60.0F / fps);
            if (coordinates.x > entity.getCoordinates().x)
                move_dir.x -= 5 * (60.0F / fps);
        }

        if (coordinates.y - entity.getCoordinates().y <= 250) {

            if (coordinates.y < entity.getCoordinates().y)
                move_dir.y += 5 * (60.0F / fps);
            if (coordinates.y > entity.getCoordinates().y)
                move_dir.y -= 5 * (60.0F / fps);
        }
    } else {

        enemy_body.setFillColor(sf::Color(100, 17, 200, 100));

        if (move_clock.getElapsedTime() >= sf::seconds(3)) {
            move_dir = sf::Vector2f(
                           static_cast<int>(ran_gen::genRand(-100, 100, seed)) % 5,
                           static_cast<int>(ran_gen::genRand(-100, 100, seed)) % 5) *
                       (60.0F / fps);
            move_clock.restart();
        }
    }

    enemy_body.move(move_dir);
    coordinates = enemy_body.getPosition();
}

sf::FloatRect Enemy::getHitbox() { return enemy_body.getGlobalBounds(); }