#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "FruitTile.h"

int main(){
	float windowWidth = 480, windowHeight = 270;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "GAME");
	window.setFramerateLimit(60);

	Game game = Game();
	sf::Clock clock;
	sf::Text initText, score, finalScore, end;
	sf::Font font;
	bool restart = true;
	if (!font.loadFromFile("Texts/ARCADE.ttf")) {
		std::cout << "ERROR IN LOADING TEXT" << std::endl;
	}
	initText.setFont(font);
	initText.setString("PRESS ENTER TO START GAME");
	initText.setCharacterSize(24);
	initText.setPosition(sf::Vector2f(65, 120));
	initText.setFillColor(sf::Color::White);
	initText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	score.setFont(font);
	score.setString("0");
	score.setCharacterSize(24);
	score.setPosition(sf::Vector2f(5, 0));
	score.setFillColor(sf::Color::White);
	score.setStyle(sf::Text::Bold | sf::Text::Underlined);
	finalScore.setFont(font);
	finalScore.setString("0");
	finalScore.setCharacterSize(24);
	finalScore.setPosition(sf::Vector2f(65, 110));
	finalScore.setFillColor(sf::Color::White);
	finalScore.setStyle(sf::Text::Bold | sf::Text::Underlined);
	end.setFont(font);
	end.setString("END");
	end.setCharacterSize(24);
	finalScore.setPosition(sf::Vector2f(65, 110));
	finalScore.setFillColor(sf::Color::White);
	finalScore.setStyle(sf::Text::Bold | sf::Text::Underlined);

	while (window.isOpen()) {
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::LostFocus:
				std::cout << "GAME PAUSED" << std::endl;
				//game.pause();
				break;
			case sf::Event::GainedFocus:
				std::cout << "GAME UNPAUSED" << std::endl;
				//game.resume();
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Enter:
					if (!game.getState()) {
						std::cout << "ENTER WAS PRESSED" << std::endl;
						game.startLevel();
						game.setState(true);
					}
					break;
				}

			}
		}
		window.clear();
		if (game.getPassedCount() == 72) {
			game.setState(false);
		}
		if (game.getState()) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				game.platform.moveLeft();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				game.platform.moveRight();
			}
			window.draw(game.platform.sprite);
			score.setString(std::to_string(game.getScore()));
			window.draw(score);
			for (int i = 0; i < 9; i += 1) {
				for (int j = 0; j < 8; j += 1) {
					if(!game.tiles[i][j]->collided)
						window.draw(game.tiles[i][j]->sprite);
				}
			}
			game.moveFruits();
			game.hasCollided();
		}
		else if (game.getPassedCount() == 72) {
			if (restart) {
				restart = false;
				clock.restart();
			}
			sf::Time secs = clock.getElapsedTime();
			finalScore.setString("TOTAL FRUITS POSSIBLE: " + std::to_string(game.getFruitCount()) + "\nTOTAL SCORE: " + std::to_string(game.getScore()));
			if (secs.asSeconds() < 5) {
				window.draw(finalScore);
			}
			else {
				window.draw(end);
			}
		}
		else if(!game.getState()) {
			window.draw(initText);
		}

		window.display();
		
	}
	return EXIT_SUCCESS;
}