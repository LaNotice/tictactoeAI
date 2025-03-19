#include "../include/system.hpp"

void event_manager (sf::RenderWindow* window, Game* g, int* diff) {
        sf::Event event;
        while (window->pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Q) { window->close(); }
			if (event.key.code == sf::Keyboard::Add) { if (*diff < 9) { *diff += 1; } }
			if (event.key.code == sf::Keyboard::Subtract) { if (*diff > 0) { *diff -= 1; } }
			if (event.key.code == sf::Keyboard::R) {
				for (int i = 0; i < 9; i++) { g->board[i] = 0; g->undo_move(); }
				g->turn = false;
			}
			if (event.key.code == sf::Keyboard::U) { g->undo_move(); }
			// Random AI Player
			if (event.key.code == sf::Keyboard::A) {
				std::vector<int> lmoves = g->legal_moves();
				if (lmoves.size() == 0) { std::cout << "the game ended, no move possible\n"; return; }
				int best_move_index;
				int best_eval;
				int nigga = 0;

				if (g->turn) {
					best_eval = 6;
				} else {
					best_eval = -6;
				}
				Game copy = copy_game(g);

				std::vector<int> eval;
				for (int i = 0; i < lmoves.size(); i++) {
					copy.play_move(lmoves[i]);
					int score = ai_move(&copy, *diff, -5, 5, &nigga);
					copy.undo_move();
					std::cout << "evaluate " << lmoves[i] << " to " << score << std::endl; 

					if (copy.turn && score <= best_eval) {
						best_eval = score;
						best_move_index = i;
					} else if (!copy.turn && score >= best_eval) {
						best_eval = score;
						best_move_index = i;
					}
				}
				std::cout << "play the move " << lmoves[best_move_index] << " with evaluation of " << best_eval << " after " << nigga << " nodes explored\n";
				g->play_move(lmoves[best_move_index]);
			}

			// AI Player
			if (event.key.code == sf::Keyboard::D) {}
                }

		// Human Player
                if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
				if (event.mouseButton.x >= 10 && event.mouseButton.x <= 460
					&& event.mouseButton.y >= 10 && event.mouseButton.y <= 460) {
					int move = click_to_move(event.mouseButton.x - 10, event.mouseButton.y - 10);
					if (g->is_legal(move)) {
						g->play_move(move);
					}
				}

                        }
                }
        }
}

void draw_status (sf::RenderWindow* window, Status s, int diff) {
	sf::Text text;
	sf::Text dif;

	sf::Font font;
	if (!font.loadFromFile("fonts/Vera.ttf")) { window->close(); std::cout << "Error while loading fonts\n"; }

	dif.setFont(font);
	dif.setCharacterSize(24);
	dif.setFillColor(sf::Color::Black);
	dif.setPosition(500, 300);
	std::string d = "difficulty : ";
	char di = (char)(diff + 0x30);
	dif.setString(d + di);
	window->draw(dif);

	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	text.setPosition(500, 150);

	if (s == ON_GOING) {
		text.setString("en cours...");
	} else if (s == DRAW) {
		text.setString("egalite");
	} else if (s == X_WIN) {
		text.setString("X gagne");
		text.setFillColor(sf::Color::Red);
	} else {
		text.setString("O gagne");
		text.setFillColor(sf::Color::Blue);
	}

	window->draw(text);
}

int click_to_move (int x, int y) {
	return y/150*3 + x/150;
}
