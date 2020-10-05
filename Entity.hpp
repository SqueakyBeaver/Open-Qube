////////////////////////////////////////////////////////////////////////////////
//  So this is pretty much just for orginization and grouping                 //
//  This just groups all of the common elements of the Qube and Enemy classes //
////////////////////////////////////////////////////////////////////////////////

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "HealthBar.hpp"

class Entity {
private:
    static inline unsigned int x; // Should not be negative

public:
    int entity_id{};
    Entity(sf::Vector2f &coords, float radius, std::string team, int lvl,
           int max_health)
        : entity_id(x++), coordinates(), scale(sf::Vector2f(1, 1)),
          radius(radius), team(team), level(lvl), health(max_health),
          max_health(max_health), health_meter(coords, radius) {
    } // Sorry but I got errors

    virtual ~Entity() {}

    // Get the coordinates
    sf::Vector2f getCoordinates(); // I gotta apease stuff

    // More to come

protected:
    // Where the entity currently is
    sf::Vector2f coordinates;

    // Current scale of the entity
    sf::Vector2f scale;

    // Radius of entity
    float radius{};

    // Entity's team (player, enemy)
    std::string team;

    // Whether entity is spinning
    bool spinning{};

    // Entity's level
    int level{1};

    // Entity's heath
    float health;

    // Entity's maximum health
    float max_health;

    HealthBar health_meter;
};

#endif