#pragma once
#include <SFML/System.hpp>
#include <entt/entt.hpp>
#include "../components/Particle.h"
#include <array>

class ParticleSystem
{
public:
	ParticleSystem(entt::registry& _registry);
	void update(const sf::Time _deltatime);
	void render(sf::RenderWindow& window);
private:
	entt::registry& registry;
	std::array<Particle, 10> particles;

};