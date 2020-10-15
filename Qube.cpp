#include "Qube.hpp"

#include <SFML/Graphics.hpp>
#include <cstdlib> //std::exit
#include <string>

#include <iostream> //need to debug

Qube::Qube(sf::Vector2f coords, std::string file, sf::RenderWindow &draw_window,
           int lvl)
    : Entity(coords, 40, Teams::Player, lvl, 100), health_bar(draw_window),
      hero_texture()

{

    if (!hero_texture.loadFromFile(file)) {
        std::exit(2);
    } else {
        qube_hero.setTexture(hero_texture);
        qube_hero.setOrigin(radius, radius);
        qube_hero.setPosition(draw_window.mapCoordsToPixel(coords).x,
                              draw_window.mapCoordsToPixel(coords).y);
    }

    health = 100;
    max_health = 100;
}

void Qube::run(sf::Vector2f &run_for) {
    float sprint_multi = 1;
    if (sprinting)
        sprint_multi = 10;
    qube_hero.move(run_for * sprint_multi);
    if (!spinning) {
        if (run_for.x || run_for.y) {
            if (run_for.x) {
                if (run_for.x > 0)
                    angle_rotation +=
                        static_cast<float>(FacingDirections::East);
                else if (run_for.x < 0)
                    angle_rotation +=
                        static_cast<float>(FacingDirections::West);
            }

            if (run_for.y) {
                if (run_for.y > 0)
                    angle_rotation +=
                        static_cast<float>(FacingDirections::South);
                else if (run_for.y < 0)
                    angle_rotation +=
                        static_cast<float>(FacingDirections::North);
            }

            if (run_for.x && run_for.y) {
                angle_rotation /= 2.0;

                if (run_for.x < 0 &&
                    run_for.y < 0) // Whoever looks at this: this is the only
                                   // way I could think of to make this work
                    angle_rotation = 315;
            }

            qube_hero.setRotation(angle_rotation);
            angle_rotation = 0;
        }
    }
    coordinates = qube_hero.getPosition();
    health_meter.update(max_health, health, coordinates, radius);
    run_for = sf::Vector2f(0, 0);
}

void Qube::spin(int fps) {
    static int rotated_for{};
    static float rotate_brake{};

    if (rotate_speed < 0)
        rotate_speed = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        rotate_brake += 25 * (60.0F / fps);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
        spinning = true;
        rotate_speed = rotated_for / 1.5 * (60.0F / fps);
    }
    if (spinning) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
            ++rotated_for;

            if (rotated_for < 90)
                rotate_speed = (level + rotated_for) * .75;
        }

        rotate_speed -= .2 * (60.0F / fps);

        if (rotated_for >= 115 &&
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (health > 0)
                health -= .2;
        }
        if (rotate_speed < 1) {
            spinning = false;
        }
    } else {
        rotate_speed = 0;
        rotated_for = 0;
        rotate_brake = 0;
    }
    if (rotate_speed - rotate_brake <= 0)
        spinning = false;
    else
        qube_hero.rotate(rotate_speed - rotate_brake);
}

void Qube::regenerate() {
    static sf::Time regen_start = sf::seconds(max_health / 20 / level);
    static sf::Clock regen_timer;

    if (!healing && health < max_health &&
        regen_timer.getElapsedTime() >= regen_start) {
        healing = true;
        regen_timer.restart();
    }
    if (healing) {
        if (regen_timer.getElapsedTime() >= sf::seconds(.5)) {
            if (health < max_health)
                health += level / max_health * 50;
            if (health >= max_health)
                health = max_health;

            regen_timer.restart();
        }
    }
    if (health == max_health)
        healing = false;
}

bool Qube::isSpinning() { return spinning; }

float Qube::getSpinSpeed() { return rotate_speed; }

void Qube::updateHealthMeter(sf::RenderWindow &window) {
    health_meter.update(max_health, health, coordinates, radius);
    health_bar.update(max_health, health, window);
}

sf::FloatRect Qube::getHitbox() { return qube_hero.getGlobalBounds(); }

void Qube::draw(sf::RenderTarget &target,
                sf::RenderStates states = sf::RenderStates::Default) const {
    target.draw(qube_hero, states);
    target.draw(health_bar, states);
    target.draw(health_meter, states);
}