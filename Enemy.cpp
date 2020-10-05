#include "Enemy.hpp"

Enemy::Enemy(unsigned int radius, unsigned int points, sf::Color body_color,
             unsigned int lvl, sf::Vector2f coords)
    : Entity(coords, radius, "Enemy", lvl, (lvl * 25)),
      enemy_body(radius, points) {
    body_color.a = 230;
    enemy_body.setFillColor(body_color);
    enemy_body.setOutlineColor(sf::Color(0, 0, 0, 175));
    enemy_body.setOutlineThickness(1.3);
    enemy_body.setPosition(coordinates);
    enemy_body.setOrigin(radius, radius);
}

void Enemy::spin() {
    enemy_body.rotate(5 *
                      level); // Damage will be calculated based on spin speed
    health_meter.update(max_health, health, coordinates, radius);
}