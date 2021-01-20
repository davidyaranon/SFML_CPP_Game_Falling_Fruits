#ifndef FRUITTILE_H
#define FRUITTILE_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class FruitTile {
public:
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;
	float x, y;
	bool type, collided, passed;
	FruitTile() { this->type = true;  this->collided = false; this->passed = false; this->x = 0; this->y = 0; }
	FruitTile(std::string, float, float, bool, bool, bool);
	bool setupSprite(std::string);
};

class Platform : public FruitTile {
public:
	Platform() : FruitTile() {}
	Platform(std::string, float, float, bool, bool, bool);
	void moveLeft();
	void moveRight();
};

#endif