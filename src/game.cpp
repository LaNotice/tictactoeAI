#include "../include/game.hpp"

Game::Game () {
	this->turn = false;
	for (int i = 0; i < 9; i++) {
		this->board[i] = 0;
	}
}

void Game::debug_print () {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << "[" << this->board[3*i + j] << "]";
		}
		std::cout << std::endl;
	}
	char t;
	if (this->turn) { t = 'o'; } else { t = 'x'; }
	std::cout << "it's " << t << " turn\n";
	std::cout << "move history : [";
	for (int i = 0; i < this->move_history.size(); i++) {
		std::cout << this->move_history[i] << ", ";
	}
	std::cout << "]\n";
}

Game copy_game (Game* g) {
	Game c = Game();
	c.turn = g->turn;
	for (int i = 0; i < 9; i++) { c.board[i] = g->board[i]; }
	for (int j = 0; j < g->move_history.size(); j++) { c.move_history.push_back(g->move_history[j]);}
	return c;
}

void Game::play_move (int move) {
	if (this->check_win() != ON_GOING) { return; }
	if (this->turn) {
		this->board[move] = -1;
	} else {
		this->board[move] = 1;
	}
	this->turn = !this->turn;
	this->move_history.push_back(move);
}

bool Game::is_legal (int move) {
	if (this->board[move] == 0)
		return true;
	return false;
}

std::vector<int> Game::legal_moves () {
	std::vector<int> m;
	for (int i = 0; i < 9; i++) {
		if (this->is_legal(i)) {
			m.push_back(i);
		}
	}
	return m;
}

void Game::undo_move () {
	if (this->move_history.size() > 0) {
		int move = this->move_history[this->move_history.size() - 1];
		this->move_history.pop_back();
		this->board[move] = 0;
	}
	this->turn = !this->turn;
}

Status Game::check_win () {
	for (int i = 0; i < 9; i+=3) {
		if (this->board[i] + this->board[i+1] + this->board[i+2] == 3) {
			return X_WIN;
		} else if (this->board[i] + this->board[i+1] + this->board[i+2] == -3) {
			return O_WIN;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (this->board[i] + this->board[3 + i] + this->board[6 + i] == 3) {
			return X_WIN;
		} else if (this->board[i] + this->board[3 + i] + this->board[6 + i] == -3) {
			return O_WIN;
		}
	}

	if (this->board[0] + this->board[4] + this->board[8] == 3) {
		return X_WIN;
	} else if (this->board[0] + this->board[4] + this->board[8] == -3) {
		return O_WIN;
	}

	if (this->board[2] + this->board[4] + this->board[6] == 3) {
		return X_WIN;
	} else if (this->board[2] + this->board[4] + this->board[6] == -3) {
		return O_WIN;
	}

	bool has_move = false;
	for (int i = 0; i < 9; i++) { if (this->board[i] == 0) { has_move = true; } }
	if (has_move) {
		return ON_GOING;
	} else {
		return DRAW;
	}
}

void Game::draw (sf::RenderWindow* window) {
	sf::Texture x;
	sf::Texture o;
	if (!x.loadFromFile("assets/cross.png")) { window->close(); std::cout << "Error while loading cross sprite\n"; }
	if (!o.loadFromFile("assets/circle.png")) { window->close(); std::cout << "Error while loading circle sprite\n"; }
	
	for (int i = 0; i < 9; i++) {
		if (this->board[i] == 1) {
			sf::Sprite sprite;
			sprite.setTexture(x);
			sprite.setPosition(15 + i%3 * 150, 15 + i/3 * 150);
			sprite.setScale(sf::Vector2f(0.15f, 0.15f));
			window->draw(sprite);
		} else if (this->board[i] == -1) {
			sf::Sprite sprite;
			sprite.setTexture(o);
			sprite.setPosition(15 + i%3 * 150, 15 + i/3 * 150);
			sprite.setScale(sf::Vector2f(0.15f, 0.15f));
			window->draw(sprite);
		}
	}
}
