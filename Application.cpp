#include "Application.hpp"

using sf::Keyboard;

const float RUN_DISTANCE{5};

Application::Application()
    : window(sf::VideoMode::getFullscreenModes()[0], "Qube's Adventure",
             sf::Style::Fullscreen),

      qube(window.mapPixelToCoords(
               sf::Vector2i(40, window.getView().getSize().y / 2)),
           "Qube-hero.png", window, 1),

      enemy(40, 5, sf::Color(50, 70, 180), 3,
            sf::Vector2f(window.getView().getSize().x / 2 + 50,
                         window.getView().getSize().y / 2)),

      modes(), calibri(), run_dir(0, 0), player_info(), start_text(),
      resized_view() {

    if (!calibri.loadFromFile("calibri.ttf"))
        std::exit(2);

    start_text.setFont(calibri);
    start_text.setString("Press space to start");

    player_info.setFont(calibri);
    player_info.setCharacterSize(18);
    player_info.setPosition(20, 20);

    player_info.setFillColor(sf::Color(255, 60, 17));
    start_text.setFillColor(sf::Color(60, 178, 200));

    modes = sf::VideoMode::getFullscreenModes();

    window.setVerticalSyncEnabled(true);
}

void Application::loopGame() {

    while (window.isOpen()) {
        // Start it
        // Gather what happpened
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // Window closed
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                resized_view.setViewport(sf::FloatRect(
                    0.f, 0.f, event.size.width, event.size.height));
                window.setView(sf::View(sf::FloatRect(
                    0.f, 0.f, event.size.width, event.size.height)));
                player_info.setPosition(20, 20); // Could *possibly* change
                break;

            default:
                break;
            }
        }

        player_info.setString(
            "X: " + std::to_string(qube.getCoordinates().x) +
            "\nY: " + std::to_string(qube.getCoordinates().y) +
            "\nHealth: " + std::to_string(qube.getHealth()));

        player_info.setPosition(window.mapPixelToCoords(sf::Vector2i(20, 20)));

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            if (!resized) {
                // window.
                window.create(modes[0], "Qube's Adventure", sf::Style::Default);
                window.setSize(
                    sf::Vector2u(window.getSize().x, window.getSize().y - 30));
                window.setTitle("Qube's Adventure");
                window.setVerticalSyncEnabled(true);
                resized = true;
            } else {
                window.create(modes[0], "Qube's Adventure",
                              sf::Style::Fullscreen);
                window.setSize(
                    sf::Vector2u(window.getSize().x, window.getSize().y + 30));
                window.setVerticalSyncEnabled(true);
                resized = false;
            }
            continue;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left) ||
            Keyboard::isKeyPressed(Keyboard::Key::A))
            run_dir.x -= RUN_DISTANCE;

        if (Keyboard::isKeyPressed(Keyboard::Key::Right) ||
            Keyboard::isKeyPressed(Keyboard::Key::D))
            run_dir.x += RUN_DISTANCE;

        if (Keyboard::isKeyPressed(Keyboard::Key::Up) ||
            Keyboard::isKeyPressed(Keyboard::Key::W))
            run_dir.y -= RUN_DISTANCE;

        if (Keyboard::isKeyPressed(Keyboard::Key::Down) ||
            Keyboard::isKeyPressed(Keyboard::Key::S))
            run_dir.y += RUN_DISTANCE;

        qube.regenerate(); // Pwease work?
        qube.health_bar.update(100, qube.getHealth(), window);

        qube.spin();
        qube.run(run_dir);
        enemy.spin();

        moveView(run_dir); // Need to rework some stuff

        drawEntities();

        while (!started) {

            window.draw(start_text);
            window.display();
            started = Keyboard::isKeyPressed(Keyboard::Key::Space);
        }
    }
}

void Application::drawEntities() {
    window.clear(sf::Color(138, 127, 128, 200));

    window.draw(qube);
    window.draw(enemy);
    window.draw(player_info);

    window.display();
}

void Application::moveView(const sf::Vector2f &move_dir) {
    sf::View view = window.getView();

    if (qube.getCoordinates().x + move_dir.x >=
        window.mapPixelToCoords(sf::Vector2i(view.getSize().x, 0))
            .x) // Weird formatting, huh
        view.move(view.getSize().x, 0);

    if (qube.getCoordinates().x + move_dir.x <=
        window.mapPixelToCoords(sf::Vector2i(0, 0)).x)
        view.move(-view.getSize().x, 0);

    if (qube.getCoordinates().y + move_dir.y >=
        window.mapPixelToCoords(sf::Vector2i(0, view.getSize().y))
            .y) // Again, very weird
        view.move(0, view.getSize().y);

    if (qube.getCoordinates().y + move_dir.y <=
        window.mapPixelToCoords(sf::Vector2i(0, 0)).y)
        view.move(0, -view.getSize().y);

    window.setView(view);
}