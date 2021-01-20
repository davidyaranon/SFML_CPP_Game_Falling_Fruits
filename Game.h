#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include "FruitTile.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>  
#include <unordered_map>
#include <SFML/Graphics.hpp>

class Game {
private:
	int score;
	int level;
	int bombCount;
	int passedCount;
	bool state;
public:
	Platform platform = Platform("Sprites/Platform.png", 215, 250, false, true, false);
	Game() { srand(time(NULL)); this->level = 1; this->score = 0; this->state = false; this->bombCount = 0; this->passedCount = 0; }
	~Game() {}
	std::vector<std::vector<std::unique_ptr<FruitTile>>> tiles; //2D vector containing fruit pointers
	void startLevel();
	void moveFruits();
	void incrementScore();
	void decrementScore();
	int getScore();
	int getLevel();
	int getFruitCount();
	int getPassedCount();
	void hasCollided();
	bool getState();
	void setState(bool);
	std::string generateFruitName();
};

#endif