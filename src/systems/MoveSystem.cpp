#include "MoveSystem.h"
#include "../components/Player.h"
#include <SFML/Graphics.hpp>


MoveSystem::MoveSystem(sf::Vector2u _window_size, entt::registry& _registry)
	:
	window_size{_window_size},
	registry{_registry}
{

}

void MoveSystem::update(const sf::Time _deltatime)
{
	deltatime = _deltatime;

	
	auto player_view = registry.view<Player, sf::RectangleShape>();
	player_view.each([&](Player& player, sf::RectangleShape& rect)
		{
			if (sf::Keyboard::isKeyPressed(player.up_key))
			{
				rect.move({ 0, -500.f * deltatime.asSeconds()});
			}
			else if (sf::Keyboard::isKeyPressed(player.down_key))
			{
				rect.move({ 0, 500.f * deltatime.asSeconds()});
			}

			if (rect.getPosition().y < 0)
			{
				rect.setPosition({ rect.getPosition().x, 0 });
			}
			else if (rect.getPosition().y  > window_size.y - rect.getSize().y)
			{
				rect.setPosition({ rect.getPosition().x, window_size.y - rect.getSize().y });
			}
		});
	
}

void MoveSystem::onKeyPressed(const sf::Event::KeyPressed key_pressed)
{
	
	auto player_view = registry.view<Player, sf::RectangleShape>();
	player_view.each([&](Player& player, sf::RectangleShape& rect)
		{
			if (key_pressed.code == player.up_key)
			{
				rect.move({ 0, -1000.f * deltatime.asSeconds() });
			}
			else if (key_pressed.code == player.down_key)
			{
				rect.move({ 0, 1000.f * deltatime.asSeconds() });
			}

			if (rect.getPosition().y < 0)
			{
				rect.setPosition({ rect.getPosition().x, 0 });
			}
			else if (rect.getPosition().y > window_size.y - rect.getSize().y)
			{
				rect.setPosition({ rect.getPosition().x, window_size.y - rect.getSize().y });
			}

		});
	

}
