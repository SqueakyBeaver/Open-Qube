///////////////////////////////
// Class for any health bars //
///////////////////////////////

#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class HealthBar : public sf::Drawable {
public:
    // Main health bar shape position set
    HealthBar(const sf::RenderWindow &window);

    // For the small entity meters
    HealthBar(sf::Vector2f &coordinates, float radius);

    HealthBar() : bar(), bar_outline() {};

    // For large health bar
    void update(float max_health, float current_health, sf::RenderWindow &window);

    // For mini health bar
    void update(float max_health, float current_health,
                const sf::Vector2f &coordinatess, float radius);

protected:
    sf::RectangleShape bar;
    sf::RectangleShape bar_outline;

private:
    virtual void
    draw(sf::RenderTarget &target,
         sf::RenderStates states = sf::RenderStates::Default) const {
        target.draw(bar_outline, states);
        target.draw(bar, states);
    }
};

#endif