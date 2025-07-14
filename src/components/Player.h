#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player(sf::Keyboard::Key _up_key, sf::Keyboard::Key _down_key);
	
	const sf::Keyboard::Key up_key;
	const sf::Keyboard::Key down_key;
	int points = 0;
	
};