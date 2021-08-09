#include "util.hpp"
using namespace std;

int main() {
	config c = read_config();
	bool over;
	do {
		over = read_move(c);
		write_move('f', 1, vector<int>());
	} while (!over);
}
