#include "util.hpp"
using namespace std;

int main() {
	config c = read_config();
	bool over;
	while (read_move(c))
		c.play();
}
