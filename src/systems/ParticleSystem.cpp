#include "ParticleSystem.h"
#include "../components/Ball.h"
#include "../components/Velocity.h"


ParticleSystem::ParticleSystem(entt::registry& _registry)
	:
	registry{_registry}
{
	sf::RectangleShape shape{ sf::Vector2f(5.f, 5.f) };
	shape.setFillColor(sf::Color::White);

	particles.fill({shape, 0});
}

void ParticleSystem::update(const sf::Time _deltatime) 
{
	auto ball_view = registry.view<Ball, Velocity>();
	ball_view.each([&](Ball& ball, Velocity& vel)
		{
			auto pos = ball.getPosition();
			
		});
}

void ParticleSystem::render(sf::RenderWindow& window)
{
	for (const auto& p : particles)
	{
		if (p.lifetime > 0)
		{
			window.draw(p.shape);
		}
		
	}
}