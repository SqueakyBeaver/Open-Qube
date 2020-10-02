/*TODO
ADD SMALL HEALTH BAR ABOVE ENTITIES
*/

#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

class HealthBar : public sf::Drawable
{
public:
    HealthBar(const sf::RenderWindow &window); //Main health bar shape position set

    void update(float max_health, float current_health);

protected:
    sf::RectangleShape bar;
    sf::RectangleShape bar_outline;

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const
    {
        
        target.draw(bar_outline, states);
        target.draw(bar, states);
    }
};

#endif