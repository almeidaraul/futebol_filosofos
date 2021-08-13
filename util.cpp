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
		auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();
        while (*(ball_pos + direction) == PLAYER) {
            while (*(ball_pos + direction) == PLAYER)
                ball_pos = ball_pos + direction;
            ball_pos = ball_pos+direction;
        }

        int posicao_filosofo = distance(tabuleiro.begin(), ball_pos);

        if ((abs(distance(ball_pos, gol_pos))) % 2 == 0)
            posicao_filosos += direction;
        return posicao_filosofo;
}

void config::play() {
		
		vector <tile> field_copia = this->field;
		int direction = (this->s == LEFT) ? 1 : -1;
		auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();

		
		if (fazGol(direction))
            write_jumps(moveBolaVetor(field_copia, direction));
		else if (fazGol(-direction))    //se o oponente pode fazer gol
            write_jumps(moveBolaVetor(field_copia, direction));
				//empurra a bola pra frente
		else if (caiPosicaoMorta(direction))     //se cai exatamente ao lado do gol
            write_player(distance(field_copia.begin(), gol_pos) - direction);
				//coloca um filosófo na posição antes do gol
		else if (haDoisOuMaisSaltos(direction))
            write_jumps(moveBolaVetor(field_copia, direction));
				//manda a bola o mais pra frente possível
		else
            write_player(melhorPosicaoFilosofo(field_copia, direction));
				//coloca filosofo alternado
				
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
