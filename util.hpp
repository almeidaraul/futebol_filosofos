#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
extern "C" {
#include "campo.h"
}

typedef enum {
	LEFT, RIGHT
} playing_side;

typedef enum {
	GOAL, EMPTY, PLAYER, BALL
} tile;

struct config {
	playing_side s;
	unsigned int k;
	bool over;
	std::vector<tile> field;

	config ();
	config (char s, unsigned int k, std::string _field);

	void insert_player(int i);
	std::vector<tile>::iterator moveBolaIterador(std::vector <tile> &tabuleiro, int direction);
	std::vector<int> moveBolaVetor(std::vector <tile> &tabuleiro, int direction) ;
	int melhorPosicaoFilosofo(std::vector <tile> &tabuleiro, int direction);
	bool fazGol(int direction);
	bool deveSaltar(int direction);
	bool caiPosicaoMorta(int direction);
	void play();
};

config read_move();
void write_player(int i, playing_side s);
void write_jumps(std::vector<int> path, playing_side s);
std::vector<std::string> split_string(std::string s);
