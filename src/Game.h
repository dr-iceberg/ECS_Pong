#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "systems/MoveSystem.h"
#include "systems/RenderSystem.h"

class Game
{
public:
	Game();
	void run();
private:
	void update();
	void render();


	sf::RenderWindow window;
	sf::Clock clock;
	entt::registry registry;
	sf::Time deltatime = sf::Time::Zero;
	MoveSystem move_system;
	RenderSystem render_system;
	entt::dispatcher event_dispatcher;

	sf::Color bg_color{ 30, 30, 30 };

};