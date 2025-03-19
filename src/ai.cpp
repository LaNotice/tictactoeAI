#include "../include/ai.hpp"

int ai_move (Game* g, int depth, int alpha, int beta, int* count) {
	*count += 1;
	int best;
	if (g->turn) {
		best = 5;
	} else {
		best = -5;
	}

	if (depth == 0 || evaluate(g) != 0 || g->check_win() == DRAW) {
		return evaluate(g);
	}

	std::vector<int> all_moves = g->legal_moves();
	for (int i = 0; i < all_moves.size(); i++) {
		g->play_move(all_moves[i]);
		int score = ai_move(g, depth - 1, alpha, beta, count);
		g->undo_move();

		if (g->turn && score < best) {
			best = score;
		} else if (!g->turn && score > best) {
			best = score;
		}

		// improve performance
		if (g->turn && score <= beta) {
			beta = score;
			if (beta <= alpha) { break; }
		} else if (!g->turn && score >= alpha) {
			alpha = score;
			if (alpha >= beta) { break; }
		}
	}

	return best;
}


int evaluate (Game* g) {
	Status s = g->check_win();
	switch (s) {
		case ON_GOING:
			return 0;
		case DRAW:
			return 0;
		case X_WIN:
			return 1;
		case O_WIN:
			return -1;
	}
	std::cout << "ERROR INVALID RETURN IN CHECK_WIN\n";
	return -5;
}
