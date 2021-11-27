#include <vector>
#include <iostream>
#include "FruitTile.h"
#include "Game.h"
#include <algorithm>


void Game::startLevel() {
	this->tiles.clear();
	this->state = true;
	float y, prev = -100;
	for (int i = 0; i < 9; i += 1) {
		std::vector<std::unique_ptr<FruitTile>> row;
		for (int j = 0; j < 8; j += 1) {
			do {
				y = -100 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (-1000 - (-100))));
			} while (y + 500 < prev || y - 500 > prev);
			prev = y;
			std::string fruit = generateFruitName();
			if (fruit == "Sprites/TNT.png") {
				std::unique_ptr<FruitTile> f(new FruitTile(fruit, 60 * j, y, false, false, false));
				row.emplace_back(std::move(f));
			}
			else {
				std::unique_ptr<FruitTile> f(new FruitTile(fruit, 60 * j, y, false, true, false));
				row.emplace_back(std::move(f));
			}
		}
		this->tiles.emplace_back(std::move(row));
	}
}

void Game::moveFruits() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			this->tiles[i][j]->sprite.move(0, 2.5); //Move function also moves rectangular bounds with it, making collisions super easy
			this->tiles[i][j]->y += 2.5;
			if (this->tiles[i][j]->y > 300 && !this->tiles[i][j]->passed) {
				this->tiles[i][j]->passed = true;
				this->passedCount++;
			}
		}
	}
}

std::string Game::generateFruitName() {
	int r = rand() % 6;
	std::string path = "";
	if (r == 0) {
		path = "Eggplant";
	}
	else if (r == 1) {
		path = "Orange";
	}
	else if (r == 2) {
		path = "Banana";
	}
	else if (r == 3) {
		path = "Apple";
	}
	else if (r == 4) {
		path = "Pepper";
	}
	else {
		path = "TNT";
		this->bombCount++;
	}
	return "Sprites/" + path + ".png";
}

void Game::incrementScore() {
	this->score ++;
}

void Game::decrementScore() {
	this->score -= 5;
	if (this->score < 0) {
		this->score = 0;
	}
}

int Game::getPassedCount() {
	return this->passedCount;
}

int Game::getLevel() {
	return this->level;
}

int Game::getScore() {
	return (this->score);
}

bool Game::getState() {
	return this->state;
}

void Game::setState(bool state) {
	this->state = state;
}

int Game::getFruitCount() {
	return 72 - this->bombCount;
}

void Game::hasCollided() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 8; j++) {
			if (this->tiles[i][j]->sprite.getGlobalBounds().intersects(this->platform.sprite.getGlobalBounds()) //FRUIT
				&& this->tiles[i][j]->collided == false
				&& this->tiles[i][j]->type == true) { //SFML collision detector using textureRect
				this->incrementScore();
				this->tiles[i][j]->collided = true;
			}
			else if (this->tiles[i][j]->sprite.getGlobalBounds().intersects(this->platform.sprite.getGlobalBounds()) //BOMB
				&& this->tiles[i][j]->collided == false
				&& this->tiles[i][j]->type == false) {
				this->decrementScore();
				this->tiles[i][j]->collided = true;
			}
		}
	}
}