#include "Enemy.hpp"

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
                       sf::Vector2f coords) {
    radius = r;
    coordinates = coords;
    team = Teams::Enemy;
    level = lvl;
    max_health = lvl * 25;
    health = max_health;
    health_meter = HealthBar(coords, r);

    hitbox.left = (coords.x - .8 * radius);
    hitbox.top = (coords.y - .8 * radius);
    hitbox.height = (1.6 * radius);
    hitbox.width = (1.6 * radius);

    enemy_body.setRadius(r);
    enemy_body.setPointCount(points);
    enemy_body.setFillColor(sf::Color(100, 17, 200, 100));
    enemy_body.setOutlineColor(sf::Color(0, 0, 0, 175));
    enemy_body.setOutlineThickness(1.3);
    enemy_body.setPosition(coordinates);
    enemy_body.setOrigin(radius, radius);
} // Dang, that's a lot of stuff

void Enemy::spin() { enemy_body.rotate(50 * level); }

void Enemy::draw(sf::RenderTarget &target,
                 sf::RenderStates states = sf::RenderStates::Default) const {
    if (health > 0) {
        target.draw(enemy_body, states);
        target.draw(health_meter, states);
    }
}

sf::Vector2f Enemy::findNextCoordinates(Entity &entity) {

    static sf::Vector2f move_dir;
    if (coordinates.x < entity.getCoordinates().x)
        move_dir.x += 5;
    if (coordinates.x > entity.getCoordinates().x)
        move_dir.x -= 5;

    if (coordinates.y < entity.getCoordinates().y)
        move_dir.y += 5;
    if (coordinates.y > entity.getCoordinates().y)
        move_dir.y -= 5;

    return move_dir;
}

void Enemy::run(const sf::Vector2f &run_dir) {
    enemy_body.move(run_dir);
    coordinates += run_dir;
    hitbox.left = (coordinates.x - .8 * radius);
    hitbox.top = (coordinates.y - .8 * radius);
}