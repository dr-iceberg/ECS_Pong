#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

class RenderSystem
{
public:
	RenderSystem(sf::RenderWindow& _window, entt::registry& _registry);
	void render();

private:
	sf::RenderWindow& window;
	entt::registry& registry;

};