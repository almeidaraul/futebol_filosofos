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

void write_move(char cmd, int i, vector<int> path) {
	cout << cmd;
	if (cmd != 'n') {
		cout << ' ' << i;
		if (cmd == 'o')
			for (auto jump_destination: path)
				cout << ' ' << jump_destination;
		cout << '\n';
	}
}
