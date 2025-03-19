#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>

enum Status { ON_GOING, DRAW, X_WIN, O_WIN };

struct Game {
	// turn = false, x turn / turn = true, o turn
	bool turn;
	int board[9];
	std::vector<int> move_history;

	Game ();
	void debug_print ();
	void play_move (int move);
	void undo_move ();
	Status check_win ();
	std::vector<int> legal_moves ();
	bool is_legal (int move);
	void draw (sf::RenderWindow* window);
};

Game copy_game (Game* g);
