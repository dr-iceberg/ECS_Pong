#include "Game.h"
#include "components/Player.h"
#include "components/Position.h"
#include "components/Velocity.h"
#include "components/Ball.h"

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


    // Add a Ball
    auto ball = registry.create();

    Ball ball_shape;
    ball_shape.setRadius(10.f);
    ball_shape.setFillColor(sf::Color::White);
    ball_shape.setPosition({ window.getSize().x / 2.f, window.getSize().y / 2.f });
    Velocity ball_vel = { 600.f, 600.f };

    registry.emplace<sf::CircleShape>(ball, ball_shape);
    registry.emplace<Velocity>(ball, ball_vel);



    //event_dispatcher.sink<sf::Event::KeyPressed>().connect<&MoveSystem::onKeyPressed>(move_system);
    //event_dispatcher.sink<sf::Event::KeyReleased>().connect<&MoveSystem::onKeyReleased>(move_system);

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
    static bool focused = true;
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (event->is<sf::Event::FocusGained>())
        {
            focused = true;
        }
        else if (event->is<sf::Event::FocusLost>())
        {
            focused = false;
        }
        // using event dispatcher
        /*
        else if (event->is<sf::Event::KeyPressed>())
        {
            auto& ev = *event->getIf< sf::Event::KeyPressed>();
            event_dispatcher.trigger<const sf::Event::KeyPressed>(std::move(ev));
        }
        else if (event->is<sf::Event::KeyReleased>())
        {
            const auto& ev = *event->getIf< sf::Event::KeyReleased>();
            event_dispatcher.trigger<const sf::Event::KeyReleased>(std::move(ev));
        }*/
    }
    
    // when window is not focused we dont want to update the movements
    if (focused)
    {
        move_system.update(deltatime);
    }
    


}

void Game::render()
{
    window.clear();

    render_system.render();


    window.display();
}
