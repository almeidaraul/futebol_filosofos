#include "util.hpp"
using namespace std;

int main() {
	config c = read_config();
	bool over;
	do {
		over = read_move(c);
		write_move('o', 1, vector<int>({1, 2, 3}));
	} while (!over);
}
