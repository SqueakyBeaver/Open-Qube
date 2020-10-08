#include "Entity.hpp"

Entity::Entity(sf::Vector2f &coords, float radius, Teams team, int lvl,
               int max_health)
    : entity_id(x++), coordinates(coords), scale(sf::Vector2f(1, 1)),
      radius(radius), team(team), level(lvl), health(max_health),
      max_health(max_health), health_meter(coords, radius),
      hitbox(coords.x - .8 * radius, coords.y - .8 * radius, radius * 2 * .8, radius * 2 * .8) {}

Entity::Entity()
    : entity_id(x++), coordinates(), scale(sf::Vector2f(1, 1)), radius(),
      team(), level(), health(), max_health(), health_meter(), hitbox() {}

sf::Vector2f Entity::getCoordinates() { return coordinates; }

float Entity::getRadius() { return radius; }

int Entity::getMaxHealth() { return max_health; }

void Entity::updateHealthMeter() {
    health_meter.update(max_health, health, coordinates, radius);
}

Teams Entity::getTeam() { return team; }

sf::FloatRect Entity::getHitbox() { return hitbox; }

void Entity::damage(float damage_by) { health -= damage_by; }