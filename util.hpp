#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

typedef enum {
	LEFT, RIGHT
} playing_side;

typedef enum {
	GOAL, EMPTY, PLAYER, BALL
} tile;

struct config {
	playing_side s;
	unsigned int k;
	std::vector<tile> field;

	config ();
	config (char s, unsigned int k, std::string _field);

	void insert_player(int i);
};

config read_config();
bool read_move(config &c);
void write_player(int i);
void write_jumps(vecvtor<int> path);
void write_end();
void write_move(char cmd, int i, std::vector<int> path);
