#include "HealthBar.hpp"

#include <iostream>
#include <cassert>

HealthBar::HealthBar(const sf::RenderWindow &window) : bar(), bar_outline()
{
    //only set basic shape, size, and color
    bar.setPosition(window.getSize().x / 4, 40);
    bar.setSize(sf::Vector2f((window.getSize().x / 4) * 2, 25));
    bar.setFillColor(sf::Color(255, 0, 0, 100));

    bar_outline.setFillColor(sf::Color::Transparent);
    bar_outline.setOutlineColor(sf::Color(0, 0, 100));
    bar_outline.setOutlineThickness(1.5F);
    bar_outline.setPosition((window.getSize().x / 4 - 2), 38);
    bar_outline.setSize(sf::Vector2f((((window.getSize().x / 4) * 2) + 4), 29));
}

void HealthBar::update(float max_health, float current_health)
{
    if (current_health > 0)
        bar.setScale(current_health / max_health, 1);
    else if (current_health <= 0)
        bar.setScale(0, 1);
}