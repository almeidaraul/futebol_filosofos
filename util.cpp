#include <algorithm>
#include <vector>

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

    vector::iterator moveBola(vector <tile> tabuleiro, int direction, vector::iterator ball_pos) {

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

    bool fazGol(int direction) {

        vector <tile> field_copia = this->field;
        auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);
        auto gol_pos = (this-> == LEFT) ? field_copia.end()-1 : field_copia.begin()

        if (distance(moveBola(field_copia, direction, ball_pos), gol_pos) == 0)
            return true;
        return false;

    }

    bool haDoisOuMaisSaltos(int direction) {

        vector <tile> field_copia = this->field;
        auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);

        if (abs(distance(moveBola(field_copia, direction, ball_pos), ball_pos)) > 2)
            return true;
        return false;

    }

    bool caiPosicaoMorta(int direction) {

        vector <tile> field_copia = this->field;
        auto ball_pos = find(field_copia.begin(), field_copia.end(), BALL);
        auto gol_pos = (this-> == LEFT) ? field_copia.end()-1 : field_copia.begin()

        if (distance(moveBola(field_copia, direction, ball_pos), gol_pos) == 1)
            return true;
        return false;

    }

    void play() {
        
        auto ball_pos = find(this->field.begin(), this->field.end(), BALL);
        int direction = (this->s == LEFT) ? 1 : -1;

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
    }

}

config read_config() {
	char _s;
	unsigned int _k;
	string _field;
	cin >> _s >> _k >> _field;
	return config(_s, _k, _field);
}
