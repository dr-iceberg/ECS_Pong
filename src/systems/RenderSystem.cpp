#include "RenderSystem.h"
#include "../components/Ball.h"

RenderSystem::RenderSystem(sf::RenderWindow& _window, entt::registry& _registry)
	:
	window{_window},
	registry{_registry}
{

}

void RenderSystem::render()
{
	auto rect_view = registry.view<sf::RectangleShape>();
	rect_view.each([&](sf::RectangleShape& rect)
		{
			window.draw(rect);
		});
	auto ball_view = registry.view<Ball>();
	ball_view.each([&](Ball& ball)
		{
			window.draw(ball);
		});
}