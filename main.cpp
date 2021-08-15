#include "util.hpp"
using namespace std;

int main(int argc, char **argv) {
	campo_conecta(argc, argv);
	config c;
	c.s = argv[1][0] == 'e' ? LEFT : RIGHT;
	c = read_move(c);
	while (!c.over) {
		c.play();
		c = read_move(c);
	}
}
