#include "Entity.hpp"

#include <cmath>

Entity::Entity(sf::Vector2f &coords, float radius, Teams team, int lvl,
               int max_health)
    : entity_id(x++), coordinates(coords), scale(sf::Vector2f(1, 1)),
      radius(radius), team(team), level(lvl), health(max_health),
      max_health(max_health), health_meter(coords, radius) {}

Entity::Entity()
    : entity_id(x++), coordinates(), scale(sf::Vector2f(1, 1)), radius(),
      team(), level(), health(), max_health(), health_meter() {}

sf::Vector2f Entity::getCoordinates() { return coordinates; }

float Entity::getRadius() { return radius; }

int Entity::getMaxHealth() { return max_health; }

void Entity::updateHealthMeter() {
    health_meter.update(max_health, health, coordinates, radius);
}

Teams Entity::getTeam() { return team; }

void Entity::damage(float damage_by) { health -= damage_by; }

float Entity::distFrom(Entity &entity) {
    return sqrt(((coordinates.x - entity.getCoordinates().x) *
                 (coordinates.x - entity.getCoordinates().x)) +
                ((coordinates.y - entity.getCoordinates().y) *
                 (coordinates.y - entity.getCoordinates().y)));
}