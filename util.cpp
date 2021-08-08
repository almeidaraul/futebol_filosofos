using namespace std;

typedef enum {
	LEFT, RIGHT
} playing_side;

typedef enum {
	GOAL, EMPTY, PLAYER, BALL
} tile;

struct config {
	playing_side s;
	unsigned int k;
	vector<tile> field;

	config () {}
	config (char s, unsigned int k, string _field) : s(s == 'e' ? LEFT : RIGHT), k(k) {
		field.resize(k+2);
		field[0] = field[k+1] = GOAL;
		for (int i = 0; i < k; ++i)
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

}

config read_config() {
	char _s;
	unsigned int _k;
	string _field;
	cin >> _s >> _k >> _field;
	return config(_s, _k, _field);
}
