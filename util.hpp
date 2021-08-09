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
	std::vector<tile>::iterator moveBola(std::vector<tile> tabuleiro, int direction, std::vector<tile>::iterator ball_pos);
	bool fazGol(int direction);
	bool haDoisOuMaisSaltos(int direction);
	bool caiPosicaoMorta(int direction);
	void play();
};

config read_config();
bool read_move(config &c);
void write_player(int i);
void write_jumps(std::vector<int> path);
