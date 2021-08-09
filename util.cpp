#include "util.hpp"
using namespace std;

config::config () {}
config::config (char s, unsigned int k, string _field) : s(s == 'e' ? LEFT : RIGHT), k(k) {
	field.resize(k+2);
	field[0] = field[k+1] = GOAL;
	for (unsigned int i = 0; i < k; ++i)
		switch (_field[i]) {
			case '.':
				field[i+1] = EMPTY;
				break;
			case 'o':
				field[i+1] = BALL;
				break;
			case 'f':
				field[i+1] = PLAYER;
				break;
		}
}

void config::insert_player(int i) {
	if (field[i] != EMPTY)
		cerr << "Tried inserting player at non-empty position " << i << '\n';
	else
		field[i] = PLAYER;
}

vector<tile>::iterator config::moveBola(vector <tile> tabuleiro, int direction, vector<tile>::iterator ball_pos) {

		while (*(ball_pos + direction) == PLAYER) {
				auto destination = ball_pos + direction;
				while (*destination == PLAYER)
						destination += direction;
				fill(ball_pos, destination, EMPTY);
				*destination = BALL;
				ball_pos = destination;
		}

		return ball_pos;

}

bool config::fazGol(int direction) {

		vector <tile> field_copia = this->field;
		auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);
		auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();

		if (distance(moveBola(field_copia, direction, ball_pos), gol_pos) == 0)
				return true;
		return false;

}

bool config::haDoisOuMaisSaltos(int direction) {

		vector <tile> field_copia = this->field;
		auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);

		if (abs(distance(moveBola(field_copia, direction, ball_pos), ball_pos)) > 2)
				return true;
		return false;

}

bool config::caiPosicaoMorta(int direction) {

		vector <tile> field_copia = this->field;
		auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);
		auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();

		if (distance(moveBola(field_copia, direction, ball_pos), gol_pos) == 1)
				return true;
		return false;

}

void config::play() {
		
		auto ball_pos = find(this->field.begin(), this->field.end(), BALL);
		int direction = (this->s == LEFT) ? 1 : -1;

		/*
		if (fazGol(direction))
				//move a bola pro gol
		else if (fazGol(-direction))    //se o oponente pode fazer gol
				//empurra a bola pra frente
		else if (caiPosicaoMorta())     //se cai exatamente ao lado do gol
				//coloca um filosófo na posição antes do gol
		else if (haDoisOuMaisSaltos(direction))
				//manda a bola o mais pra frente possível
		else
				//coloca filosofo alternado
				*/
}

config read_config() {
	char _s;
	unsigned int _k;
	string _field;
	cin >> _s >> _k >> _field;
	return config(_s, _k, _field);
}

bool read_move(config &c) {
	char cmd;
	cin >> cmd;
	if (cmd == 'f') {
		int i;
		cin >> i;
		c.insert_player(i);
	} else if (cmd == 'o') {
		int jumps, dest;
		cin >> jumps;
		while (jumps--) {
			cin >> dest;
			//pula pro destino
		}
	} else return true;
	return false;
}

void write_player(int i) {
	cout << "f " << i << '\n';
}

void write_jumps(vector<int> path) {
	cout << "o " << path.size();
	for (auto jump: path)
		cout << ' ' << jump;
	cout << '\n';
}
