#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "FruitTile.h"

FruitTile::FruitTile(std::string filePath, float x, float y, bool collided, bool type, bool passed) {
	if (!setupSprite(filePath)) {
		std::cout << "ERROR IN LOADING" << filePath << std::endl;
		return;
	}
	this->passed = passed;
	this->type = type;
	this->collided = collided;
	this->x = x;
	this->y = y;
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 60, 60));
	this->sprite.setScale(0.5, 0.5);
	this->pos = sf::Vector2f(x, y);
	this->sprite.setPosition(pos);
}

bool FruitTile::setupSprite(std::string filePath) {
	if (!this->texture.loadFromFile(filePath)) {
		return false;
	}
	this->texture.setSmooth(true);
	return true;
}

Platform::Platform(std::string filePath, float x, float y, bool collided, bool type, bool passed) : FruitTile(filePath, x, y, collided, type, passed) {}

void Platform::moveLeft() {
	this->sprite.move(-5, 0);
	this->x -= -5;
}

void Platform::moveRight() {
	this->sprite.move(5, 0);
	this->x += 5;
}