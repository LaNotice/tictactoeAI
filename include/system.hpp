#include <cstdlib>
#include <iostream>
#include <ctime>
#include<SFML/Graphics.hpp>

#include "./ai.hpp"

void event_manager (sf::RenderWindow* window, Game* g, int* diff);
void draw_status (sf::RenderWindow* window, Status s, int diff);
int click_to_move (int x, int y);
