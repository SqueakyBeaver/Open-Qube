#include "Enemy.hpp"

#include "RandGen.hpp"

Enemy::Enemy(unsigned int radius, unsigned int points, unsigned int lvl,
             sf::Vector2f coords)
    : Entity(coords, radius, Teams::Enemy, lvl, (lvl * 25)),
      body(radius, points), move_dir() {
    body.setOutlineColor(sf::Color(0, 0, 0, 175));
    body.setOutlineThickness(1.3);
    body.setPosition(coordinates);
    body.setOrigin(radius, radius);
}

Enemy::Enemy() : body() {}

void Enemy::destroy() { body.setRadius(0); }

void Enemy::initialize(unsigned int lvl, sf::Vector2f coords) {
    radius = lvl * 2;
    coordinates = coords;
    team = Teams::Enemy;
    level = lvl;
    max_health = lvl * 250;
    health = max_health;
    health_meter = HealthBar(coords, radius);

    body.setRadius(radius);
    body.setPointCount(rand_gen::genRand(3, 10));
    body.setFillColor(sf::Color(100, 17, 200, 100));
    body.setOutlineColor(sf::Color(0, 0, 0));
    body.setOutlineThickness(1.3);
    body.setPosition(coordinates);
    body.setOrigin(radius, radius);
} // Dang, that's a lot of stuff

void Enemy::attack(Entity &entity, sf::RenderWindow &window) {
    sf::Vector2f coord_diff = entity.getCoordinates() - coordinates;

    if (std::sqrt((coord_diff.x) * (coord_diff.x) +
                  (coord_diff.y) * (coord_diff.y)) >=
            window.getView().getSize().x / 3 &&
        std::sqrt((coord_diff.x) * (coord_diff.x) +
                  (coord_diff.y) * (coord_diff.y)) <=
            window.getView().getSize().x / 3 * 2) {
    }
}

void Enemy::run(Entity &entity, int fps, sf::RenderWindow &window) {
    static float one_direction_for{};
    float dist = std::sqrt((entity.getCoordinates().x - coordinates.x) *
                               (entity.getCoordinates().x - coordinates.x) +
                           (entity.getCoordinates().y - coordinates.y) *
                               (entity.getCoordinates().y - coordinates.y));

    if (dist < window.getView().getSize().x / 3 ||
        dist > window.getView().getSize().x / 3 * 2) {

        body.setFillColor(sf::Color(199, 16, 16, 200));
        /*
                if (coordinates.x < entity.getCoordinates().x - 10)
                    body.move(5.0F * (60.0F / fps), 0);
                if (coordinates.x > entity.getCoordinates().x + 10)
                    body.move(-5.0F * (60.0F / fps), 0);

                if (coordinates.y < entity.getCoordinates().y - 10)
                    body.move(0, 5.0F * (60.0F / fps));
                if (coordinates.y > entity.getCoordinates().y + 10)
                    body.move(0, -5.0F * (60.0F / fps));
        */
        if (coordinates.x > entity.getCoordinates().x)
            body.move(5 * (60.0F / fps), 0);

        if (coordinates.x < entity.getCoordinates().x)
            body.move(-5 * (60.0F / fps), 0);

        if (coordinates.y > entity.getCoordinates().y)
            body.move(0, 5 * (60.0F / fps));

        if (coordinates.y < entity.getCoordinates().y)
            body.move(0, -5 * (60.0F / fps));

    } else {
        if (move_dir == sf::Vector2f(0, 0) && one_direction_for == 0) {
            move_dir = sf::Vector2f(
                static_cast<int>(rand_gen::genRand(-100, 100)) % 5,
                static_cast<int>(rand_gen::genRand(-100, 100)) % 5);
        }
        if (one_direction_for < 50 * (60.0F / fps)) {

            if (coordinates.x - move_dir.x - radius >= 0 &&
                coordinates.y - move_dir.y - radius >= 0 &&
                coordinates.x + move_dir.x + radius <=
                    window.getView().getSize().y * 50 &&
                coordinates.y + move_dir.y + radius <=
                    window.getView().getSize().y * 50) { // Sorry

                body.move(move_dir * (60.0F / fps));
            } else {
                move_dir = sf::Vector2f(
                    static_cast<int>(rand_gen::genRand(-100, 100)) % 5,
                    static_cast<int>(rand_gen::genRand(-100, 100)) % 5);
            }
            ++one_direction_for;
        }
        if (one_direction_for >= 50 * (60.0F / fps)) {
            one_direction_for = 0;
            move_dir = sf::Vector2f(0, 0);
        }
        body.setFillColor(sf::Color(100, 17, 200, 100));
    }
    coordinates = body.getPosition();
}

sf::FloatRect Enemy::getHitbox() { return body.getGlobalBounds(); }

void Enemy::draw(sf::RenderTarget &target,
                 sf::RenderStates states = sf::RenderStates::Default) const {
    if (health > 0) {
        target.draw(body, states);
        target.draw(health_meter, states);
    }
}