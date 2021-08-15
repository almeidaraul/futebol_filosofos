#include "util.hpp"
using namespace std;

int main(int argc, char **argv) {
	cout << "Futebas solver for phutball_1d\n";
	campo_conecta(argc, argv);
	cout << "Connection to controller established\n";
	config c;
	c.s = argv[1][0] == 'e' ? LEFT : RIGHT;
	c = read_move(c);
	while (!c.over) {
		c.play();
		c = read_move(c);
	}
	cout << "Game over\n";
}
