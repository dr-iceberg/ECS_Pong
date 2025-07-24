#include "MoveSystem.h"
#include "../components/Player.h"
#include <SFML/Graphics.hpp>
#include "../components/Ball.h"
#include "../components/Velocity.h"
#include "../components/AI.h"


MoveSystem::MoveSystem(sf::Vector2u _window_size, entt::registry& _registry)
	:
	window_size{_window_size},
	registry{_registry}
{

}

void MoveSystem::update(const sf::Time _deltatime)
{
	deltatime = _deltatime;

	static const float player_vel = 500.f;
	
	auto player_view = registry.view<Player, sf::RectangleShape>();
	player_view.each([&](Player& player, sf::RectangleShape& rect)
		{
			if (sf::Keyboard::isKeyPressed(player.up_key))
			{
				rect.move({ 0, -player_vel * deltatime.asSeconds()});
			}
			else if (sf::Keyboard::isKeyPressed(player.down_key))
			{
				rect.move({ 0, player_vel * deltatime.asSeconds()});
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

	auto players_view = registry.view<sf::RectangleShape>();
	auto ball_view = registry.view<Ball, Velocity>();
	ball_view.each([&](Ball& ball, Velocity& vel)
		{
			const auto& ball_pos = ball.getPosition();
			const auto& ball_radius = ball.getRadius();

			ball.move({ vel.x * deltatime.asSeconds(), vel.y * deltatime.asSeconds()});
			

			// player and ai collision
			players_view.each([&](sf::RectangleShape& rect)
				{
					const auto& player_size = rect.getSize();
					const auto& player_pos = rect.getPosition();

					
					// right side of player
					if (ball_pos.x < player_pos.x + player_size.x 
						&& ball_pos.x > player_pos.x
						&& player_pos.y < ball_pos.y 
						&& ball_pos.y < player_pos.y + player_size.y)
					{
						vel.x = abs(vel.x);
						//ball.setPosition({ player_pos.x + player_size.x, ball_pos.y });
					}
					// left side of player, consider removing
					else if (player_pos.x + player_size.x > ball_pos.x + 2*ball_radius 
						&& ball_pos.x + 2 * ball_radius > player_pos.x
						&& player_pos.y < ball_pos.y 
						&& ball_pos.y < player_pos.y + player_size.y)
					{
						vel.x = abs(vel.x) * -1;
						//ball.setPosition({ player_size.x - 2 * ball_radius, ball_pos.y });
					}

					// lower side of player
					if (ball_pos.y < player_pos.y + player_size.y 
						&& ball_pos.y > player_pos.y
						&& player_pos.x < ball_pos.x 
						&& ball_pos.x < player_pos.x + player_size.x)
					{
						vel.y = abs(vel.y);
						//ball.setPosition({ ball_pos.x, player_pos.y + player_size.y });
					}
					// upper side of player
					else if (player_pos.y + player_size.y > ball_pos.y + 2 * ball_radius 
						&& ball_pos.y + 2 * ball_radius  > player_pos.y
						&& player_pos.x < ball_pos.x 
						&& ball_pos.x < player_pos.x + player_size.x)
					{
						vel.y = abs(vel.y) * -1;
						//ball.setPosition({  ball_pos.x, player_size.y - 2 * ball_radius });
					}
				});


			// wall collision

			if (ball_pos.x < 0)
			{
				vel.x = abs(vel.x);
				//ball.setPosition({ 0, ball_pos.y });
			}
			else if (ball_pos.x + 2 * ball_radius > window_size.x)
			{
				vel.x = abs(vel.x) * -1;
				//ball.setPosition({ window_size.x - 2*ball_radius, ball_pos.y });
			}

			if (ball_pos.y < 0)
			{
				vel.y = abs(vel.y);
				//ball.setPosition({ ball_pos.x ,0  });
			}
			else if (ball_pos.y + 2*ball_radius > window_size.y)
			{
				vel.y = abs(vel.y) * -1;
				//ball.setPosition({ ball_pos.x, window_size.y - 2*ball_radius });
			}
		});


	auto ai_view = registry.view<AI, sf::RectangleShape>();
	ai_view.each([&](AI& ai, sf::RectangleShape& rect)
		{
			const auto& ai_pos = rect.getPosition();
			const auto& ai_size = rect.getSize();

			ball_view.each([&](Ball& ball, Velocity& vel)
				{
					const auto& ball_pos = ball.getPosition();
					const auto& ball_radius = ball.getRadius();
					
					/*
					// old primitive system
					if (ai_pos.y < ball_pos.y)
					{
						rect.move({ 0, player_vel * deltatime.asSeconds() });
					}
					else if (ai_pos.y > ball_pos.y)
					{
						rect.move({ 0, -player_vel * deltatime.asSeconds() });
					}
					*/
					if (vel.x > 0)
					{
						sf::Vector2f predicted_pos = predictBallPos(deltatime);

						if (ai_pos.y < predicted_pos.y - (ai_size.y / 2.f))
						{
							rect.move({ 0, player_vel * deltatime.asSeconds() });
						}
						else if (ai_pos.y > predicted_pos.y - (ai_size.y / 2.f))
						{
							rect.move({ 0, -player_vel * deltatime.asSeconds() });
						}
					}
					else
					{
						if (ai_pos.y < window_size.y / 2.f - (ai_size.y / 2.f))
						{
							rect.move({ 0, player_vel * deltatime.asSeconds() });
						}
						else if (ai_pos.y > window_size.y / 2.f - (ai_size.y / 2.f))
						{
							rect.move({ 0, -player_vel * deltatime.asSeconds() });
						}
					}


				});


		});

	
}
// not used currently
[[deprecated("this function is an alternative way to handle movement which is not used currently")]]
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

sf::Vector2f MoveSystem::predictBallPos(const sf::Time& _deltatime)
{
	sf::Vector2f predicted_pos;

	auto ball_view = registry.view<Ball, Velocity>();
	ball_view.each([&](Ball& ball, Velocity& vel)
		{
			const auto& ball_pos = ball.getPosition();
			const auto& ball_radius = ball.getRadius();

			Velocity predicted_vel = vel;
			predicted_pos = ball_pos;

			while (predicted_pos.x + 2*ball_radius <= window_size.x)
			{
				predicted_pos.x = predicted_pos.x + predicted_vel.x * deltatime.asSeconds();
				predicted_pos.y = predicted_pos.y + predicted_vel.y * deltatime.asSeconds();


				if (predicted_pos.x < 0)
				{
					predicted_vel.x = abs(predicted_vel.x);
					
				}
				else if (predicted_pos.x + 2 * ball_radius > window_size.x)
				{
					predicted_vel.x = abs(predicted_vel.x) * -1;
					
				}

				if (predicted_pos.y < 0)
				{
					predicted_vel.y = abs(predicted_vel.y);
					
				}
				else if (predicted_pos.y + 2 * ball_radius > window_size.y)
				{
					predicted_vel.y = abs(predicted_vel.y) * -1;
					
				}
			}
		});


	return predicted_pos;
}
