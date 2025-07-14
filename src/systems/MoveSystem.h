#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
class MoveSystem
{
public:
	MoveSystem(sf::Vector2u _window_size, entt::registry& _registry);
	void update(const sf::Time _deltatime);
	void onKeyPressed(const sf::Event::KeyPressed key_pressed);
	void onKeyReleased(const sf::Event::KeyReleased key_released) {};

private:
	entt::registry& registry;
	sf::Vector2u window_size;
	sf::Time deltatime = sf::Time::Zero;
};