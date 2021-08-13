#include "util.hpp"
using namespace std;

int main(int argc, char **argv) {
	campo_conecta(argc, argv);
	config c;
	c.s = argv[1][0] == 'e' ? LEFT : RIGHT;
	while (!c.over) {
		c = read_move(c);
		c.play();
	}
}
