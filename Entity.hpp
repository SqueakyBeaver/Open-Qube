////////////////////////////////////////////////////////////////////////////////
//  So this is pretty much just for orginization and grouping                 //
//  This just groups all of the common elements of the Qube and Enemy classes //
////////////////////////////////////////////////////////////////////////////////

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
//#include <string>

#include "HealthBar.hpp"

// The team options (put here because everything that relies on this will
// include this file)
enum class Teams {
    Player,
    Enemy,
};

class Entity {
public:
    // Constructor
    Entity(sf::Vector2f &coords, float radius, Teams team, int lvl,
           int max_health);

    // Default constructor?
    Entity();

    // Get the coordinates
    sf::Vector2f getCoordinates(); // I gotta apease stuff

    // Get the radius
    float getRadius();

    // Get the max health
    int getMaxHealth();

    // Update the health meter
    void updateHealthMeter();

    // Get the team
    Teams getTeam();

    // Damage the entity
    void damage(float damage_by);

    // Distance from another entity
    float distFrom(
        Entity &entity); // Might not need (wish I had remembered this earlier)

    // Set the health (don't use a lot)
    void setHealth(float new_health);

    // More to come

protected:
    // Where the entity currently is
    sf::Vector2f coordinates;

    // Current scale of the entity
    sf::Vector2f scale;

    // Radius of entity
    float radius{};

    // Entity's team (player, enemy)
    Teams team;

    // Entity's level
    int level{1};

    // Entity's heath
    float health;

    // Entity's maximum health
    float max_health;

    // The health meters of the entity
    HealthBar health_meter;
};

#endif