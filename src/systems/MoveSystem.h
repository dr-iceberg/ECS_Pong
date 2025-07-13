#pragma once
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
class MoveSystem
{
public:
	MoveSystem(sf::Vector2u _window_size, entt::registry& _registry);
	void update(const sf::Time deltatime);

private:
	entt::registry& registry;
	sf::Vector2u window_size;
};