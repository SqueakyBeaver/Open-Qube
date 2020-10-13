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
private:
    // Assigned to id
    static inline unsigned int x; // Should not be negative

public:
    // Id of the entity
    int entity_id{};

    Entity(sf::Vector2f &coords, float radius, Teams team, int lvl,
           int max_health);

    Entity();

    virtual ~Entity() {}

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
    float distFrom(Entity &entity);

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

    // The health meters of the entities
    HealthBar health_meter;
};

#endif