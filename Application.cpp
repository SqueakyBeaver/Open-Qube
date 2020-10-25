#include "Application.hpp"

using sf::Keyboard;

Application::Application()
    : window(sf::VideoMode::getFullscreenModes()[0], "Qube's Adventure",
             sf::Style::Fullscreen),

      qube(window.mapPixelToCoords(
               sf::Vector2i(40, window.getView().getSize().y / 2)),
           "Qube-hero.png", window, 1),

      /*enemy(40, 5, sf::Color(50, 70, 180), 3,
            sf::Vector2f(window.getView().getSize().x / 2 + 50,
                         window.getView().getSize().y / 2)),*/

      enemies(500, window),

      modes(), calibri(), run_dir(0, 0), player_info(), start_text(),
      resized_view(), fps_clock() {

    if (!calibri.loadFromFile("calibri.ttf"))
        std::exit(2);

    start_text.setFont(calibri);
    start_text.setString("Press enter to start");

    player_info.setFont(calibri);
    player_info.setCharacterSize(18);
    player_info.setPosition(20, 20);

    player_info.setFillColor(sf::Color(255, 60, 17));
    start_text.setFillColor(sf::Color(60, 178, 200));

    modes = sf::VideoMode::getFullscreenModes();

    window.setVerticalSyncEnabled(true);
}

void Application::loopGame() {
    // Distance to run
    int run_distance{5};
    while (!(qube.getHealth() < 0 || enemies.getEnemyCount() <= 0) &&
           window.isOpen()) {
        if (Keyboard::isKeyPressed(Keyboard::Key::Backspace)) {
            qube.setHealth(0);
            break;
        }

        // Gather what happpened
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // Window closed
            case sf::Event::Closed:
                window.close();
                break;

            // Window was resized
            case sf::Event::Resized:
                resized_view.setViewport(sf::FloatRect(
                    0.f, 0.f, event.size.width, event.size.height));
                window.setView(sf::View(sf::FloatRect(
                    0.f, 0.f, event.size.width, event.size.height)));
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == Keyboard::Key::LShift)
                    qube.sprinting = true;
                break;

            case sf::Event::KeyReleased:
                if (event.key.code == Keyboard::Key::LShift)
                    qube.sprinting = false;
                break;

            default:
                break;
            }
        }

        player_info.setString(
            "X: " + std::to_string(qube.getCoordinates().x) +
            "\nY: " + std::to_string(qube.getCoordinates().y) + "\nHealth: " +
            std::to_string(qube.getHealth()) + "\nFps: " + std::to_string(fps));

        player_info.setPosition(window.mapPixelToCoords(sf::Vector2i(20, 20)));

        if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
            if (!resized) {

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
            window.clear(sf::Color(138, 127, 128));
            continue;
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Left) ||
            Keyboard::isKeyPressed(Keyboard::Key::A))
            run_dir.x -= run_distance;

        if (Keyboard::isKeyPressed(Keyboard::Key::Right) ||
            Keyboard::isKeyPressed(Keyboard::Key::D))
            run_dir.x += run_distance;

        if (Keyboard::isKeyPressed(Keyboard::Key::Up) ||
            Keyboard::isKeyPressed(Keyboard::Key::W))
            run_dir.y -= run_distance;

        if (Keyboard::isKeyPressed(Keyboard::Key::Down) ||
            Keyboard::isKeyPressed(Keyboard::Key::S))
            run_dir.y += run_distance;

        while (!started) {
            window.draw(start_text);
            window.display();
            started = Keyboard::isKeyPressed(Keyboard::Key::Enter);
        }

        // Update the player's thingies
        qube.regenerate();
        qube.updateHealthMeter(window);
        qube.run(run_dir, window);
        qube.spin(fps);

        enemies.update(qube, fps, window);

        moveView(run_dir);

        drawEntities();

        fps = std::floor(1 / fps_clock.restart().asSeconds());

        run_distance = (60.0F / fps) * 10;
    }
}

void Application::drawEntities() {
    window.clear(sf::Color(
        138, 127, 128)); // Hehe if I comment this out, things get weird

    window.draw(qube);
    window.draw(enemies);
    window.draw(player_info);

    window.display();
}

void Application::moveView(const sf::Vector2f &move_dir) {
    sf::View view = window.getView();

    if (qube.getCoordinates().x + move_dir.x >=
        window.mapPixelToCoords(sf::Vector2i(view.getSize()))
            .x) // Weird formatting, huh
        view.move(view.getSize().x, 0);

    if (qube.getCoordinates().x + move_dir.x <=
        window.mapPixelToCoords(sf::Vector2i(0, 0)).x)
        view.move(-view.getSize().x, 0);

    if (qube.getCoordinates().y + move_dir.y >=
        window.mapPixelToCoords(sf::Vector2i(view.getSize()))
            .y) // Again, very weird
        view.move(0, view.getSize().y);

    if (qube.getCoordinates().y + move_dir.y <=
        window.mapPixelToCoords(sf::Vector2i(0, 0)).y)
        view.move(0, -view.getSize().y);

    window.setView(view);
}

void Application::gameOver(sf::String &&end_string) {
    bool end{};
    sf::Text row1(end_string, calibri, 60);
    sf::Text row2("Press enter to continue", calibri);

    row1.setOrigin(
        row1.getGlobalBounds().left + row1.getGlobalBounds().width / 2.0F,
        row1.getGlobalBounds().top + row1.getGlobalBounds().height / 2.0F);

    row2.setOrigin(
        row2.getGlobalBounds().left + row2.getGlobalBounds().width / 2.0F,
        row2.getGlobalBounds().top + row2.getGlobalBounds().height / 2.0F);

    row1.setPosition(window.mapPixelToCoords(
        sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
    row1.setFillColor(sf::Color(60, 178, 200));

    row2.setPosition(window.mapPixelToCoords(sf::Vector2i(
        window.getSize().x / 2,
        window.getSize().y / 2 + row1.getGlobalBounds().height + 20)));
    row2.setFillColor(sf::Color(60, 178, 200, 100));

    while (!end) {
        end = Keyboard::isKeyPressed(Keyboard::Key::Enter);
        window.clear();
        window.draw(row1);
        window.draw(row2);
        window.display();
    }
    window.close();
}

void Application::endGame() {
    if (qube.getHealth() <= 0) {
        gameOver("You lost");
    } else if (enemies.getEnemyCount() == 0) {
        gameOver("You won");
    } else if (!window.isOpen()) {
        return;
    } else {
        gameOver("Idk what happened tbh");
    }
}