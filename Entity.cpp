#include "Entity.hpp"

sf::Vector2f Entity::getCoordinates() { return coordinates; }

float Entity::getRadius() { return radius; }

int Entity::getMaxHealth() { return max_health; }

void Entity::updateHealthMeter() {
    health_meter.update(max_health, health, coordinates, radius);
}