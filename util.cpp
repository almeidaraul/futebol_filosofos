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

vector<tile>::iterator config::moveBolaIterador(vector <tile> &tabuleiro, int direction) {
	auto ball_pos = find(tabuleiro.begin(), tabuleiro.end(), BALL);

	while (*(ball_pos + direction) == PLAYER) {
		auto destination = ball_pos + direction;
		while (*destination == PLAYER)
			destination += direction;
		if (distance(tabuleiro.begin(), ball_pos) < distance(tabuleiro.begin(), destination))
			fill(ball_pos, destination, EMPTY);
		else
			fill(destination, ball_pos, EMPTY);
		*destination = BALL;
		ball_pos = destination;
	}

	return ball_pos;
}

vector<int> config::moveBolaVetor(vector <tile> &tabuleiro, int direction) {
	vector<int> v;
	auto ball_pos = find(tabuleiro.begin(), tabuleiro.end(), BALL);

	while (*(ball_pos + direction) == PLAYER) {
		auto destination = ball_pos + direction;
		while (*destination == PLAYER)
			destination += direction;
		v.push_back(distance(tabuleiro.begin(), destination));
		if (distance(tabuleiro.begin(), ball_pos) < distance(tabuleiro.begin(), destination))
			fill(ball_pos, destination, EMPTY);
		else
			fill(destination, ball_pos, EMPTY);
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

bool config::deveSaltar(int direction) {
	vector <tile> field_copia = this->field;
	auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);

	int dist = abs(distance(moveBolaIterador(field_copia, direction), ball_pos));

	int distancia_a_saltar = (this->k/4 > 3) ? this->k/4 : 3;

	if (dist > distancia_a_saltar)
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

int config::melhorPosicaoFilosofo(vector <tile> &tabuleiro, int direction) {
	auto ball_pos = find(tabuleiro.begin(), tabuleiro.end(), BALL);
	auto gol_pos = (this->s == LEFT) ? tabuleiro.end()-1 : tabuleiro.begin();

	while (*(ball_pos + direction) == PLAYER) {
		while (*(ball_pos + direction) == PLAYER)
			ball_pos = ball_pos + direction;
		ball_pos = ball_pos+direction;
	}

	if (*(ball_pos) == BALL)
		ball_pos += direction;

	bool ha_dois_filosofos_seguidos = false;
	auto iter = find(tabuleiro.begin(), tabuleiro.end(), BALL);

	while (iter != (gol_pos-direction)) {
		if (*iter == PLAYER && *(iter+direction) == PLAYER)
			ha_dois_filosofos_seguidos = true;
		iter += direction;
	}

	if ((*(ball_pos-direction) != BALL) && (((abs(distance(ball_pos, gol_pos))) % 2 == 0) || (ha_dois_filosofos_seguidos)))
		ball_pos += direction;

	int posicao_filosofo = distance(tabuleiro.begin(), ball_pos);
	return posicao_filosofo;
}

void config::play() {
	vector <tile> field_copia = this->field;
	int direction = (this->s == LEFT) ? 1 : -1;
	auto gol_pos = (this->s == LEFT) ? field_copia.end()-1 : field_copia.begin();

	if (fazGol(direction)) {
		write_jumps(moveBolaVetor(field_copia, direction), s);
		over = true;
	}
	else if (fazGol(-direction))//se o oponente pode fazer gol 
		//empurra a bola pra frente
		write_jumps(moveBolaVetor(field_copia, direction), s);
	else if (caiPosicaoMorta(direction)) //se cai exatamente ao lado do gol
		//coloca um filosófo na posição antes do gol
		write_player(distance(field_copia.begin(), gol_pos) - direction, s);
	else if (deveSaltar(direction))
		//manda a bola o mais pra frente possível
		write_jumps(moveBolaVetor(field_copia, direction), s);
	else
		//coloca filosofo alternado
		write_player(melhorPosicaoFilosofo(field_copia, direction), s);
}

vector<string> split_string(string s, char separator=' ') {
	vector<string> ans;
	string t = "";
	for (auto c: s)
		if (c == separator || c == '\n') {
			ans.push_back(t);
			t = "";
		} else {
			t.push_back(c);
		}
	return ans;
}

config read_move(config c = config()) {
	char _s = c.s;
	unsigned int _k = c.k;
	char buf[512];
	campo_recebe(buf);
	vector<string> split = split_string(buf);
	cout << "Read opponent move:";
	for (size_t i = 3; i < split.size(); ++i)
		cout << ' ' << split[i];
	cout << endl;
	_s = split[0][0];
	_k = stoi(split[1]);
	string _field = split[2];
	c = config(_s, _k, _field);
	c.over = c.over || c.field[0] == BALL || c.field[c.k] == BALL;
	return c;
}

void write_player(int i, playing_side s) {
	char buf[512];
	sprintf(buf, "%c f %d\n", s == LEFT ? 'e' : 'd', i);
	campo_envia(buf);  
}

void write_jumps(vector<int> path, playing_side s) {
	char buf[512];
	char temp[51];
	sprintf(buf, "%c o %ld", s == LEFT ? 'e' : 'd', path.size());
	for (auto jump: path) {
		sprintf(temp, " %d", jump);
		strcat(buf, temp);
	}
	sprintf(temp, "\n");
	strcat(buf, temp);
	campo_envia(buf);  
}
