#include "HealthBar.hpp"

#include <cassert>
#include <iostream>

HealthBar::HealthBar(const sf::RenderWindow &window) : bar(), bar_outline() {
    // only set basic shape, size, and color
    bar.setPosition(sf::Vector2f(
        window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 4, 40))));
    bar.setSize(sf::Vector2f((window.getSize().x / 4) * 2, 25));
    bar.setFillColor(sf::Color(255, 0, 0, 100));

    bar_outline.setFillColor(sf::Color::Transparent);
    bar_outline.setOutlineColor(sf::Color(0, 0, 100));
    bar_outline.setOutlineThickness(1.5F);
    bar_outline.setPosition(bar.getPosition() - sf::Vector2f(2, 2));
    bar_outline.setSize(sf::Vector2f((((window.getSize().x / 4) * 2) + 4), 29));
}

HealthBar::HealthBar() : bar(), bar_outline() {}

// coordinates: Entity's coordinates
// Radius: radius of entitiy
HealthBar::HealthBar(sf::Vector2f &coordinates, float radius)
    : bar(), bar_outline() {
    // only set basic shape, size, and color
    bar.setPosition(sf::Vector2f(coordinates.x - (radius / 2),
                                 coordinates.y - radius - 20));
    bar.setSize(sf::Vector2f(radius, 5));
    bar.setFillColor(sf::Color(255, 0, 0));

    bar_outline.setFillColor(sf::Color::Transparent);
    bar_outline.setOutlineColor(sf::Color::Black);
    bar_outline.setOutlineThickness(.9F);
    bar_outline.setPosition(bar.getPosition() - sf::Vector2f(2, 2));
    bar_outline.setSize(sf::Vector2f(radius + 4, 9));
}

void HealthBar::update(float max_health, float current_health,
                       sf::RenderWindow &window) {
    if (current_health > 0)
        bar.setScale(current_health / max_health, 1);
    else if (current_health <= 0)
        bar.setScale(0, 1);

    bar.setPosition(
        window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 4, 40)));

    bar_outline.setPosition(bar.getPosition() - sf::Vector2f(2, 2));
}

void HealthBar::update(float max_health, float current_health,
                       const sf::Vector2f &coordinates, float radius) {

    bar.setPosition(sf::Vector2f(coordinates.x - (radius / 2),
                                 coordinates.y - radius - 20));

    bar_outline.setPosition(bar.getPosition() - sf::Vector2f(2, 2));

    if (current_health > 0)
        bar.setScale(current_health / max_health, 1);
    else if (current_health <= 0)
        bar.setScale(0, 1);
}

void HealthBar::draw(
    sf::RenderTarget &target,
    sf::RenderStates states = sf::RenderStates::Default) const {
    target.draw(bar_outline, states);
    if (bar.getScale().x > 0)
        target.draw(bar, states);
}