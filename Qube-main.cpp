/*
TODO:
MAKE MAIN SHORTER
PUT MOST STUFF IN A CLASS
*/
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Qube.hpp"
#include "Enemy.hpp"

#include <cassert>  //for assert
#include <iostream> //need to debug

//Uncomment when doing release
//#define NDEBUG

//Constants:

//Factor of movement. Easier this way
constexpr double RUN_DISTANCE{5};

using sf::Keyboard;

void displayHealth(const sf::Vector2f &position, int health, int max_health);

int main()
{
    sf::Font calibri;

    if (!calibri.loadFromFile("../calibri.ttf"))
        return 2;
    sf::Text text("Press space to start", calibri);

    sf::Text coordinates;
    coordinates.setFont(calibri);
    coordinates.setCharacterSize(18);

    coordinates.setFillColor(sf::Color(255, 60, 17));
    text.setFillColor(sf::Color(60, 178, 200));

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    sf::VideoMode mode = modes[0];

    sf::RenderWindow window(mode, "Qube's Adventure", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);

    //Create the hero (image is in parent directory)
    Qube qube(sf::Vector2f(40, window.getView().getSize().y / 2), "../Qube-hero.png", window); //Ugh

    Enemy enemy(40, 5, sf::Color(50, 70, 180), 3,
                sf::Vector2f(window.getView().getSize().x / 2 + 50, window.getView().getSize().y / 2));

    //Running directions and stuff
    sf::Vector2f run_dir(0, 0);

    //A view
    sf::View resizedView;
    bool resized{};

    coordinates.setPosition(20, 20); //Setting it here because it shouldn't change

    bool start;
    while (window.isOpen())
    {
        //Start it
        //Gather what happpened
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                //Window closed
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                resizedView.setViewport(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
                window.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
                coordinates.setPosition(20, 20); // Could *possibly* change
                break;

            default:
                break;
            }
        }

        coordinates.setString("X: " + std::to_string(qube.qube_hero.getPosition().x) + "\nY: " +
                              std::to_string(qube.qube_hero.getPosition().y) + "\nHealth: " + std::to_string(qube.getHealth()));

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
        {
            if (!resized)
            {
                //window.
                window.create(modes[0], "Qube's Adventure", sf::Style::Default);
                window.setSize(sf::Vector2u(window.getSize().x, window.getSize().y - 30));
                window.setTitle("Qube's Adventure");
                window.setVerticalSyncEnabled(true);
                resized = true;
            }
            else
            {
                window.create(modes[0], "Qube's Adventure", sf::Style::Fullscreen);
                window.setSize(sf::Vector2u(window.getSize().x, window.getSize().y + 30));
                window.setVerticalSyncEnabled(true);
                resized = false;
            }
            continue;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::A))
            run_dir.x -= RUN_DISTANCE;

        if (Keyboard::isKeyPressed(Keyboard::Key::Right) || Keyboard::isKeyPressed(Keyboard::Key::D))
            run_dir.x += RUN_DISTANCE;

        if (Keyboard::isKeyPressed(Keyboard::Key::Up) || Keyboard::isKeyPressed(Keyboard::Key::W))
            run_dir.y -= RUN_DISTANCE;

        if (Keyboard::isKeyPressed(Keyboard::Key::Down) || Keyboard::isKeyPressed(Keyboard::Key::S))
            run_dir.y += RUN_DISTANCE;

        qube.regenerate(); //Pwease work?

        qube.health_bar.update(100, qube.getHealth());

        qube.spin();
        qube.run(run_dir);
        enemy.spin();

        window.clear(sf::Color(138, 127, 128, 200));

        window.draw(qube.qube_hero);
        window.draw(enemy.enemy_body);
        window.draw(qube.health_bar);
        window.draw(coordinates);

        window.display();

        while (!start)
        {

            window.draw(text);
            window.display();
            start = Keyboard::isKeyPressed(Keyboard::Key::Space);
        }
    }

    return 0;
}
