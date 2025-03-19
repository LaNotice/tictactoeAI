#include <cstdlib>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "include/system.hpp"

int main () {
	int DIFFICULTY = 9;

	std::srand(std::time(nullptr));
	sf::RenderWindow window(sf::VideoMode(800, 500), "Werks");
	sf::RectangleShape lines[4];
	for (int i = 0; i < 4; i++) {
		lines[i] = sf::RectangleShape(sf::Vector2f(450, 10));
		lines[i].setFillColor(sf::Color::Black);
		if (i >= 2) {
			lines[i].setRotation(90.f);
		}
	}

	lines[0].setPosition(10, 150);
	lines[1].setPosition(10, 300);
	lines[2].setPosition(150, 10);
	lines[3].setPosition(300, 10);


	sf::RectangleShape playground(sf::Vector2f(450, 450));
	playground.setPosition(10, 10);
	playground.setFillColor(sf::Color::Yellow);

	Game ttt = Game();

	while (window.isOpen()) {
		// clear
		window.clear(sf::Color::White);
		
		event_manager(&window, &ttt, &DIFFICULTY);
		// draw the game
		//window.draw(playground);
		for (int i = 0; i < 4; i++) { window.draw(lines[i]); }
		draw_status(&window, ttt.check_win(), DIFFICULTY);
		ttt.draw(&window);
		// display
		window.display();
	}

	return 0;
}

