#include "Game.h"
#include "components/Player.h"
#include "components/Position.h"

Game::Game()
    :
    window{ sf::VideoMode({ 1280, 720 }), "SFML works!" },
    move_system{ window.getSize(), registry },
    render_system{ window, registry}
{
    window.setFramerateLimit(144);

    // Add a player
    auto player = registry.create();
    registry.emplace<Player>(player, sf::Keyboard::Key::W, sf::Keyboard::Key::S);

    sf::RectangleShape shape{sf::Vector2f(10.f, 50.f)};
    shape.setPosition({ 10, 10 });
    shape.setFillColor(sf::Color::Green);

    registry.emplace<sf::RectangleShape>(player, shape);


}

void Game::run()
{


    while (window.isOpen())
    {
        deltatime = clock.restart();

        update();
        render();
    }

}


void Game::update()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }

    move_system.update(deltatime);


}

void Game::render()
{
    window.clear();

    render_system.render();


    window.display();
}
