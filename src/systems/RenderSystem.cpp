#include "RenderSystem.h"

RenderSystem::RenderSystem(sf::RenderWindow& _window, entt::registry& _registry)
	:
	window{_window},
	registry{_registry}
{

}

void RenderSystem::render()
{
	auto render_view = registry.view<sf::RectangleShape>();
	render_view.each([&](sf::RectangleShape& rect)
		{
			window.draw(rect);
		});
}