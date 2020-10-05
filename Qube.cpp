#include "Qube.hpp"

#include <SFML/Graphics.hpp>
#include <cstdlib> //std::exit
#include <string>

#include <iostream> //need to debug

Qube::Qube(sf::Vector2f coords, std::string file, sf::RenderWindow &draw_window)
    : coordinates(coords), health_bar(draw_window), health_meter(coords, 40),
      hero_texture()

{

    if (!hero_texture.loadFromFile(file)) {
        std::exit(2);
    } else {
        qube_hero.setTexture(hero_texture);
        qube_hero.setOrigin(radius, radius);
        qube_hero.setPosition(coords);
    }

    health = 100;
    max_health = 100;
}

void Qube::run(sf::Vector2f &run_for) {
    qube_hero.move(run_for);
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

void Qube::spin() {
    static int rotated_for{};
    static float rotate_speed{};

    if (rotate_speed < 0)
        rotate_speed = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) {
        if (rotate_speed < 25)
            rotate_speed = 0;
        rotate_speed -= 25;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
        spinning = true;
        rotate_speed = rotated_for / 1.5;
    }
    if (spinning) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
            ++rotated_for;

            if (rotated_for < 90)
                rotate_speed = rotated_for / 1.5;
        }

        if (rotated_for >= 90 ||
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
            rotate_speed -= 1.5;
            if (rotated_for >= 115 &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                if (health > 0)
                    health -= .2;
            }
        }
        if (!rotate_speed || rotate_speed < 1) {
            spinning = false;
        }
    } else {
        rotate_speed = 0;
        rotated_for = 0;
    }
    qube_hero.rotate(rotate_speed);
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

float Qube::getHealth() { return health; }