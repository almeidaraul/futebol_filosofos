#include "util.hpp"
using namespace std;

config::config () { over = false; }
config::config (char s, unsigned int k, string _field) : s(s == 'e' ? LEFT : RIGHT), k(k) {
	over = false;
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

vector<tile>::iterator config::moveBolaIterador(vector <tile> tabuleiro, int direction) {

		auto ball_pos = find(tabuleiro.begin(), tabuleiro.end(), BALL);
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
vector<int> config::moveBolaVetor(vector <tile> tabuleiro, int direction) {

        vector<int> v;

		auto ball_pos = find(tabuleiro.begin(), tabuleiro.end(), BALL);

		while (*(ball_pos + direction) == PLAYER) {
				auto destination = ball_pos + direction;
				while (*destination == PLAYER)
						destination += direction;
                v.push_back(distance(tabuleiro.begin(), destination));
				fill(ball_pos, destination, EMPTY);
				*destination = BALL;
				ball_pos = destination;
		}

		return v;

}

bool config::fazGol(int direction) {

		vector <tile> field_copia = this->field;
		auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();

		if (distance(moveBolaIterador(field_copia, direction), gol_pos) == 0)
				return true;
		return false;

}

bool config::haDoisOuMaisSaltos(int direction) {

		vector <tile> field_copia = this->field;
		auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);

		if (abs(distance(moveBolaIterador(field_copia, direction), ball_pos)) > 2)
				return true;
		return false;

}

bool config::caiPosicaoMorta(int direction) {

		vector <tile> field_copia = this->field;
		auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();

		if (distance(moveBolaIterador(field_copia, direction), gol_pos) == 1)
				return true;
		return false;

}

int config::melhorPosicaoFilosofo(vector <tile> tabuleiro, int direction) {

        
		auto ball_pos = find(this->field.begin(), this->field.end(), BALL);
        while (*(ball_pos + direction) == PLAYER) {
            while (*(ball_pos + direction) == PLAYER)
                ball_pos = ball_pos + direction;
            ball_pos = ball_pos+direction;
        }

        return (distance(tabuleiro.begin(), ball_pos) + direction);
}

void config::play() {
		
		vector <tile> field_copia = this->field;
		int direction = (this->s == LEFT) ? 1 : -1;
		auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();

		
		if (fazGol(direction))
            write_jumps(moveBolaVetor(field_copia, direction), s);
		else if (fazGol(-direction))    //se o oponente pode fazer gol
            write_jumps(moveBolaVetor(field_copia, direction), s);
				//empurra a bola pra frente
		else if (caiPosicaoMorta(direction))     //se cai exatamente ao lado do gol
            write_player(distance(field_copia.begin(), gol_pos) - direction, s);
				//coloca um filosófo na posição antes do gol
		else if (haDoisOuMaisSaltos(direction))
            write_jumps(moveBolaVetor(field_copia, direction), s);
				//manda a bola o mais pra frente possível
		else
            write_player(melhorPosicaoFilosofo(field_copia, direction), s);
				//coloca filosofo alternado
				
}

config read_move() {
	char _s;
	unsigned int _k;
	char char_field;
	char buf[512];
	campo_recebe(buf);
	sscanf(strtok(buf, " \n"), "%c", &_s);
	sscanf(strtok(buf, " \n"), "%d", &_k);
	sscanf(strtok(buf, " \n"), "%s", &char_field);
	string _field(char_field, char_field+_k);
	config c = config(_s, _k, _field);
	char cmd;
	sscanf(strtok(buf, " \n"), "%c", &cmd);
	if (cmd == 'f') {
		int i;
		sscanf(strtok(buf, " \n"), "%d", &i);
		c.insert_player(i);
	} else if (cmd == 'o') {
		int jumps, dest;
		vector<int> path;
		sscanf(strtok(buf, " \n"), "%d", &jumps);
		while (jumps--) {
			sscanf(strtok(buf, " \n"), "%d", &dest);
			path.push_back(dest);
			//pula pro destino
		}
	}
	c.over = c.field[0] == BALL || c.field[c.k] == BALL;
	return c;
}

void write_player(int i, playing_side s) {
	char buf[512];
  sprintf(buf, "%c f %d\n", s == LEFT ? 'e' : 'd', i);
  campo_envia(buf);  
}

void write_jumps(vector<int> path, playing_side s) {
	char buf[512];
  sprintf(buf, "%c o %ld", s == LEFT ? 'e' : 'd', path.size());
  sprintf(buf, "%c o %ld", s == LEFT ? 'e' : 'd', path.size());
	for (auto jump: path)
		sprintf(buf, " %d", jump);
	sprintf(buf, "\n");
  campo_envia(buf);  
}
